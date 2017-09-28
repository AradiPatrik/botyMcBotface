#include "Utils.h"
#include "BaseLocation.h"
#include <algorithm>
bool Utils::IsPlaceable(const sc2::GameInfo& info, const sc2::Point2DI &tile) {
	unsigned char encodedPlacement = info.placement_grid.data[tile.x + ((info.height - 1) - tile.y) * info.width];
	bool decodedPlacement = encodedPlacement == 255;
	return decodedPlacement;
}

float Utils::HeightAtTile(const sc2::GameInfo& info, const sc2::Point2DI &tile) {
	unsigned char encodedHeight = info.terrain_height.data[tile.x + ((info.height - 1) - tile.y) * info.width];
	float decodedHeight = -100.0f + 200.0f * float(encodedHeight) / 255.0f;
	return decodedHeight;
}

float Utils::HeightAtTile(const sc2::GameInfo &info, size_t x, size_t y) {
	return HeightAtTile(info, sc2::Point2DI(x, y));
}

void Utils::DrawSquareAroundPoint(sc2::DebugInterface &debug, const sc2::Point3D& point, float radius, sc2::Color color) {
	sc2::Point3D half{ 0.5f, 0.5f, 0.5f };
	sc2::Point3D nearPoint = (point - half * radius);
	sc2::Point3D farPoint = (point + half * radius);
	debug.DebugBoxOut(nearPoint, farPoint, color);
}

void Utils::SortUnitsByDistanceFromPoint(const sc2::Point3D &ancor, std::vector<sc2::Unit> &units) {
	std::sort(units.begin(), units.end(), [&ancor](const sc2::Unit& first, const sc2::Unit& second) {
		return sc2::DistanceSquared3D(ancor, first.pos) < sc2::DistanceSquared3D(ancor, second.pos);
	});
}

// TODO: test this+
void Utils::SortPointsByDistanceFromPoint(const sc2::Point2D &ancor, std::vector<sc2::Point2D>& points) {
	std::sort(points.begin(), points.end(), [&ancor](const sc2::Point2D& first, const sc2::Point2D& second) {
		return sc2::DistanceSquared2D(ancor, first) < sc2::DistanceSquared2D(ancor, second);
	});
}

sc2::Point2D Utils::GetDirectionFromOrientation(ORIENTATION o) {
	switch (o) {
	case (ORIENTATION::TOP):			return sc2::Point2D(0, 1);
	case (ORIENTATION::TOP_RIGHT):		return sc2::Point2D(1, 1);
	case (ORIENTATION::RIGHT):			return sc2::Point2D(1, 0);
	case (ORIENTATION::BOTTOM_RIGHT):	return sc2::Point2D(1, -1);
	case (ORIENTATION::BOTTOM):			return sc2::Point2D(0, -1);
	case (ORIENTATION::BOTTOM_LEFT):	return sc2::Point2D(-1, 1);
	case (ORIENTATION::LEFT):			return sc2::Point2D(-1, 0);
	case (ORIENTATION::TOP_LEFT):		return sc2::Point2D(-1, 1);
	case (ORIENTATION::NOT_SET):		return sc2::Point2D(0, 0);
	}
	return sc2::Point2D(0, 0); // never reached
}