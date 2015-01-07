#include <algorithm>
#include <iostream>
#include <queue>
#include "Gamestate.hpp"
#include "MafiaGame.hpp"
#include "Role.hpp"

Gamestate::Gamestate(vector<string> playerNames, vector<Role*> gameRoles, int phaseNum/* = 0 */){
	//When we initialize an object, all players will start as undetermined
	for (int i = 0; i<playerNames.size(); ++i){
		players.push_back(new Player(playerNames[i]));
	}
	phaseNumber = phaseNum;
	//Similarly, all roles will start as undetermined
	roles = gameRoles;
	uncollapsedRoles = gameRoles;

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
	//Ensure that the array is 0-initialized
	for (int i = 0; i<factionList.size()+1; ++i){
		toReturn[i] = 0;
	}

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

//Clears the counts kept in roleCounts and deathCounts
void Gamestate::clearCounts(){
	for (int i = 0; i<players.size(); ++i){
		deathCounts[i][0] = 0;
		deathCounts[i][1] = 0;
		roleCounts[i] = new int[roles.size()];
		for (int j = 0; j<roles.size(); ++j){
			roleCounts[i][j] = 0;
		}
	}
}

void Gamestate::resolveToCurrentPhase(){
	vector<int> roleAssignment;

	clearCounts();

	for (int i = 0; i<uncollapsedRoles.size(); ++i){
		roleAssignment.push_back(i);
	}

	do{
		//Clear out all temporary data
		for (int i = 0; i<roles.size(); ++i){
			roles[i]->roleblocked = false;
			roles[i]->protection = false;
		}

		vector<RoleAssignment> currentRoleAssignments;

		int nextRoleToAssign = 0;
		for (int i = 0; i<players.size(); ++i){
			RoleAssignment toAdd;
			toAdd.player = players[i];
			if (toAdd.player->determinedRole == NULL){
				toAdd.role = uncollapsedRoles[roleAssignment[nextRoleToAssign]];
				++nextRoleToAssign;
			}
			else{
				toAdd.role = toAdd.player->determinedRole;
			}
			currentRoleAssignments.push_back(toAdd);
		}

		//TODO: Get this data from somewhere
		vector<int> executionTargets;

		MafiaGame gameLogic = MafiaGame(currentRoleAssignments, executionTargets);\
		vector<bool> permutationResults = gameLogic.resolveToPhase(phaseNumber);
		//If the permutation is invalid, then we don't record statistics
		if (permutationResults.size() == 0){
			continue;
		}

		//Add the results of the current permutation to the statistics
		nextRoleToAssign = 0;
		for (int i = 0; i<currentRoleAssignments.size(); ++i){
			if (players[i] ->determinedRole == NULL){
				++roleCounts[i][roleAssignment[nextRoleToAssign]];
				++nextRoleToAssign;
			}
			else
			{
				int roleIndex = 0;
				while (roles[roleIndex] != players[i]->determinedRole){
					++roleIndex;
				}
				++roleCounts[i][roleIndex];
			}

			if (permutationResults[i]){
				++deathCounts[i][0];
			}
			else{
				++deathCounts[i][1];
			}
		}

	} while (next_permutation(roleAssignment.begin(), roleAssignment.end()));
}

void Gamestate::submitActionsForPlayer(int playerNum, int phase, map<string, int> actions){
	if (phase <= players[playerNum]->actions.size()){
		players[playerNum]->actions.resize(phase+1);
	}
	players[playerNum]->actions[phase] = actions;
}


int Gamestate::advancePhase(){
	return ++phaseNumber;
}

