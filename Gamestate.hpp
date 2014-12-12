#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED
#include <string>
#include <vector>

class Player;
class Role;

class Gamestate{
protected:
	std::vector<Player> players;
	std::vector<Role> roles;
	int phaseNumber;

public:
	Gamestate(std::vector<std::string> playerNames);
	Gamestate(std::vector<std::string> playerNames, int phaseNum);
};


#endif