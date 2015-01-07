#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED
#include <array>
#include <map>
#include <string>
#include <vector>
#include "Player.hpp"
using namespace std;

class Role;

class Gamestate{
protected:
	//The list of players in the game
	vector<Player*> players;
	//The list of roles in the game
	vector<Role*> roles;
	/*We will store roles that belong to players whose wavefunctions have collapsed seperately.
	There's no other way to tell them apart (other than cross-referencing with players), and 
	it makes it easier to assign uncollapsed players to roles in a permutation*/
	vector<Role*> uncollapsedRoles;
	int phaseNumber;

	//Each row corresponds to a player, each column to a role. Each entry is the number of quantum states currently in the game in which the given player has the given role.
	int** roleCounts;
	//Each row corresponds to a player. The first entry in each row is the number of quantum states in which the player is alive, the second dead.
	int** deathCounts;

	//The list of all factions in the game
	vector<string> factionList;

	void initializeFactionList();
	void clearCounts();

public:
	Gamestate(vector<string> playerNames, vector<Role*> roles, int phaseNum=0);

	//Returns a list of all roles in this game
	vector<string> getRoleTypes();
	//Returns a list of all factions in this game
	vector<string> getFactions();
	int getNumPlayers();
	//Returns a list of the names of players, in order (i.e., player 0's name is at index 0, etc)
	vector<string> getPlayerNames();
	//Returns an array of values for the given player. 
	//The last value is the probability that the player is alive.
	//The first n values represent the probability that the player is a member of each of the factions, in the same order as returned by getFactions.
	float* getStandardStatistics(int playerNum);

	//Performs phase resolution until the internal state is up to date
	void resolveToCurrentPhase();

	//What it says on the tin. Phase should be even, because even phases are nights
	void submitActionsForPlayer(int playerNum, int phase, map<string, int> actions);

	//Returns the new phase number
	int advancePhase();
};


#endif