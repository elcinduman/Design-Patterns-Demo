#include <iostream>
#include <string>
#include <map>

using namespace std;
/*
	Forward decleration of classes.
*/
class GoalActionParser;
class LiteralExpression;
class Context;
class AndExpression;
class OrExpression;

class Context {
public:
	Context() {

	}
	bool Lookup(const char*) const;
	void Assign(LiteralExpression* exp, bool value);
private:
	map<char*, int> m1;
	map<char*, int>::iterator itr;
};

class GoalActionParser {
public:
	GoalActionParser() {

	}
	virtual bool interpret(Context& aContext) = 0;
	virtual GoalActionParser* change(const char* name, GoalActionParser& expr) = 0;
	virtual GoalActionParser* make_copy() const = 0;
	virtual char* getActions() = 0;
	virtual char* getGoals() = 0;
};

class LiteralExpression : public GoalActionParser {
public:
	LiteralExpression() {

	}
	LiteralExpression(const char* name);

	virtual bool interpret(Context& aContext);
	virtual GoalActionParser* change(const char* name, GoalActionParser& expr);
	virtual GoalActionParser* make_copy() const;
	virtual char* getActions();
	virtual char* getGoals();
private:
	char* _name;
};

class AndExpression : public GoalActionParser {
public:
	AndExpression() {

	}
	AndExpression(GoalActionParser* op1, GoalActionParser* op2);

	virtual bool interpret(Context& aContext);
	virtual GoalActionParser* change(const char* name, GoalActionParser& exp);
	virtual GoalActionParser* make_copy() const;
	virtual char* getActions();
	virtual char* getGoals();
private:
	GoalActionParser* _operand1;
	GoalActionParser* _operand2;
};

class OrExpression : public GoalActionParser {
public:
	OrExpression() {

	}
	OrExpression(GoalActionParser* op1, GoalActionParser* op2);

	virtual bool interpret(Context& aContext);
	virtual GoalActionParser* change(const char* name, GoalActionParser& exp);
	virtual GoalActionParser* make_copy() const;
	virtual char* getActions();
	virtual char* getGoals();
private:
	GoalActionParser* _operand1;
	GoalActionParser* _operand2;
};
