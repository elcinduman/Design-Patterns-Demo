#include <iostream>
#include "mediator.h"
#include "NPCFactory.h"
#include "interpreter.h"
#include "command.h"
#include "observer.h"

int main()
{

	std::cout << "MEDIATOR PATTERN " << std::endl;

	NavigationManager* nm = new NavigationManager();
	WeaponsManager* wm = new WeaponsManager();
	TargetManager* tm = new TargetManager();
	DegradationManager* dm = new DegradationManager();
	TeamManager* tm2 = new TeamManager();
	CooperativeMediator* mediator = new CooperativeMediator(nm, wm, tm, dm, tm2);

	std::cout << "Triggering Navigation Managers operation.\n" << std::endl;
	nm->setDestination("Ankara");
	std::cout << "\n";
	std::cout << "Triggering Weapon Managers operation.\n" << std::endl;
	wm->addWeapon("Gun");
	wm->addWeapon("Fork");

	std::cout << "Triggering Target Managers operation.\n" << std::endl;
	tm->target = "Target1";
	tm->update();

	//std::cout << "Triggering Team Managers operation.\n" << std::endl;
	//tm2->setTeam("Helper");

	std::cout << "Triggering the Degradation Manager.\n" << std::endl;
	dm->health = 10;
	dm->update();
	//std::cout << "Triggering Degredation operation.\n" << std::endl; 
	std::cout << "----*-----" << std::endl;

	std::cout << "ABSTRACT FACTORY PATTERN" << std::endl;

	makeNPCs npc_game;
	VillainNPCFactory factory;
	npc_game.createNPCs(&factory);

	std::cout << "----*------" << std::endl;

	GoodNPCFactory factory2;
	npc_game.createNPCs(&factory2);

	std::cout << "----*-----" << std::endl;

	std::cout << "INTERPRETER PATTERN" << std::endl;

	GoalActionParser* exp;
	Context context;

	LiteralExpression* act1 = new LiteralExpression("MOVE");
	LiteralExpression* act2 = new LiteralExpression("RUN");

	LiteralExpression* act3 = new LiteralExpression("ATTACK");
	LiteralExpression* act4 = new LiteralExpression("STOP");

	exp = new AndExpression(new OrExpression(act1, act3), new OrExpression(act4, act2));

	context.Assign(act1, false);
	context.Assign(act3, true);
	context.Assign(act2, true);
	context.Assign(act4, false);

	bool result = exp->interpret(context);

	std::cout << "Goal: (" << act1->getActions() << " or " << act3->getActions() << ")" <<
		" AND (" << act2->getActions() << " or " << act4->getActions() << ")" << std::endl;

	if (result == 1) {
		std::cout << "Result: " << act3->getActions() << " AND " << act2->getActions() << std::endl;
	}
	else {
		std::cout << "Result: " << act4->getActions() << std::endl;
	}

	//Another test case
	//Changing the interpretations. 

	LiteralExpression* act5 = new LiteralExpression("DO_NOTHING");
	LiteralExpression* act6 = new LiteralExpression("SAVE");

	context.Assign(act5, true);
	context.Assign(act5, true);

	GoalActionParser* replacement = exp->change("MOVE", *new AndExpression(act5, act6));

	result = exp->interpret(context);
	std::cout << result << std::endl;

	if (result == 1) {
		std::cout << "Result is: " << act5->getActions() << ", " << act6->getActions() << std::endl;
	}

	std::cout << "----*-----" << std::endl;

	std::cout << "COMMAND PATTERN" << std::endl;
	WorldModel* world_model = new WorldModel();
	Command* cmd1 = new ReadFactCommand();
	Command* cmd2 = new CreateFactCommand();
	Command* cmd3 = new QueryFactCommand();


	world_model->putCommand(cmd1);
	world_model->putCommand(cmd2);
	world_model->putCommand(cmd3);

	world_model->request("read");
	world_model->request("create");
	world_model->request("query");

	world_model->request("delete");
	world_model->request("action");
	world_model->request("something");

	world_model->removeCommand(cmd1);
	world_model->removeCommand(cmd2);
	world_model->removeCommand(cmd3);

	world_model->request("read");
	world_model->request("create");
	world_model->request("query");

	world_model->putCommand(cmd1);
	world_model->putCommand(cmd2);
	world_model->putCommand(cmd3);
	world_model->request("read");
	world_model->request("create");
	world_model->request("query");

	std::cout << "----*-----" << std::endl;
	std::cout << "OBSERVER PATTERN" << std::endl;

	GoalActionSubject* subject = new GoalActionSubject();
	GoalManager* goalObserver = new GoalManager(subject);
	ActionManager* actionObserver = new ActionManager(subject);

	subject->createGoalAction("ESCAPE", "RUN");
	//subject->createGoalAction("HIDE", "MOVE");

	subject->changeGoalAction("HIDE", "MOVE");
	delete goalObserver;
	subject->createGoalAction("DO NOTHING", "DO NOTHING");

	GoalManager* g2 = new GoalManager(subject);
	GoalManager* g3 = new GoalManager(subject);
	GoalManager* g4 = new GoalManager(subject);

	subject->createGoalAction("ATTACK", "MOVE");
}
