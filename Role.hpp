#ifndef ROLE_HPP_INCLUDED
#define ROLE_HPP_INCLUDED
#include "RoleFactory.hpp"
#include <string>
#include <vector>

class Role{
public:
	std::string roleName;
	//ActionPriority determines the order in which night actions are resolved
	//Allowed values are >=0. The higher the value, the later in the order the action will go
	//Negative values indicate no night action
	int actionPriority;
	std::string actionType;

	std::string faction;
	bool guilty;

	int phaseKilled;
	bool roleblocked;
	bool protection;

	Role();

	virtual bool validateAction(Role *target, int phaseNumber) = 0;
	virtual void performAction(Role *target, int phaseNumber) = 0;
	virtual std::string getResult(Role *target) = 0;
	virtual void onDeath(std::vector<Role*> gameRoles) = 0;
	bool isGuilty();
	std::string getName();
	std::string getFaction();
	std::string getActionType();
	int getActionPriority();
	int getPhaseKilled();
	bool isProtected();
	bool isRoleBlocked();
};

#endif