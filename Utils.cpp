#include "Utils.h"
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
