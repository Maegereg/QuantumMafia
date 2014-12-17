#include <iostream>
#include "Gamestate.hpp"
#include "Player.hpp"
#include "Role.hpp"

Gamestate::Gamestate(vector<string> playerNames, vector<Role*> gameRoles, int phaseNum/* = 0 */){
	for (int i = 0; i<playerNames.size(); ++i){
		players.push_back(new Player(playerNames[i]));
	}
	phaseNumber = phaseNum;
	roles = gameRoles;

	deathCounts = new int*[players.size()];
	roleCounts = new int*[players.size()];
	//Initialization leads to appropriate initial probabilities - equal chance of all roles, 100% alive
	for (int i = 0; i<players.size(); ++i){
		deathCounts[i] = new int[2] {1, 0};
		roleCounts[i] = new int[roles.size()];
		for (int j = 0; j<roles.size(); ++j){
			roleCounts[i][j] = 1;
		}
	}

	initializeFactionList();
}

vector<string> Gamestate::getRoleTypes(){
	vector<string> roleTypes;
	for (int i = 0; i<roles.size(); ++i){
		//Linear search on a list will be slow, but the list will be small
		if(find(roleTypes.begin(), roleTypes.end(), roles[i]->roleName) != roleTypes.end()){
			roleTypes.push_back(roles[i]->roleName);
		}
	}
	return roleTypes;
}

void Gamestate::initializeFactionList(){
	for (int i = 0; i<roles.size(); ++i){
		//Linear search on a list will be slow, but the list will be small
		if(find(factionList.begin(), factionList.end(), roles[i]->faction) == factionList.end()){
			factionList.push_back(roles[i]->faction);
		}
	}
}

vector<string> Gamestate::getFactions(){
	return factionList;
}

int Gamestate::getNumPlayers(){
	return players.size();
}

vector<string> Gamestate::getPlayerNames(){
	vector<string> playerNames;
	for (int i = 0; i<players.size(); ++i){
		playerNames.push_back(players[i]->playerName);
	}
	return playerNames;
}

float* Gamestate::getStandardStatistics(int playerNum){
	float* toReturn = new float[factionList.size()+1];
	float totalStates = 0;
	for (int i = 0; i<roles.size(); ++i){
		totalStates = totalStates + roleCounts[playerNum][i];
		for (int j = 0; j<factionList.size(); ++j){
			if (factionList[j] == roles[i]->faction){
				toReturn[j] = toReturn[j]+roleCounts[playerNum][i];
			}
		}

	}
	for (int i = 0; i<factionList.size(); ++i)
	{
		toReturn[i] = toReturn[i]/totalStates;
	}
	toReturn[factionList.size()] = deathCounts[playerNum][0] / (deathCounts[playerNum][0]+deathCounts[playerNum][1]);
	return toReturn;
}


