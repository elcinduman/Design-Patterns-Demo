#include "mediator.h"

CooperativeMediator::CooperativeMediator(NavigationManager* navManager, WeaponsManager* wepManager, TargetManager* tarManager, DegradationManager* degManager, TeamManager* teamManager) {
	//setting managers.
	_navManager = navManager;
	_wepManager = wepManager;
	_degManager = degManager;
	_tarManager = tarManager;
	_teamManager = teamManager;

	navManager->set_mediator(this);
	wepManager->set_mediator(this);
	tarManager->set_mediator(this);
	degManager->set_mediator(this);
	teamManager->set_mediator(this);
}

void CooperativeMediator::changed(Manager* mng) {

	std::cout << "Mediator is notified about the changes in " + mng->name << " Manager." << std::endl;

	if (mng->name == "Navigation") {
		_navManager->getPath();
	}
	if (mng->name == "Weapons") {
		std::cout << "Best weapon chosen as: " << _wepManager->getBestWeapon() << std::endl;
	}
	if (mng->name == "Target") {
		_tarManager->getTarget();

	}
	if (mng->name == "Degredation") {
		std::cout << "Health has been determined as " << _degManager->health << std::endl;
		std::cout << "Mediator notifies the Team Manager. " << std::endl;
		_teamManager->setTeam("Help for injured");
		std::cout << "Team role determined as: " << _teamManager->teamRole << std::endl;
	}
	if (mng->name == "Team") {
		std::cout << "Team role determined as: " << _teamManager->teamRole << std::endl;
	}
}


Manager::Manager(Mediator* med) {
	this->set_mediator(med);
}

void Manager::set_mediator(Mediator* med) {
	this->_mediator = med;
}

void Manager::update() {
	_mediator->changed(this);
}
/*
* Navigation Manager codes.
*/

void NavigationManager::setDestination(string str) {
	this->destination = str;
	std::cout << "Destination has been set as " << destination << std::endl;
	this->update();
}

string NavigationManager::getPath() {
	string str = "Path has been determined for " + destination;
	return str;
}

/*
* Target Manager
*/

string TargetManager::getTarget() {
	return target;
}

/*
* Team Manager
*/

void TeamManager::setTeam(string team) {
	this->teamRole = team;
	std::cout << "Team has been set as " << team << " ." << std::endl;
	this->update();
}

/*
* Weapon Manager
*/

void WeaponsManager::addWeapon(string weapon) {
	this->_weapons.push_back(weapon);
	std::cout << "Weapon has been added to the system." << std::endl;
	this->update();
}

string WeaponsManager::getBestWeapon() { //returns the first element of the weapons array.
	return this->_weapons.front();
}

void WeaponsManager::useWeapon() {
	std::cout << "Selected weapon has been used." << std::endl;
	this->update();
}