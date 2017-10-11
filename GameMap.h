#pragma once
#include <sc2api\sc2_api.h>
#include "BaseLocation.h"
#include <vector>
#include <string>

class Bot;
// !Contains base positions
class GameMap
{
	Bot & m_bot;
	std::vector<BaseLocation> m_baseLocations;
	int m_width;
	int m_height;
	std::vector<sc2::Point2DI> m_reservedTiles;

	std::vector<sc2::Units> ClusterResources(sc2::Units);
	bool IsTileReserved(const sc2::Point2DI &);

public:
	GameMap(Bot &);
	void OnStart();
	// !Reserve a Tile for construction
	void ReserveTiles(const std::vector<sc2::Point2DI> & tiles);
	// !This function takes tile index as parameter, which can be calculated as: (int)(Point + 0.5f)
	// !Checks if tile is reserved and placeable
	bool IsTilePlaceable(const sc2::Point2DI &tile);
	void DrawPlaceableGrid();
	void DrawBoxAroundPoint(const sc2::Point3D &point, float radius = 1.0, sc2::Color color = sc2::Colors::White);
	void DrawLineBetweenPoints(const sc2::Point3D &first, const sc2::Point3D &second, sc2::Color color = sc2::Colors::White);
};
