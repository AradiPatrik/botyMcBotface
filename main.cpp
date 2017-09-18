#include <sc2api/sc2_api.h>
#include <iostream>
#include <algorithm>
#include "Bot.h"

using namespace sc2;

int main(int argc, char* argv[]) {
	Coordinator coordinator;
	coordinator.LoadSettings(argc, argv);

	Bot bot;
	coordinator.SetParticipants({
		CreateParticipant(Race::Terran, &bot),
		CreateComputer(Race::Zerg)
	});

	coordinator.LaunchStarcraft();
	coordinator.StartGame(sc2::kMapBelShirVestigeLE);


	while (coordinator.Update()) {

	}

	return 0;
}