#include <sc2api/sc2_api.h>
#include <iostream>
#include <algorithm>

using namespace sc2;

class Bot : public Agent {

public:

	enum StartPosition {
		TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
	};

	virtual void OnGameStart() final {
		Point3D startLoc = Observation()->GetStartLocation();
		// Get all mineralfields in the map
		Units mineralFields = Observation()->GetUnits(Unit::Alliance::Neutral,
			[](const Unit& unit) {
			return unit.unit_type.ToType() == UNIT_TYPEID::NEUTRAL_MINERALFIELD
				|| unit.unit_type.ToType() == UNIT_TYPEID::NEUTRAL_MINERALFIELD750;
		}
		);

		// Get all mineralfields visible to the bot
		std::vector<Point2D> visibleMineralPositions;
		for (const auto& mineralField : mineralFields) {
			if (Observation()->GetVisibility(mineralField.pos) == Visibility::Visible) {
				visibleMineralPositions.push_back(mineralField.pos);
			}
		}

		// Get average position of visible mineralfields
		Point2D avgPosOfVisibleMinerals;
		for (const auto& point : visibleMineralPositions) {
			avgPosOfVisibleMinerals.x += point.x;
			avgPosOfVisibleMinerals.y += point.y;
		}
		avgPosOfVisibleMinerals.x /= visibleMineralPositions.size();
		avgPosOfVisibleMinerals.y /= visibleMineralPositions.size();

		std::cout << "CommandCenter at: [ " << startLoc.x << ", " << startLoc.y << " ]" << std::endl;
		std::cout << "avgPosOfVisibleMinerals: [ " <<
			avgPosOfVisibleMinerals.x << ", " << avgPosOfVisibleMinerals.y << " ]" << std::endl;

		// Determine where we are
		if (avgPosOfVisibleMinerals.x < startLoc.x) {
			startPosition = avgPosOfVisibleMinerals.y > startLoc.y ?
				StartPosition::TOP_LEFT : StartPosition::TOP_RIGHT;
		} else {
			startPosition = avgPosOfVisibleMinerals.y > startLoc.y ?
				StartPosition::BOTTOM_LEFT : StartPosition::BOTTOM_RIGHT;
		}

		int supplyBuildingScvNum = GetWorkersConstructingBuilding(ABILITY_ID::BUILD_SUPPLYDEPOT).size();
		std::cout << GetFreeScvs().size() << std::endl;
	}

	virtual void OnUnitIdle(const Unit& unit) final {
		switch (unit.unit_type.ToType()) {
			case UNIT_TYPEID::TERRAN_COMMANDCENTER:
			{
				Actions()->UnitCommand(unit.tag, ABILITY_ID::TRAIN_SCV);
			}
		}
	}

	virtual void OnStep() final {
		// TOOD: build supplyDepot if appropriet
		int supplyBuildingScvNum = GetWorkersConstructingBuilding(ABILITY_ID::BUILD_SUPPLYDEPOT).size();
		if (supplyBuildingScvNum < 1 && Observation()->GetMinerals() > 100) {
			if (GetFreeScvs().size() > 0)
				ConstructBuilding(GetFreeScvs()[0], ABILITY_ID::BUILD_SUPPLYDEPOT);
			else
				std::cerr << "There are no scvs to build with" << std::endl;
		}
	}

private:

	//! Find the best spot for construction, than build a supplyDepot
	void ConstructBuilding(const Unit& scv, ABILITY_ID buildingAbilityId) {
		Point3D constructionSpot = Observation()->GetStartLocation();
		while (!Query()->Placement(buildingAbilityId, constructionSpot)) {
			if (startPosition == TOP_LEFT || startPosition == TOP_RIGHT) {
				constructionSpot.y--;
			} else {
				constructionSpot.y++;
			}
		}
		Actions()->UnitCommand(scv.tag, buildingAbilityId, constructionSpot);
		// TODO: add padding around building
	}

	//! Get the buildings currently under construction
	Units GetBuildingsUnderConstruction(const Unit& building) {
		Units buildingsUnderConstruction = Observation()->GetUnits(Unit::Alliance::Ally,
			[&building](const Unit& u) {
			return (u.build_progress != 1.0 && u.unit_type == building.unit_type);
		}
		);
	}

	//! Get workers who are building a given structure
	Units GetWorkersConstructingBuilding(ABILITY_ID id) {
		return Observation()->GetUnits(Unit::Alliance::Self, [id](const Unit& u) {
			for (const auto& order : u.orders) {
				if (order.ability_id.ToType() == id) {
					return true;
				}
			}
			return false;
		});
	}

	//! Get scvs
	Units GetFreeScvs() {
		return Observation()->GetUnits(Unit::Alliance::Self, [](const Unit& u) {
			// TODO: check if scv is constructing
			return (u.unit_type.ToType() == UNIT_TYPEID::TERRAN_SCV);
		});
	}

	//! The position we started on
	StartPosition startPosition;
	int supplyDepotPadding = 2;
};

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