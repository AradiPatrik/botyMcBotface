#include "GameMap.h"
#include "Bot.h"

#include <algorithm>
#include <iostream>
#include "Filters.h"
#include "BaseLocation.h"
#include "Utils.h"

GameMap::GameMap(Bot &bot)
	: m_bot(bot)
	, m_width(0)
	, m_height(0) {}

void GameMap::OnStart() {
	m_width = m_bot.Observation()->GetGameInfo().width;
	m_height = m_bot.Observation()->GetGameInfo().height;

	// Initialize m_baseLocations
	sc2::Units resources = m_bot.Observation()->GetUnits(sc2::Unit::Alliance::Neutral, Filters::isResource);
	std::vector<sc2::Units> resourceClusters = ClusterResources(resources);
	for (const auto& cluster : resourceClusters) {
		BaseLocation temp{ cluster, *this };
		m_baseLocations.push_back(temp);
	}

	DrawPlaceableGrid();

	m_bot.Debug()->SendDebug();
}

void GameMap::ReserveTiles(const std::vector<sc2::Point2DI> &tiles) {
	for (const auto& tile : tiles) {
		m_reservedTiles.push_back(tile);
	}
}

bool GameMap::IsTileReserved(const sc2::Point2DI &tile) {
	for (const auto &reservedTile : m_reservedTiles) {
		if (tile == reservedTile)
			return true;
	}
	return false;
}

bool GameMap::IsTilePlaceable(const sc2::Point2DI &tile) {
	unsigned char encodedPlacement = m_bot.Observation()
		->GetGameInfo()
		.placement_grid
		.data[tile.x + ((m_height - 1) - tile.y) * m_width];
	return encodedPlacement == 255 && !IsTileReserved(tile);
}

void GameMap::DrawPlaceableGrid() {
	for (size_t y{ 0 }; y < m_height; y++) {
		for (size_t x{ 0 }; x < m_width; x++) {
			Utils::DrawSquareAroundPoint
			(
				*m_bot.Debug(),
				sc2::Point3D(x, y, Utils::HeightAtTile(m_bot.Observation()->GetGameInfo(), x, y)),
				0.5f
			);
		}
	}
}

std::vector<sc2::Units> GameMap::ClusterResources(sc2::Units resources) {
	const float maxSquareDistance = 400;
	std::vector<sc2::Units> resourceClusters;
	while (!resources.empty()) {
		sc2::Units cluster;
		auto iterator = resources.begin();
		sc2::Point3D relativeTo = iterator->pos;
		while (iterator != resources.end()) {
			const sc2::Point3D currentPos = iterator->pos;
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