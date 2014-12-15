#ifndef ROLEFACTORY_HPP_INCLUDED
#define ROLEFACTORY_HPP_INCLUDED
#include <map>
#include <string>

class Role;

class RoleFactory{
protected:
	std::map<std::string, std::function<Role* (void)> > roleConstructors;

public:
	void registerRole(std::string roleName, std::function<Role* (void)> constructor);
	Role* constructRole(std::string roleName);
	static RoleFactory* Instance();

};

class RoleRegistrar{
public:
	RoleRegistrar(std::string className, std::function<Role* (void)> constructor);
};

#endif