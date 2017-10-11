#pragma once
#include <sc2api\sc2_api.h>

#include "GameMap.h"

class Bot : public sc2::Agent
{
	GameMap m_map;

public:
	Bot();
	virtual void OnGameStart() final;
	virtual void OnStep() final;
};
