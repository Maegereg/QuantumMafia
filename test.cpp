#include <iostream>
#include <vector>
#include "Gamestate.hpp"
#include "Role.hpp"
#include "VanillaTownie.hpp"
#include "MafiaGoon.hpp"
#include "RoleFactory.hpp"

int main(int argc, char** argv){
	std::vector<Role*> roles;
	roles.push_back((RoleFactory::Instance()->constructRole("Vanilla Townie")));
	roles.push_back(new MafiaGoon(0));
	std::vector<std::string> playerNames;
	playerNames.push_back("Alice");
	playerNames.push_back("Bob");
	Gamestate state(playerNames, roles);

	float* aliceStatistics = state.getStandardStatistics(0);
	cout << aliceStatistics[0];
	cout <<"\n";
	cout << aliceStatistics[1];
	cout <<"\n";
	cout << aliceStatistics[2];
	cout <<"\n";
}