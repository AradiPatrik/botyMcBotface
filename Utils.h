#pragma once
#include <sc2api/sc2_api.h>
#include "BaseLocation.h"
namespace Utils {
	// !returns if a tile is placeable or not
	bool IsPlaceable(const sc2::GameInfo &, const sc2::Point2DI &);

	float HeightAtTile(const sc2::GameInfo &, const sc2::Point2DI &);
	float HeightAtTile(const sc2::GameInfo &, size_t, size_t);

	// !draws square around unit
	void DrawSquareAroundPoint(sc2::DebugInterface &, const sc2::Point3D &, float = 1.0f, sc2::Color = sc2::Colors::White);

	void SortUnitsByDistanceFromPoint(const sc2::Point3D &, std::vector<sc2::Unit>&);

	void SortPointsByDistanceFromPoint(const sc2::Point2D &, std::vector<sc2::Point2D>&);

	sc2::Point2D GetDirectionFromOrientation(ORIENTATION o);
}