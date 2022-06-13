#include "observer.h"

using namespace std;

void Subject::attach(Observer* obs) {
	_observers.push_back(obs);
}
void Subject::detach(Observer* obs) {
	_observers.remove(obs);
}

void Subject::notify() {
	list<Observer*>::iterator itr;
	Observer* ptr;
	for (itr = _observers.begin(); itr != _observers.end(); itr++) {
		ptr = *itr;
		ptr->update(this);
	}
}

void GoalActionSubject::createGoalAction(std::string goal, std::string action) {
	this->goal = goal;
	this->action = action;
	notify();
}

void GoalActionSubject::changeGoalAction(std::string goal, std::string action) {
	this->goal = goal;
	this->action = action;
	notify();
	std::cout << "Goal and actions are now changed." << std::endl;
}

std::string GoalActionSubject::getGoalsActions() {
	std::string st = "Goal is: " + goal + "\nAction is: " + action;
	return st;
}

GoalManager::GoalManager(GoalActionSubject* sub) {
	_subject = sub;
	_subject->attach(this);
}

GoalManager::~GoalManager() {
	_subject->detach(this);
}

void GoalManager::printInformation() {
	std::cout << "Goal and action set has been changed for the Goal Manager." << std::endl;
	std::string str = _subject->getGoalsActions();
	std::cout << str << std::endl;
}

void GoalManager::update(Subject* sub) {
	sub = _subject;
	printInformation();
}


ActionManager::ActionManager(GoalActionSubject* sub) {
	_subject = sub;
	_subject->attach(this);
}

ActionManager::~ActionManager() {
	_subject->detach(this);
}

void ActionManager::update(Subject* sub) {
	sub = _subject;
	printInformation();
}

void ActionManager::printInformation() {
	std::cout << "Goal and action set has been changed for the Action Manager." << std::endl;
	std::string str = _subject->getGoalsActions();
	std::cout << str << std::endl;
}
