#include <iostream>
#include <map>
#include <vector>
#include "Gamestate.hpp"
#include "Role.hpp"
#include "VanillaTownie.hpp"
#include "MafiaGoon.hpp"
#include "RoleFactory.hpp"

using namespace std;

int main(int argc, char** argv){
	vector<Role*> roles;
	roles.push_back((RoleFactory::Instance()->constructRole("Vanilla Townie")));
	roles.push_back(new MafiaGoon(0));
	vector<string> playerNames;
	playerNames.push_back("Alice");
	playerNames.push_back("Bob");
	Gamestate state(playerNames, roles);

	map<string, int> actions;
	actions["kill"] = 0;

	//Both players get the same actions
	state.submitActionsForPlayer(0, 0, actions);
	state.submitActionsForPlayer(1, 0, actions);

	state.advancePhase();
	state.resolveToCurrentPhase();

	float* aliceStatistics = state.getStandardStatistics(0);
	cout << aliceStatistics[0];
	cout <<"\n";
	cout << aliceStatistics[1];
	cout <<"\n";
	cout << aliceStatistics[2];
	cout <<"\n";
}