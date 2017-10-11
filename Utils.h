#pragma once
#include <sc2api/sc2_api.h>
#include "BaseLocation.h"
namespace Utils
{
	bool IsPlaceable(const sc2::GameInfo &info, const sc2::Point2DI &tile);

	float HeightAtTile(const sc2::GameInfo &info, const sc2::Point2DI &tile);
	float HeightAtTile(const sc2::GameInfo &info, size_t x, size_t y);

	void DrawSquareAroundPoint(sc2::DebugInterface &debug, const sc2::Point3D &point, float radius = 1.0f, sc2::Color color = sc2::Colors::White);

	void SortUnitsByDistanceFromPoint(const sc2::Point3D &ancor, std::vector<sc2::Unit> &units);

	void SortPointsByDistanceFromPoint(const sc2::Point2D &ancor, std::vector<sc2::Point2D> &points);

	sc2::Point2D GetDirectionFromOrientation(ORIENTATION o);
}