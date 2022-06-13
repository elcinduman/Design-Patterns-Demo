#include "command.h"

using namespace std;

void WorldModel::putCommand(Command* commands) {
	_commands.push_back(commands);
}

void WorldModel::removeCommand(Command* commands) {
	_commands.remove(commands);
}

void WorldModel::request(string data) {
	list<Command*>::iterator itr;
	Command* ptr;
	int is_visited = 0;
	for (itr = _commands.begin(); itr != _commands.end(); itr++) {
		ptr = *itr;
		if (data == ptr->getName()) {
			ptr->execute();
			is_visited = 1;
		}
	}
	if (!is_visited) {
		std::cout << "Exception: Requested cannot be found." << std::endl;
	}
}

void ReadFactCommand::readFact() {
	std::cout << "Fact has been read." << std::endl;
}

string ReadFactCommand::getName() {
	return command_name;
}

void ReadFactCommand::execute() {
	if (command_name == "read") {
		readFact();
	}
}

void QueryFactCommand::queryFact() {
	std::cout << "Fact has been queried." << std::endl;
}

string QueryFactCommand::getName() {
	return command_name;
}

void QueryFactCommand::execute() {
	if (command_name == "query") {
		queryFact();
	}
}

string CreateFactCommand::getName() {
	return command_name;
}

void CreateFactCommand::createFact() {
	std::cout << "Fact has been created." << std::endl;
}

void CreateFactCommand::execute() {
	if (command_name == "create") {
		createFact();
	}
}