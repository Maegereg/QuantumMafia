#ifndef MAFIAGAME_HPP_INCLUDED
#define MAFIAGAME_HPP_INCLUDED

#include <vector>
#include "Player.hpp"
#include "Role.hpp"

using namespace std;

struct RoleAssignment{
	Player* player;
	Role* role;
};

/*
	Contains the logic to run a classical game of Mafia. Takes a list of players and roles,
	resolves the game up to a given phase, and returns who's dead and who's alive. Also 
	checks for validity, to make sure all actions are legal.
*/
class MafiaGame{
protected:
	vector<RoleAssignment> players;
	vector<int> executions;
	int phaseNum;

	/*
		Resolves a given night
		Returns false if the game is not valid at this point
	*/
	bool resolveNight(int nightPhase);

public:
	/*
		Accepts a list of players and roles paired, and a list of execution targets.
		Each execution target indicates the index of the role list of the execution 
		target.
		In general, the order of the players should be the same as in every other case
	*/
	MafiaGame(vector<RoleAssignment> playersAndRoles, vector<int> executions);
	/*
		Returns a list of true/false values for each player indicating if the player
		is alive after the given phase.
		Returns an empty vector if the game is invalid
	*/
	vector<bool> resolveToPhase(int phase);
};

#endif