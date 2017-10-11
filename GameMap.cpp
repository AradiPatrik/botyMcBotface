#include "GameMap.h"
#include "Bot.h"

#include <algorithm>
#include <iostream>
#include "Predicates.h"
#include "BaseLocation.h"
#include "Utils.h"

GameMap::GameMap(Bot &bot)
	: m_bot(bot)
	, m_width(0)
	, m_height(0)
{
}

void GameMap::OnStart()
{
	// this needs cleaning up
	m_width = m_bot.Observation()->GetGameInfo().width;
	m_height = m_bot.Observation()->GetGameInfo().height;

	// Initialize m_baseLocations
	sc2::Units resources = m_bot.Observation()->GetUnits(sc2::Unit::Alliance::Neutral, Predicates::isResource);
	std::vector<sc2::Units> resourceClusters = ClusterResources(resources);
	for (const auto& cluster : resourceClusters)
	{
		BaseLocation temp{ cluster, *this };
		m_baseLocations.push_back(temp);
	}

	// DrawPlaceableGrid();

	m_bot.Debug()->SendDebug();
}

void GameMap::ReserveTiles(const std::vector<sc2::Point2DI> &tiles)
{
	// TODO: check if tile is already reserved
	for (const auto& tile : tiles)
	{
		m_reservedTiles.push_back(tile);
	}
}

bool GameMap::IsTileReserved(const sc2::Point2DI &tile)
{
	// TODO: test this
	for (const auto &reservedTile : m_reservedTiles)
	{
		if (tile == reservedTile)
			return true;
	}
	return false;
}

bool GameMap::IsTilePlaceable(const sc2::Point2DI &tile)
{
	// TODO: test this
	return Utils::IsPlaceable(m_bot.Observation()->GetGameInfo(), tile) && !IsTileReserved(tile);
}

void GameMap::DrawPlaceableGrid()
{
	for (size_t y{ 0 }; y < m_height; y++)
	{
		for (size_t x{ 0 }; x < m_width; x++)
		{
			Utils::DrawSquareAroundPoint
			(
				*m_bot.Debug(),
				sc2::Point3D(x, y, Utils::HeightAtTile(m_bot.Observation()->GetGameInfo(), x, y)),
				0.5f
			);
		}
	}
}

std::vector<sc2::Units> GameMap::ClusterResources(sc2::Units resources)
{
	// tweak this if something broken about clustering
	const float maxSquareDistance = 400;
	std::vector<sc2::Units> resourceClusters;
	while (!resources.empty())
	{
		sc2::Units cluster;
		auto iterator = resources.begin();
		sc2::Point3D relativeTo = iterator->pos;
		while (iterator != resources.end())
		{
			const sc2::Point3D currentPos = iterator->pos;
			if (sc2::DistanceSquared3D(currentPos, relativeTo) < maxSquareDistance)
			{
				cluster.push_back(*iterator);
				relativeTo == iterator->pos;
				iterator = resources.erase(iterator);
			}
			else
			{
				++iterator;
			}
		}
		resourceClusters.push_back(cluster);
	}
	return resourceClusters;
}

void GameMap::DrawBoxAroundPoint(const sc2::Point3D& point, float radius, sc2::Color color)
{
	Utils::DrawSquareAroundPoint(*m_bot.Debug(), point, radius, color);
}

void GameMap::DrawLineBetweenPoints(const sc2::Point3D& first, const sc2::Point3D& second, sc2::Color color)
{
	m_bot.Debug()->DebugLineOut(first, second, color);
}