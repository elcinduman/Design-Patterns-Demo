#include "interpreter.h"
using namespace std;

bool Context::Lookup(const char* name) const
{
	map<char*, int> m2(m1.begin(), m1.end());
	map<char*, int>::iterator itr;
	for (itr = m2.begin(); itr != m2.end(); itr++) {
		if (strcmp(itr->first, name) == 0) {
			return itr->second;
		}
	}
	return false;
}

void Context::Assign(LiteralExpression* exp, bool value) {
	char* name = exp->getActions();
	m1[name] = value;
}


LiteralExpression::LiteralExpression(const char* name) {
	_name = _strdup(name);
}

bool LiteralExpression::interpret(Context& aContext) {
	return aContext.Lookup(_name);
}

GoalActionParser* LiteralExpression::make_copy() const {
	return new LiteralExpression(_name);
}

char* LiteralExpression::getActions()
{
	return _name;
}

char* LiteralExpression::getGoals()
{
	return _name;
}

GoalActionParser* LiteralExpression::change(const char* name, GoalActionParser& expr) {

	if (strcmp(name, _name) == 0) {
		return expr.make_copy();
	}
	else {
		return new LiteralExpression(_name);
	}
}

/*
* Operations of AND.
*/
AndExpression::AndExpression(GoalActionParser* op1, GoalActionParser* op2) {
	_operand1 = op1;
	_operand2 = op2;
}

bool AndExpression::interpret(Context& aContext) {
	return _operand1->interpret(aContext) && _operand2->interpret(aContext);
}

GoalActionParser* AndExpression::make_copy() const {
	return new AndExpression(_operand1->make_copy(), _operand2->make_copy());
}

char* AndExpression::getActions()
{
	return nullptr;
}

char* AndExpression::getGoals() {
	return nullptr;
}

GoalActionParser* AndExpression::change(const char* name, GoalActionParser& exp) {
	return new AndExpression(_operand1->change(name, exp), _operand2->change(name, exp));
}

/*
* Operations of OR.
*/

OrExpression::OrExpression(GoalActionParser* op1, GoalActionParser* op2) {
	_operand1 = op1;
	_operand2 = op2;
}

bool OrExpression::interpret(Context& aContext) {
	return _operand1->interpret(aContext) || _operand2->interpret(aContext);
}

GoalActionParser* OrExpression::make_copy() const {
	return new OrExpression(_operand1->make_copy(), _operand2->make_copy());
}

char* OrExpression::getActions() {
	return nullptr;
}

char* OrExpression::getGoals() {
	return nullptr;
}

GoalActionParser* OrExpression::change(const char* name, GoalActionParser& exp) {
	return new OrExpression(_operand1->change(name, exp), _operand2->change(name, exp));
}