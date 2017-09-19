#include "GameMap.h"
#include "Bot.h"

#include <algorithm>
#include <iostream>
#include "Filters.h"
#include "BaseLocation.h"

using sc2::Units; using sc2::Unit;
using std::vector; using std::remove;
using std::cout; using std::endl;
using sc2::Point3D;



GameMap::GameMap(Bot & bot)
	: m_bot(bot)
	, m_width(0)
	, m_height(0)
{}

void GameMap::OnStart() {
	m_width = m_bot.Observation()->GetGameInfo().width;
	m_height = m_bot.Observation()->GetGameInfo().height;

	// Initialize m_baseLocations
	Units resources = m_bot.Observation()->GetUnits(Unit::Alliance::Neutral, Filters::resourceFilter);
	vector<Units> resourceClusters = GetResourceClusters(resources);
	for (const auto& cluster : resourceClusters) {
		BaseLocation temp{ cluster };
		m_baseLocations.push_back(temp);
	}

	for (const auto &location : m_baseLocations) {
		m_bot.Debug()->DebugSphereOut(location.Center(), 1.0f, Colors::Red);
	}
	m_bot.Debug()->SendDebug();
}

// Helper functions

vector<Units> GameMap::GetResourceClusters(Units resources) {
	const float maxSquareDistance = 400;
	vector<Units> resourceClusters;
	while (!resources.empty()) {
		Units cluster;
		auto iterator = resources.begin();
		Point3D relativeTo = iterator->pos;
		while (iterator != resources.end()) {
			const Point3D currentPos = iterator->pos;
			if (sc2::DistanceSquared3D(currentPos, relativeTo) < maxSquareDistance) {
				cluster.push_back(*iterator);
				relativeTo == iterator->pos;
				iterator = resources.erase(iterator);
			} else {
				++iterator;
			}
		}
		resourceClusters.push_back(cluster);
	}
	return resourceClusters;
}
