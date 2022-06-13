#pragma once
//Positions determines the actions that will be made. 
#include <iostream>
#include <string>

enum class Actions {
	MOVE,
	ATTACK,
	HELP,
	STOP,
	DO_NOTHING,
	HARM,
};

class NPCPosition {
public:
	NPCPosition() {
		posX = 0;
		posY = 0;
		posZ = 0;
		setPosition(posX, posY, posZ);
	}
	NPCPosition(float x, float y, float z) {
		setPosition(x, y, z);
	}
	virtual float* getPosition() { return 0; }
private:
	float posX, posY, posZ;
	virtual void setPosition(float x, float y, float z) { }
};

class VillainNPCPosition : public NPCPosition {
public:
	VillainNPCPosition() {
		setPosition(0, 0, 0);
	}
	VillainNPCPosition(float x, float y, float z) {
		setPosition(x, y, z);
	}
	virtual float* getPosition() override {
		float arr[3] = { posX, posY, posZ };
		return arr;
	}
private:
	float posX, posY, posZ;
	virtual void setPosition(float x, float y, float z) override {
		posX = x;
		posY = y;
		posZ = z;
	}
};

class GoodNPCPosition : public NPCPosition {
public:
	GoodNPCPosition() {
		setPosition(0, 0, 0);
	}
	GoodNPCPosition(float x, float y, float z) {
		setPosition(x, y, z);
	}
	virtual float* getPosition() override {
		float arr[3] = { posX, posY, posZ };
		return arr;
	}
private:
	float posX, posY, posZ;
	virtual void setPosition(float x, float y, float z) override {
		posX = x;
		posY = y;
		posZ = z;
	}
};

/*
 * NPC Action object class.
 */

class NPCAction {
public:
	Actions acts;
	NPCAction() {}
	NPCAction(NPCPosition* pos) {
	}
	virtual int define_actions(NPCPosition* pos) {
		return 0;
	}
};

class VillainNPCAction : public NPCAction {
public:
	Actions acts;
	VillainNPCAction() {

	}
	VillainNPCAction(NPCPosition* pos) {
		define_actions(pos);
		if (acts == Actions::ATTACK) {
			std::cout << "Performed action is ATTACK. " << std::endl;

		}
		else {
			std::cout << "Performed action is HARM. " << std::endl;
		}
	}
	virtual int define_actions(NPCPosition* pos) {
		float* positions = pos->getPosition();
		if (positions[0] == 20) {
			acts = Actions::ATTACK;
			return 1;
		}
		else {
			acts = Actions::HARM;
			return 5;
		}
	}
};

class GoodNPCAction : public NPCAction {
public:
	Actions act;

	GoodNPCAction() {

	}
	GoodNPCAction(NPCPosition* pos) {
		define_actions(pos);
		if (acts == Actions::HELP) {
			std::cout << "Performed action is HELP. " << std::endl;

		}
		else {
			std::cout << "Performed action is DO NOTHING. " << std::endl;
		}
	}
	virtual int define_actions(NPCPosition* pos) {
		float* positions = pos->getPosition();
		if (positions[0] == 20) {
			acts = Actions::HELP;
			return 3;
		}
		else {
			acts = Actions::DO_NOTHING;
			return 4;
		}
	}
};

/*
 * NPC Look Towards object class.
 */

class NPCLookTowards {
public:
	NPCLookTowards() {

	}
	NPCLookTowards(NPCAction* act, NPCPosition* pos) {
	}
};
class VillainNPCLookTowards : public NPCLookTowards {
public:
	VillainNPCLookTowards() {
		std::cout << "Initialized villain's look towards." << std::endl;
	}
	VillainNPCLookTowards(NPCAction* act, NPCPosition* pos) {

		int x = act->define_actions(pos);

		if (x == 2) {
			std::cout << ("Looking towards an attack.") << std::endl;
		}
		else {
			std::cout << "Looking towards a harm." << std::endl;
		}
	}
};
class GoodNPCLookTowards : public NPCLookTowards {
public:
	GoodNPCLookTowards() {
		std::cout << "Initialized good NPC's look towards." << std::endl;
	}
	GoodNPCLookTowards(NPCAction* act, NPCPosition* pos) {

		int x = act->define_actions(pos);

		if (x == 3) {
			std::cout << ("Looking towards a help.") << std::endl;
		}
		else {
			std::cout << "Nothing to look towards." << std::endl;
		}
	}
};

