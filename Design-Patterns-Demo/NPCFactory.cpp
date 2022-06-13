#include "NPCFactory.h"
#include <iostream>

NPCTemplate* makeNPCs::createNPCs(NPCFactory* factory)
{

	NPCTemplate* aNPC = factory->makeNPC();
	NPCLookTowards* look = factory->makeLookTowards();
	NPCPosition* pos1 = factory->makePosition(30, 10, 1);
	NPCAction* action = factory->makeAction(pos1);

	aNPC->setPosition(pos1);
	aNPC->performAction(pos1);
	aNPC->lookTowards(action, pos1);

	return aNPC;
}