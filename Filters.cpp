#include "Filters.h"

bool Filters::resourceFilter(const sc2::Unit &u) {
	return u.unit_type.ToType() == sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD
		|| u.unit_type.ToType() == sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD750
		|| u.unit_type.ToType() == sc2::UNIT_TYPEID::NEUTRAL_VESPENEGEYSER;
};
