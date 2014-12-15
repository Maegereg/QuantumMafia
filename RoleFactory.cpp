#include "RoleFactory.hpp"

void RoleFactory::registerRole(std::string roleName, std::function<Role* (void)> roleConstructor){
	roleConstructors[roleName] = roleConstructor;
}

Role* RoleFactory::constructRole(std::string roleName){
	if (roleConstructors.count(roleName) > 0){
		return roleConstructors[roleName]();
	}
	return NULL;
}

RoleFactory* RoleFactory::Instance(){
	static RoleFactory factory;
	return &factory;
}


RoleRegistrar::RoleRegistrar(std::string className, std::function<Role* (void)> constructor){
	RoleFactory::Instance()->registerRole(className, constructor);
}