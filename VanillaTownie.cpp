#include "VanillaTownie.hpp"

VanillaTownie::VanillaTownie() {
	roleName = "Vanilla Townie";
	actionPriority = -1;
	actionType = "";

	faction = "Town";
	guilty = false;
}

bool VanillaTownie::validateAction(Role *target, int phaseNumber){
	return true;
}

void VanillaTownie::performAction(Role *target, int phaseNumber){
	return;
}
	
std::string VanillaTownie::getResult(Role *target){
	return "";
}

void VanillaTownie::onDeath(std::vector<Role> playerList){
	return;
}