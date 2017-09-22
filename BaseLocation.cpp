#include "BaseLocation.h"
#include "GameMap.h"
#include "Filters.h"

BaseLocation::BaseLocation(const sc2::Units & resources, GameMap & map)
	: m_resources(resources)
	, m_centerOfResources{ 0.0f, 0.0f, 0.0f }
	, m_map(map)
	, m_orientation(Orientation::NOT_SET)
{
	FindCenterOfResources();
	SplitResources();
}

// !The center of the resources, not equals the base position
const sc2::Point3D BaseLocation::Center() const {
	return m_centerOfResources;
}

void BaseLocation::FindCenterOfResources() {
	for (const auto& resource : m_resources) {
		m_centerOfResources += resource.pos;
	}
	m_centerOfResources.x /= m_resources.size();
	m_centerOfResources.y /= m_resources.size();
	m_centerOfResources.z /= m_resources.size();
}

void BaseLocation::SplitResources() {
	for (const auto &resource : m_resources) {
		if (Filters::isMineral(resource)) {
			m_minerals.push_back(resource);
		} else {
			m_resources.push_back(resource);
		}
	}
}

void BaseLocation::FindOrientation() {}

void BaseLocation::FindBasePosition() {}

void BaseLocation::DrawCenters() {
}