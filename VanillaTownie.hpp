#ifndef VANILLATOWNIE_HPP_INCLUDED
#define VANILLATOWNIE_HPP_INCLUDED
#include <string>
#include <vector>
#include "Role.hpp"

class VanillaTownie: public Role{
public:
	VanillaTownie();

	bool validateAction(Role *target, int phaseNumber);
	void performAction(Role *target, int phaseNumber);
	std::string getResult(Role *target);
	void onDeath(std::vector<Role*> playerList);
};

#endif