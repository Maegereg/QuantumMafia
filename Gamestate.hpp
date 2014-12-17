#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED
#include <array>
#include <string>
#include <vector>
using namespace std;

class Player;
class Role;

class Gamestate{
protected:
	vector<Player*> players;
	vector<Role*> roles;
	int phaseNumber;

	//Each row corresponds to a player, each column to a role. Each entry is the number of quantum states currently in the game in which the given player has the given role.
	int** roleCounts;
	//Each row corresponds to a player. The first entry in each row is the number of quantum states in which the player is alive, the second dead.
	int** deathCounts;

	//The list of all factions in the game
	vector<string> factionList;

	void initializeFactionList();

public:
	Gamestate(vector<string> playerNames, vector<Role*> roles, int phaseNum=0);

	//Returns a list of all roles in this game
	vector<string> getRoleTypes();
	//Returns a list of all factions in this game
	vector<string> getFactions();
	int getNumPlayers();
	//Returns a list of the names of players, in order (i.e., player 0's name is at index 0, etc)
	vector<string> getPlayerNames();
	//Returns an array where each row corresponds to a player. 
	//The last column is the probability that the player is alive.
	//The first n columns represent the probability that the player is a member of each of the factions, in the same order as returned by getFactions.
	float* getStandardStatistics(int playerNum);
};


#endif