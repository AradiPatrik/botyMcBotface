#include "BaseLocation.h"
#include "GameMap.h"
#include "Predicates.h"
#include "Utils.h"

const std::array<ORIENTATION, 9> BaseLocation::orientations{
	ORIENTATION::TOP,			ORIENTATION::TOP_RIGHT, ORIENTATION::RIGHT,
	ORIENTATION::BOTTOM_RIGHT,	ORIENTATION::BOTTOM,	ORIENTATION::BOTTOM_LEFT,
	ORIENTATION::LEFT,			ORIENTATION::TOP_LEFT,	ORIENTATION::NOT_SET
};

BaseLocation::BaseLocation(const sc2::Units &resources, GameMap &map)
	: m_resources(resources)
	, m_centerOfMinerals{ 0.0f, 0.0f, 0.0f }
	, m_map(map)
	, m_orientation(ORIENTATION::NOT_SET)
{
	SplitResources();
	FindCenterOfMinerals();
	FindOrientation();
}

const sc2::Point3D BaseLocation::GetCenterOfMinerals() const
{
	return m_centerOfMinerals;
}

void BaseLocation::FindCenterOfMinerals()
{
	for (const auto& mineral : m_minerals)
	{
		m_centerOfMinerals += mineral.pos;
	}
	m_centerOfMinerals.x /= m_minerals.size();
	m_centerOfMinerals.y /= m_minerals.size();
	m_centerOfMinerals.z /= m_minerals.size();
}

void BaseLocation::SplitResources()
{
	for (const auto &resource : m_resources)
	{
		if (Predicates::isMineral(resource))
		{
			m_minerals.push_back(resource);
		}
		else
		{
			m_geisers.push_back(resource);
		}
	}
}

void BaseLocation::FindOrientation()
{
	Utils::SortUnitsByDistanceFromPoint(m_centerOfMinerals, m_minerals);
	const sc2::Point3D firstMineral = m_minerals[m_minerals.size() - 1].pos;
	const sc2::Point3D secondMineral = m_minerals[m_minerals.size() - 2].pos;
	const sc2::Point3D middle = (firstMineral + secondMineral) / 2;
	sc2::Point3D direction = middle - m_centerOfMinerals;
	sc2::Normalize3D(direction);
	float closestDistance = std::numeric_limits<float>::max();
	for (ORIENTATION orientation : orientations)
	{
		// FIXME: get angle instead of distance
		float currentDistance = sc2::DistanceSquared2D(direction, Utils::GetDirectionFromOrientation(orientation));
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			m_orientation = orientation;
		}
	}
	sc2::Point3D begin = m_centerOfMinerals;
	sc2::Point3D end = sc2::Point3D{ Utils::GetDirectionFromOrientation(m_orientation).x, Utils::GetDirectionFromOrientation(m_orientation).y, 0 };
	m_map.DrawLineBetweenPoints(begin, begin + end, sc2::Colors::Purple);
}

void BaseLocation::FindBasePosition()
{
	// move cc according to orientation
}