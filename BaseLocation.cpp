#include "BaseLocation.h"
#include "GameMap.h"
#include "Filters.h"

BaseLocation::BaseLocation(const sc2::Units & resources, GameMap & map)
	: m_resources(resources)
	, m_centerOfMinerals{ 0.0f, 0.0f, 0.0f }
	, m_map(map)
	, m_orientation(Orientation::NOT_SET)
{
	SplitResources();
	FindCenterOfMinerals();

	// draw box around minerals
	for (const auto& mineral : m_minerals) {
		m_map.DrawBoxAroundPoint(mineral.pos, 1.0f, sc2::Colors::Red);
	}
}

// !The center of the resources, not equals the base position
const sc2::Point3D BaseLocation::GetCenterOfMinerals() const {
	return m_centerOfMinerals;
}

void BaseLocation::FindCenterOfMinerals() {
	for (const auto& mineral : m_minerals) {
		m_centerOfMinerals += mineral.pos;
	}
	m_centerOfMinerals.x /= m_minerals.size();
	m_centerOfMinerals.y /= m_minerals.size();
	m_centerOfMinerals.z /= m_minerals.size();
}

void BaseLocation::SplitResources() {
	for (const auto &resource : m_resources) {
		if (Filters::isMineral(resource)) {
			m_minerals.push_back(resource);
		} else {
			m_geisers.push_back(resource);
		}
	}
}

void BaseLocation::FindOrientation() {}

void BaseLocation::FindBasePosition() {}

void BaseLocation::DrawCenters() {
}