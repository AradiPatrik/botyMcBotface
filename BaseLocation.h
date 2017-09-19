#pragma once
#include <vector>
#include <sc2api\sc2_api.h>

using namespace std;
using namespace sc2;

class BaseLocation {
	Units m_resources;
	Point3D m_centerOfResources;
	void FindCenterOfResources();
public:
	BaseLocation(const Units &);
	const Point3D Center() const;
};
