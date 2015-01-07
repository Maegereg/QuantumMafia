#include <queue>
#include "MafiaGame.hpp"

MafiaGame::MafiaGame(vector<RoleAssignment> players, vector<int> executions){
	this->players = players;
	this->executions = executions;
	phaseNum = 0;
}

vector<bool> MafiaGame::resolveToPhase(int phase){
	while (phaseNum < phase){
		if (phaseNum%2 == 0){
			if (!resolveNight(phaseNum)){
				return vector<bool>();
			}
		}
		else{
			//Resolve day
		}
		++phaseNum;
	}

	vector<bool> lifeStatus;
	for (int i = 0; i< players.size(); ++i){
		lifeStatus.push_back(players[i].role->phaseKilled < 0);
	}
	return lifeStatus;
}

class CompareRoleAssignment{
	public:
	bool operator()(RoleAssignment& r1, RoleAssignment& r2){
		return r1.role->actionPriority > r1.role->actionPriority;
	}
};

bool MafiaGame::resolveNight(int nightPhase){
	//Set up a priority queue of roles sorted by increasing action priority
	priority_queue<RoleAssignment, vector<RoleAssignment>, CompareRoleAssignment> roleOrder;

	for (int i = 0; i<players.size(); ++i){
		roleOrder.push(players[i]);
	}

	//Perform all night actions in order of increasing priority
	while (!roleOrder.empty()){
		RoleAssignment nextRole = roleOrder.top();
		roleOrder.pop();
		//Dead players don't get actions
		if (nextRole.role->phaseKilled < 0 ){
			Role* target =  players[nextRole.player->actions[nightPhase][nextRole.role->actionType]].role ;
			//If invalid, we return false
			if (!nextRole.role->validateAction(target, nightPhase)){
				return false;
			}
			nextRole.role->performAction(target, nightPhase);
		}
	}
	return true;
}