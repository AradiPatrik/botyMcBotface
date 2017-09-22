#pragma once
#include <vector>
#include <sc2api/sc2_api.h>

// !Defines where the minerals are relative to the BasePosition
enum class Orientation {
	TOP,
	TOP_RIGHT,
	RIGHT,
	BOTTOM_RIGHT,
	BOTTOM,
	BOTTOM_LEFT,
	LEFT,
	TOP_LEFT,
	NOT_SET
};

class GameMap;
// !Used for getting data about an expansion
class BaseLocation {
	sc2::Units m_resources;
	sc2::Units m_geisers;
	sc2::Units m_minerals;
	sc2::Point3D m_centerOfResources;
	sc2::Point3D m_basePosition;
	Orientation m_orientation;
	GameMap & m_map;
	void FindCenterOfResources();
	void FindBasePosition();
	void FindOrientation();
	void SplitResources();
	void DrawCenters();

public:
	BaseLocation(const sc2::Units &, GameMap &);
	const sc2::Point3D Center() const;
	const sc2::Point3D BasePosition() const;
};
