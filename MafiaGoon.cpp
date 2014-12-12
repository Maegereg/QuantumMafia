#include "MafiaGoon.hpp"

MafiaGoon::MafiaGoon(int rank){
	factionRank = rank;

	roleName = "Mafia Goon";
	actionPriority = 100;
	actionType = "kill";

	faction = "Mafia";
	guilty = true;
}

//Currently only prevents players from targeting faction members if they are making the kill
//Also not allowed to kill players already dead
bool MafiaGoon::validateAction(Role *target, int phaseNumber){
	if (factionRank == 0){
		if (target->faction == faction || target->phaseKilled >=0){
			return false;
		}
	}
	return true;
}
void MafiaGoon::performAction(Role *target, int phaseNumber){
	target->phaseKilled = phaseNumber;
}


std::string MafiaGoon::getResult(Role *target){
	return "";
}

//Make sure that someone takes leadership
void MafiaGoon::onDeath(std::vector<Role*> playerList){
	for (int i = 0; i<playerList.size(); ++i){
		if (playerList[i]->faction == faction && playerList[i]->phaseKilled < 0)
		{
			--(((MafiaGoon*)playerList[i])->factionRank);
		}
	}
}