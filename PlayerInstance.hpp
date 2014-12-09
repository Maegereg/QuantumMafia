#ifndef PLAYERINSTANCE_HPP_INCLUDED
#define PLAYERINSTANCE_HPP_INCLUDED

class Role;

class PlayerInstance{
public:
	int nightKilled;
	bool roleBlocked;
	bool protected;
	*Role role;
};

#endif