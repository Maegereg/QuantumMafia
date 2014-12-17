#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
#include <map>
#include <string>
#include <vector>
class Role;

class Player{
protected:

public:
	std::string playerName;
	//There are multiple possible actions for any given phase, so each phase has a dictionary of all possible action types and the action corresponding to them
	std::vector<std::map<std::string, int> > actions;

	//Set to true only when a player is completely dead
	bool dead;
	//Set only when a player's role wavefunction has collapsed
	Role *determinedRole;
	
	Player(std::string name);
};


#endif