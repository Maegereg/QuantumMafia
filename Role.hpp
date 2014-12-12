#ifndef ROLE_HPP_INCLUDED
#define ROLE_HPP_INCLUDED
#include <string>

class Role{
protected:
	std::string roleName;
	int actionPriority;
	std::string actionType;

	std::string faction;
	bool guilty;

	int phaseKilled;
	bool roleblocked;
	bool protection;

public:
	Role();

	virtual bool validateAction(Role *target) = 0;
	virtual void performAction(Role *target) = 0;
	virtual std::string getResult(Role *target) = 0;
	bool isGuilty();
	std::string getName();
	std::string getFaction();
	std::string getActionType();
	int getActionPriotiy();
	int getPhaseKilled();
	bool isProtected();
	bool isRoleBlocked();
};

#endif