#include "BaseLocation.h"
#include "GameMap.h"

BaseLocation::BaseLocation(const Units & resources, GameMap & map) 
	: m_resources(resources)
	, m_centerOfResources{0.0f, 0.0f, 0.0f}
	, m_map(map)
{
	FindCenterOfResources();
}

const Point3D BaseLocation::Center() const {
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

void BaseLocation::FindBasePosition() {
	
}

