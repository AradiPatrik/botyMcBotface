#pragma once
#include <vector>
#include <array>
#include <sc2api/sc2_api.h>

// !Indicates position of the minerals relative to the center
enum class ORIENTATION {
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
	static const std::array<ORIENTATION, 9> orientations;
	sc2::Units m_resources;
	sc2::Units m_geisers;
	sc2::Units m_minerals;
	sc2::Point3D m_centerOfMinerals;
	sc2::Point3D m_basePosition;
	ORIENTATION m_orientation;
	GameMap & m_map;

	void FindCenterOfMinerals();
	void FindBasePosition();
	void FindOrientation();
	void SplitResources();

public:
	BaseLocation(const sc2::Units &, GameMap &);
	const sc2::Point3D GetCenterOfMinerals() const;
	const sc2::Point3D GetBasePosition() const;
};
