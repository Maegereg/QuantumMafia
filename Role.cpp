#include "Role.hpp"

Role::Role() {
	phaseKilled = -1;
	roleblocked = false;
	protection = false;
}

bool Role::isGuilty() {return guilty;}

std::string Role::getName() {return roleName;}

std::string Role::getFaction() {return faction;}

std::string Role::getActionType() {return actionType;}

int Role::getActionPriotiy() {return actionPriority;}

int Role::getPhaseKilled() {return phaseKilled;}

bool Role::isProtected() {return protection;}

bool Role::isRoleBlocked() {return roleblocked;}