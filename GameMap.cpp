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
		BaseLocation temp{ cluster, *this };
		m_baseLocations.push_back(temp);
	}

	ImageData placement_grid = m_bot.Observation()->GetGameInfo().placement_grid;
	ImageData height_grid = m_bot.Observation()->GetGameInfo().terrain_height;
	// Visualize Grid
	for (size_t y{ 0 }; y < m_height; y++) {
		for (size_t x{ 0 }; x < m_width; x++) {
			unsigned char encodedHeight = height_grid.data[x + ((m_height - 1) - y) * m_width];
			float decodedHeight = -100.0f + 200.0f * float(encodedHeight) / 255.0f;
			m_bot.Debug()->DebugBoxOut(Point3D( x, y, decodedHeight ), Point3D( x + 1, y + 1, decodedHeight + 1 ));
		}
	}
	m_bot.Debug()->SendDebug();

}

// !This function takes tile index as parameter, wich can be calculated as: (int)(Point + 0.5f)
void GameMap::ReserveTiles(const vector<Point2DI>& tiles) {
	for (const auto& tile : tiles) {
		m_reservedTiles.push_back(tile);
	}
}

bool GameMap::IsTileReserved(const Point2DI &tile) {
	for (const auto &reservedTile : m_reservedTiles) {
		if (tile == reservedTile)
			return true;
	}
	return false;
}

bool GameMap::IsTilePlaceable(const Point2DI &tile) {
	unsigned char encodedPlacement = m_bot.Observation()
		->GetGameInfo()
		.placement_grid
		.data[tile.x + ((m_height - 1) - tile.y) * m_width];
	return encodedPlacement == 255 && !IsTileReserved(tile);
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
