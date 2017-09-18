#include "Bot.h"

Bot::Bot()
	: m_map(*this)
{}

void Bot::OnGameStart() {
	m_map.OnStart();
}
