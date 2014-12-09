#ifndef ROLE_HPP_INCLUDED
#define ROLE_HPP_INCLUDED

class PlayerInstance;

class Role{
protected:
	string roleName;
	int actionPriority;
	string actionType;

	string faction;
	bool guilty;

public:

	virtual bool validateAction(PlayerInstance *target) = 0;
	virtual void performAction(PlayerInstance *target) = 0;
	virtual string getResult(PlayerInstance *target) = 0;
};

#include "PlayerInstance.hpp"

#endif