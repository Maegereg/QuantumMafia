#ifndef MAFIAGOON_HPP_INCLUDED
#define MAFIAGOON_HPP_INCLUDED
#include <string>
#include <vector>
#include "Role.hpp"

class MafiaGoon: public Role{
protected:
	//Determines the order of kills within the faction.
	//The player with faction rank 0 gets to pick the kill target
	//No garuantees are made about breaking ties in faction rank
	int factionRank;

public:
	MafiaGoon(int rank);

	bool validateAction(Role *target, int phaseNumber);
	void performAction(Role *target, int phaseNumber);
	std::string getResult(Role *target);
	void onDeath(std::vector<Role*> playerList);
};

#endif