#pragma once
#include <vector>
#include <sc2api\sc2_api.h>

using namespace std;
using namespace sc2;

class GameMap;
class BaseLocation {
	Units m_resources;
	Point3D m_centerOfResources;
	Point3D m_basePosition;
	GameMap & m_map;
	void FindCenterOfResources();
	void FindBasePosition();

public:
	BaseLocation(const Units &, GameMap &);
	const Point3D Center() const;
	const Point3D BasePosition() const;
};
