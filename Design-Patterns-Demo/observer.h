#include <iostream>
#include <list>
#include <string>

using namespace std;

class Observer;
class Subject;
class GoalActionSubject;
class GoalManager;
class ActionManager;

class Observer {
public:
	Observer() {

	}
	virtual void update(Subject* changedSubject) = 0;
};

class Subject {
public:
	Subject() {

	}
	virtual void attach(Observer* obs);
	virtual void detach(Observer* obs);
	virtual void notify();
private:
	list<Observer*> _observers;
};

class GoalActionSubject : public Subject {
public:
	GoalActionSubject() {

	}
	void createGoalAction(std::string goal, std::string action);
	void changeGoalAction(std::string goal, std::string action);
	std::string getGoalsActions();
private:
	std::string goal;
	std::string action;
};

class GoalManager : public Observer {
public:
	GoalManager(GoalActionSubject* sub);
	~GoalManager();
	virtual void update(Subject* changedSubject) override;
	void printInformation();
private:
	GoalActionSubject* _subject;
};

class ActionManager : public Observer {
public:
	ActionManager(GoalActionSubject* sub);
	~ActionManager();
	virtual void update(Subject* changedSubject) override;
	void printInformation();
private:
	GoalActionSubject* _subject;
};
