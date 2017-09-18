#include "GameMap.h"
#include "Bot.h"

#include <algorithm>
#include <iostream>
#include "Filters.h"

using sc2::Units; using sc2::Unit;
using std::vector; using std::remove;
using std::cout; using std::endl;
using sc2::Point3D;

vector<Point3D> GetCenterOfResourceClusters(const vector<Units> & resourceClusters);
vector<Units> GetResourceClusters(Units);

GameMap::GameMap(Bot & bot)
	: m_bot(bot)
	, m_width(0)
	, m_height(0)
{}

void GameMap::OnStart() {
	m_width = m_bot.Observation()->GetGameInfo().width;
	m_height = m_bot.Observation()->GetGameInfo().height;
	Units resources = m_bot.Observation()->GetUnits(Unit::Alliance::Neutral, Filters::resourceFilter);
	vector<Units> resourceClusters = GetResourceClusters(resources);
	cout << resourceClusters.size() << endl;
	vector<Point3D> centers = GetCenterOfResourceClusters(resourceClusters);
}

// Helper functions

vector<Units> GetResourceClusters(Units resources) {
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

vector<Point3D> GetCenterOfResourceClusters(const vector<Units> & resourceClusters) {
	vector<Point3D> clusterCenters;
	clusterCenters.reserve(resourceClusters.size());
	for (const auto& cluster : resourceClusters) {
		Point3D clusterCenter{ 0.0f, 0.0f, 0.0f };
		for (const auto& resource : cluster) {
			clusterCenter += resource.pos;
		}
		clusterCenter.x /= cluster.size();
		clusterCenter.y /= cluster.size();
		clusterCenter.z /= cluster.size();
		clusterCenters.push_back(clusterCenter);
	}
	return clusterCenters;
}
