#include "Bot.h"
#include <iostream>
#include "Utils.h"

Bot::Bot()
	: m_map(*this) {}

void Bot::OnGameStart() {
	m_map.OnStart();
}

void Bot::OnUnitIdle(const sc2::Unit &unit) {}

void Bot::OnStep() {}