#include <iostream>
#include <string>
#include <list>

using namespace std;

class Mediator;
class Manager;
class NavigationManager;
class WeaponsManager;
class TargetManager;
class TeamManager;
class DegradationManager;

class Mediator { //Mediator
public:
	virtual void changed(Manager* mng) = 0;
};

class CooperativeMediator : public Mediator { //ConcreteMediator
public:

	CooperativeMediator() {

	}
	CooperativeMediator(NavigationManager* navManager,
		WeaponsManager* wepManager,
		TargetManager* tarManager,
		DegradationManager* degManager,
		TeamManager* teamManager);
	virtual void changed(Manager* mng) override;

private:
	NavigationManager* _navManager;
	WeaponsManager* _wepManager;
	TargetManager* _tarManager;
	DegradationManager* _degManager;
	TeamManager* _teamManager;
};

class Manager { //Collegue
public:
	string name;
	Manager() {

	}
	Manager(Mediator* med);
	void set_mediator(Mediator* med);
	virtual void update(); //it should call the notify object. 
private:
	Mediator* _mediator;
};

class NavigationManager : public Manager {
public:
	NavigationManager() {
		this->name = "Navigation";
	}
	string destination;
	void setDestination(string str);
	string getPath();
};

class WeaponsManager : public Manager {
public:
	WeaponsManager() {
		this->name = "Weapons";
	}
	void addWeapon(string weapon);
	string getBestWeapon();
	void useWeapon();
private:
	list<string> _weapons;
};

class TargetManager : public Manager {
public:
	TargetManager() {
		this->name = "Target";
	}
	string target;
	string getTarget();
};

class DegradationManager : public Manager {
public:
	DegradationManager() {
		this->name = "Degredation";
	}
	int health;
};

class TeamManager : public Manager {
public:
	TeamManager() {
		this->name = "Team";
	}
	string teamRole;
	void setTeam(string team);
};