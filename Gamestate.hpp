#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED
#include <string>
#include <vector>

class Player;
class Role;

class Gamestate{
protected:
	std::vector<Player*> players;
	std::vector<Role*> roles;
	int phaseNumber;

	std::vector<std::string>* getRoleTypes();
	std::vector<std::string>* getFactions();

public:
	Gamestate(std::vector<std::string> playerNames, std::vector<Role*> roles);
	Gamestate(std::vector<std::string> playerNames, std::vector<Role*> roles, int phaseNum);

	int getNumPlayers();
};


#endif