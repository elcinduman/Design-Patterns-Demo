#include <iostream>
#include <string>
#include <list>

using namespace std;

class Command;
class ReadFactCommand;

class Command { // pure virtual interface for commands. 
public:
	Command() {
		command_name = "command";
	}
	virtual void execute() = 0;
	virtual string getName() {
		return command_name;
	}
private:
	string command_name;
};

class WorldModel {
public:
	WorldModel() {

	}
	void putCommand(Command*);
	void removeCommand(Command*);
	void request(string data); //request the string
private:
	list<Command*> _commands;
};

class ReadFactCommand : public Command {
public:
	ReadFactCommand() {
		command_name = "read";
	}
	virtual void execute() override;
	virtual string getName() override;
private:
	void readFact();
	string command_name;
};

class QueryFactCommand : public Command {
public:
	QueryFactCommand() {
		command_name = "query";
	}
	virtual void execute() override;
	virtual string getName() override;
private:
	void queryFact();
	string command_name;
};

class CreateFactCommand : public Command {
public:
	CreateFactCommand() {
		command_name = "create";
	}
	virtual void execute() override;
	virtual string getName() override;
private:
	void createFact();
	string command_name;
};