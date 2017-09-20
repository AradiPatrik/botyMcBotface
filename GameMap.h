#pragma once
#include <sc2api\sc2_api.h>
#include "BaseLocation.h"
#include <vector>

using namespace std;
using namespace sc2;

class Bot;
class GameMap {
	Bot & m_bot;
	vector<BaseLocation> m_baseLocations;
	int m_width;
	int m_height;
	vector<Point2DI> m_reservedTiles;

	vector<Units> GetResourceClusters(Units);
	bool IsTileReserved(const Point2DI &);

public:
	GameMap(Bot &);
	void OnStart();
	void ReserveTiles(const vector<Point2DI> &);
	bool IsTilePlaceable(const Point2DI &);

};

