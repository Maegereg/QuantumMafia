#include <iostream>
#include "Gamestate.hpp"
#include "Player.hpp"
#include "Role.hpp"

Gamestate::Gamestate(std::vector<std::string> playerNames){
	for (int i = 0; i<playerNames.size(); ++i)
	{
		players.push_back(Player(playerNames[i]));
	}
	phaseNumber = 0;
}