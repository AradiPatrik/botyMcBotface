#pragma once
#include <sc2api\sc2_api.h>

namespace Predicates
{
	bool isResource(const sc2::Unit &unit);
	bool isMineral(const sc2::Unit &unit);
	bool isGeiser(const sc2::Unit &unit);
}