/*
 * NPC Template object class.
 */

class NPCTemplate {
public:
	NPCTemplate() {

	}
	virtual NPCPosition* setPosition(NPCPosition* p) {
		float* arr = p->getPosition();
		return new NPCPosition(arr[0], arr[1], arr[2]);
	}
	virtual NPCAction* performAction(NPCPosition* p) {
		return new NPCAction(p);
	}
	virtual NPCLookTowards* lookTowards(NPCAction* a, NPCPosition* p) {
		return new NPCLookTowards(a, p);
	}
};

class VillainNPCTemplate : public NPCTemplate {
public:
	VillainNPCTemplate() {

	}
	virtual NPCPosition* setPosition(NPCPosition* p) override {
		std::cout << "Positioned as the villain of the game." << std::endl;
		std::cout << "Coordinates are: " << p->getPosition()[0] << " " << p->getPosition()[1] << " " << p->getPosition()[2] << std::endl;
		return new VillainNPCPosition(p->getPosition()[0], p->getPosition()[1], p->getPosition()[2]);
	}
	virtual NPCAction* performAction(NPCPosition* p) override {
		return new VillainNPCAction(p);
	}
	virtual NPCLookTowards* lookTowards(NPCAction* a, NPCPosition* p) override {
		return new VillainNPCLookTowards(a, p);
	}
};

class GoodNPCTemplate : public NPCTemplate {
public:
	GoodNPCTemplate() {

	}
	virtual NPCPosition* setPosition(NPCPosition* p) override {
		float* arr = p->getPosition();
		std::cout << "Positioned as the good character of the game." << std::endl;
		std::cout << "Coordinates are: " << p->getPosition()[0] << " " << p->getPosition()[1] << " " << p->getPosition()[2] << std::endl;
		return new GoodNPCPosition(p->getPosition()[0], p->getPosition()[1], p->getPosition()[2]);
	}
	virtual NPCAction* performAction(NPCPosition* pos) override {
		return new GoodNPCAction(pos);
	}
	virtual NPCLookTowards* lookTowards(NPCAction* a, NPCPosition* p) override {
		return new GoodNPCLookTowards(a, p);
	}
};

/*
 * NPCFactory interface and factory classes.
 */

class NPCFactory {
public:
	virtual NPCTemplate* makeNPC() const {
		return new NPCTemplate;
	}
	virtual NPCPosition* makePosition(float x, float y, float z) const {
		return new NPCPosition(x, y, z);
	}
	virtual NPCAction* makeAction(NPCPosition* pos) {
		return new NPCAction(pos);
	}
	virtual NPCLookTowards* makeLookTowards() {
		return new NPCLookTowards();
	}
};

class VillainNPCFactory : public NPCFactory {
public:

	virtual VillainNPCTemplate* makeNPC() const override {
		return new VillainNPCTemplate;
	}
	virtual NPCPosition* makePosition(float x, float y, float z) const override {
		return new VillainNPCPosition(x, y, z);
	}
	virtual NPCAction* makeAction(NPCPosition* pos) override {
		return new VillainNPCAction(pos);
	}
	virtual NPCLookTowards* makeLookTowards() override {
		return new VillainNPCLookTowards;
	}
};

class GoodNPCFactory : public NPCFactory {
public:

	virtual GoodNPCTemplate* makeNPC() const override {
		return new GoodNPCTemplate;
	}
	virtual NPCPosition* makePosition(float x, float y, float z) const override {
		return new GoodNPCPosition(x, y, z);
	}
	virtual NPCAction* makeAction(NPCPosition* pos) override {
		return new GoodNPCAction(pos);
	}
	virtual NPCLookTowards* makeLookTowards() override {
		return new GoodNPCLookTowards;
	}
};

/*
 * This is for creating NPCs.
 */

class makeNPCs {
public:
	NPCTemplate* createNPCs(NPCFactory* factory);
};