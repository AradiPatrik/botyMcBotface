#include "Filters.h"

bool Filters::isResource(const sc2::Unit &u) {
	return isMineral(u) || isGeiser(u);
};

bool Filters::isMineral(const sc2::Unit &u) {
	return u.unit_type.ToType() == sc2::UNIT_TYPEID::NEUTRAL_LABMINERALFIELD
		|| u.unit_type.ToType() == sc2::UNIT_TYPEID::NEUTRAL_LABMINERALFIELD750
		|| u.unit_type.ToType() == sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD
		|| u.unit_type.ToType() == sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD750
		|| u.unit_type.ToType() == sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD
		|| u.unit_type.ToType() == sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD750;
}

bool Filters::isGeiser(const sc2::Unit &u) {
	return u.unit_type.ToType() == sc2::UNIT_TYPEID::NEUTRAL_VESPENEGEYSER;
}