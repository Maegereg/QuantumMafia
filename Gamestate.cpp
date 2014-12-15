#include <iostream>
#include "Gamestate.hpp"
#include "Player.hpp"
#include "Role.hpp"

Gamestate::Gamestate(std::vector<std::string> playerNames, std::vector<Role*> roles){
	for (int i = 0; i<playerNames.size(); ++i)
	{
		players.push_back(new Player(playerNames[i]));
	}
	phaseNumber = 0;
	roles = roles;
}

Gamestate::Gamestate(std::vector<std::string> playerNames, std::vector<Role*> roles, int phaseNum){
	for (int i = 0; i<playerNames.size(); ++i)
	{
		players.push_back(new Player(playerNames[i]));
	}
	phaseNumber = phaseNum;
	roles = roles;
}

//Returned vector needs to be freed later
std::vector<std::string>* Gamestate::getRoleTypes(){
	std::vector<std::string> *roleTypes = new std::vector<std::string>;
	for (int i = 0; i<roles.size(); ++i)
	{
		//Linear search on a list will be slow, but the list will be small
		if(std::find(roleTypes->begin(), roleTypes->end(), roles[i]->roleName) != roleTypes->end()){
			roleTypes->push_back(roles[i]->roleName);
		}
	}
	return roleTypes;
}

//Returned vector needs to be freed later
std::vector<std::string>* Gamestate::getFactions(){
	std::vector<std::string> *factions = new std::vector<std::string>;
	for (int i = 0; i<roles.size(); ++i)
	{
		//Linear search on a list will be slow, but the list will be small
		if(std::find(factions->begin(), factions->end(), roles[i]->faction) != factions->end()){
			factions->push_back(roles[i]->faction);
		}
	}
	return factions;
}

int Gamestate::getNumPlayers(){
	return players.size();
}