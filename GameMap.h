#pragma once
#include <sc2api\sc2_api.h>
#include "BaseLocation.h"
#include <vector>
#include <map>

using namespace std;
using namespace sc2;

class Bot;
class GameMap {
	Bot & m_bot;
	vector<BaseLocation> m_baseLocations;
	int m_width;
	int m_height;

	// TODO: initialize this
	map<Point2D, bool> m_buildableGrid;
	vector<Units> GetResourceClusters(Units);

public:
	GameMap(Bot &);
	void OnStart();
};

