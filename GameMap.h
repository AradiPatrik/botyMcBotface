#pragma once
#include <sc2api\sc2_api.h>
#include "BaseLocation.h"
#include <vector>

class Bot;
// !Contains base positions
class GameMap {
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
	void ReserveTiles(const std::vector<sc2::Point2DI> &);
	// !This function takes tile index as parameter, which can be calculated as: (int)(Point + 0.5f)
	bool IsTilePlaceable(const sc2::Point2DI &);
	void DrawPlaceableGrid();
};
