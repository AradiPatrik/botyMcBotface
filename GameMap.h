#pragma once
#include <sc2api\sc2_api.h>
#include <set>
#include <map>

using std::set; using sc2::Point3D;
using std::map; using sc2::Point2D;

class Bot;
class GameMap {
	Bot & m_bot;
	set<Point3D> m_baseLocations;
	int m_width;
	int m_height;
	map<Point2D, bool> m_buildableGrid;

public:
	GameMap(Bot &);
	void OnStart();
};

