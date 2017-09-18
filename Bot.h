#pragma once
#include <sc2api\sc2_api.h>

#include "GameMap.h"

using sc2::Agent;

class Bot : public Agent {

	GameMap m_map;

public:
	Bot();
	virtual void OnGameStart() final;
};

