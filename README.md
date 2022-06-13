# Design Patterns Demo 

## Flexibility Requirements 
1)	Variety of Non Player Character (NPC) families should be produced by the AI component of the game.
The report that is given to us emphasizes a single type of NPC family in the whole war game. However, in war games there should be more than one type of NPC family since a variety of NPCs can be produced by AI algorithms. NPCs can advance the experience and enjoyment from the game. It can also be challenging to deal with multiple villains or harmful NPCs.
The war game must be able to produce multiple families of NPCs. These NPCs should be in different types such as good characters or bad characters. Some NPCs should be harmful while others must not harm our main character and their felonies. These NPCs should be generated inside of the Artificial Intelligence subdomain of the game. NPCs should be consistent with their actions, meaning that a good character should not harm or attack our main character.
2)	Goals and actions that are represented as a language should be interpreted by the Goal Oriented Action Planning (GOAP) controller.
In the report, it was stated that goals and actions of characters are stored inside of a Goal Action Database. GOAP controller reaches those datas via a parser. However, this solution all by itself is not suitable for our game since it is not mentioned how the parser works in our report. Interpretations of the languages are not clearly stated.
When a new scenario or a level is added to the system, it generates new actions and goals, however it is not mentioned how the system will work after we add new actions and goals. The interpretation of the languages should be flexible. When new levels and new scenarios are added to the game, the interpreter should work correctly with the newly added languages.
It is clear that we are in need of an interpreter which interprets the given language. There should be a class hierarchy for the grammar of actions and goals.
3)	Goal Oriented Action Planning (GOAP) controller should update goals and multiple actions when changes are made in the AI Module.
Goal Oriented Action Planning (GOAP) controller is a partitioned system that has cooperating classes. In the report that was given to us states that GOAP has Action Manager and Goal Manager classes that are dependent on the controllers updates. It is obvious that these classes should maintain consistency in order to work correctly and efficiently.
When the GOAP controller receives new information from the AI Module, we should notify our Action Manager and Goal Manager since new goals and actions will be determined by the notifications that the GOAP controller sends. In addition to all of these, the GOAP controller may have other Manager classes that manage actions and goals. Supporting broadcast communication is an important aspect for this requirement. By endorsing information exchanges with multiple classes we are able to make this requirement flexible.
4)	Coordination between Manager objects should be done effectively.
Coordination between the manager objects have an important effect on our game play. Manager classes are defined as Navigation, Weapon, Target, Degradation and Team. All of these stores the necessary information that determines the course of the game.
In the report, Managers are expected to be independent, meaning that they would not exchange information with each other. They would directly send information to the Blackboard. However in that case, blackboard does not support the information exchange between managers. Therefore, only information supported by the blackboard can be exchanged. Coordination problems may arise due to this design, since Manager objects may communicate with each other and exchange crucial information. Manager objects behaviors’ and coordinations should be separated from each other.
Information exchange and dependency problems must be solved in order to have an efficient game play. Manager objects should be coordinated accordingly. By doing so, we are expecting to have a flexible Manager system in our war game.
5)	The World Model should process different kinds of datas.
The World Model is initially responsible for reading, querying and creating facts. However, this model receives a variety of data from Sensors, Facts and Artificial Intelligence modules. The World Model should handle datas in order to update the world of the game. This model should concrete on requesting and receiving datas from multiple sources.

## Possible Design Patterns to Solve Requirements 

1)	Variety of Non Player Character (NPC) families should be produced within the AI subdomain of the game.
For the first requirement Abstract Factory, Factory Method and Prototype patterns are chosen as the candidate patterns to solve the requirement.
A variety of NPC families should be produced by the system. This can be done by the Abstract Factory or Factory Method since with the usage of these methods we are able to create related objects. However, the Factory Method does not provide the consistency that we need amongst the NPC families, therefore usage of Factory Method is not appropriate for our solution. Prototype pattern is also a creational design pattern that lets us copy existing objects with the clone method. In the prototype pattern, cloning complex objects which have circular references might be challenging. Initializing clones can be tricky when we want to initialize internal state values. In addition to all of these, managing prototypes can be difficult and we may have to use a prototype manager for this specific purpose.
Therefore, usage of Abstract Factory pattern should be eligible for this problem. Abstract factory provides consistency among NPCs and it also makes exchanging product families easy. Since we want to have more than one product family, we can use the Abstract Factory to provide flexibility for this requirement.
2)	Goals and actions that are represented as a language should be interpreted by the Goal Oriented Action Planning (GOAP) controller.
For the second requirement, Interpreter and State patterns are chosen as the candidate pattern to solve the requirement.
State pattern is a structural design pattern that aims to change the algorithm in run time. However, when using the State pattern adding new states can sometimes be hard and it can be challenging to implement a new state.
Interpreter pattern is a behavioral design pattern that interprets sentences in a given language. It is easy to change and extend the grammar because the pattern uses classes to represent grammar rules. Adding new ways to interpret expressions is also simple, since existing expressions can be modified incrementally. Implementation of the grammar is uncomplicated and it can be automated with a parser generator. As a result of that, usage of Interpreter pattern is suitable for handling the interpretations of actions and goals.
3)	Goals Oriented Action Planning (GOAP) controller should update goals and multiple actions when new changes are made in the AI module.
For the third requirement, Observer and Publisher-Subscriber patterns are selected as the candidate patterns to solve the requirement.
Publisher-Subscriber pattern can be implemented for this problem because it's a behavioral design pattern that is similar to Observer pattern. This pattern is mostly used in distributed systems since there can be many subscribers beyond our scope. In publisher-subscriber pattern, there may be a third component that filters all incoming updates and distributes accordingly. However, in our AI subdomain, the GOAP controller does not implement a distributed system and we do not need a third component that would filter the notifications of managers.
The Observer pattern is suitable for this kind of problem since the Observer pattern defines a one-to-many dependency between objects. When a state is changed, all the dependent objects are notified accordingly. In our situation, the GOAP controller should notify the Goal and Action Manager when an internal change is made in the AI module. These changes can affect goals and actions of players. In order to keep the game consistent, we should reflect changes in the manager classes, therefore, implementation of the Observer pattern is suitable for maintaining flexibility.
4)	Coordination between Manager objects should be done effectively.
In this problem, the Mediator and Facade design patterns are chosen as the candidate pattern to solve the requirement.
Facade is a structural design pattern that provides a unified interface to a set of interfaces in a subsystem. Facade makes the subsystem easier to use. However, Facade patterns protocol is unidirectional. Facade objects make requests of the subsystem classes but not vice versa [1]. It can constrain our Manager classes and how they interact with other objects, therefore, usage of the Facade pattern is not suitable for this requirement.
The Mediator is a behavioral design pattern that promotes loose coupling by keeping objects from referring to each other explicitly. Mediator enables cooperative behavior and the protocol is multidirectional. It makes object interactions independently. The Mediator pattern separates the coordination and the behavior of the object.
The Mediator pattern centralizes control. In our situation, implementing the Mediator pattern could fix the issue of dependency and communication problems between Managers. With the mediator, we may identify Manager objects independently and those objects can cooperate separately from each other. By coordinating manager objects our range of action can expand and the gameplay experience is more likely to be realistic.
5) The World Model should process different kinds of datas.
For this problem, Command pattern and Chain of Responsibility patterns are chosen as the candidate patterns to solve the requirement.
Chain of Responsibility is a behavioral pattern that handles the request by chaining objects. More than one object may handle a request and the handler does not know which object will handle the request. In our case, the Chain of Responsibility pattern is not suitable since there is only one method for handling the request. We could have more than one request at this point, since our game is a war game that has a dynamic structure. The World Model is always updated by sensors, artificial intelligence and fact modules, therefore, we may have more than one request at this point in the game. Receipt is also not guaranteed in this pattern.
The Command pattern can be implemented for solving this requirement. This pattern is a behavioral design pattern that supports multiple requests. Since this is a war game, we may have more than one request. In command pattern, each of the objects may perform different kinds of operations such as querying, reading or creating facts. By extending the World Models interface, we would no longer have a fixed interface problem.
In order to process different kinds of requests, the World Model should implement the Command pattern. By doing so, we would make the games world more flexible and attainable.

##	Problem Description
Five of the flexibility requirements are selected to solve. In this section, you can find the patterns suitable for each problem. This section also contains the information of the reason why we implemented these selected patterns. Static and dynamic class diagrams are also shown in the sections.
## Problem Definition
Variety of Non Player Character (NPC) families should be produced by the AI subdomain of the game.
The report that was given to us only contains one generic implementation of a NPC family. In our game, one type of NPC family is not enough since a war game should contain more than one type of NPC families in order to be successful and entertaining in the market. By implementing the abstract factory pattern, we are able to produce families of related objects without specifying their concrete classes.
### Static Class Structure
The diagrams that are created aims to check the accuracy and consistency of our solution with the usage of the Abstract Factory design pattern. C++ programming language is chosen as the implementer of the flexibility requirement.
![resim](https://user-images.githubusercontent.com/59923068/173421527-6ac3e5f1-aeec-4a2d-b93f-c84f782706f0.png)

The table above contains the UML class diagram for the Abstract Factory pattern that will be used to solve the problem. However, when implementing the Abstract Factory pattern, we should also show the product families and their hierarchies.

![resim](https://user-images.githubusercontent.com/59923068/173421602-25a338be-1c3c-4a70-9bb0-da30741e5294.png)
![resim](https://user-images.githubusercontent.com/59923068/173421618-70735d5a-0386-4367-ade3-6062f52e9a79.png)
![resim](https://user-images.githubusercontent.com/59923068/173421633-e7aed258-847e-4bc5-9478-ac7ae03940f0.png)
![resim](https://user-images.githubusercontent.com/59923068/173421655-48d79ef0-8332-46f3-b90a-a94e46a6b633.png)

Tables above contain the UML class diagrams for NPC Template, NPC Position, NPC Action and NPC Look Towards. These diagrams represent product hierarchies and families. We can now create different types of NPCs with consistent features.
### Dynamic Structure
The sequence diagram is given below to make the Abstract Factory pattern understandable by seeing the interaction of the objects.

![npcabstarcfactory_sequencediagram](https://user-images.githubusercontent.com/59923068/173421819-90a4a736-daf8-460c-a588-e233a4ee83a0.PNG)

## Problem Definition
Goals and actions that are represented as a language should be interpreted by the Goal Oriented Action Planning (GOAP) controller.
We already know that actions and goals are a grammatical language that is being stored in Goal Action Database. The interpretations are not clearly stated in the report that was given to us, therefore, we should interpret the goals and actions with an interpreter. We can represent statements in the language as abstract syntax trees with the usage of Interpreter pattern.
The Interpreter pattern uses a class to represent each grammar rule. This pattern also describes how to define a grammar for languages, represent sentences in the language and interpret these sentences.
### Static Class Structure
The diagrams that are created aims to check the accuracy and consistency of our solution with the usage of the Interpreter design pattern. C++ programming language is chosen as the implementer of this flexibility requirement.
In the diagram below, we can see that GoalActionParser is made flexible with the Interpreter pattern. We defined two operations for Goal and Action parsing. First one is for interpreting the languages which gave actions boolean values. We also defined a method called change which produces a new expression. With the change method, we are able to use the Interpreter pattern multiple times.
We also created Literal Expression, And Expression and Or Expression classes to represent grammar rules. As we already know, Literal Expressions are terminal symbols in the grammar. “And”, “Or” expressions are non terminal expressions which implement an interpret operation for non terminal symbols in the grammar.

![resim](https://user-images.githubusercontent.com/59923068/173421970-bf03be33-c4aa-4451-beb0-7763e874ef1d.png)
The static class diagram contains the signatures of the classes. It is also shown that Goal Action Parser is connected to the Goal Action Database.

### Dynamic Structure
Below, Interpreter pattern’s dynamic sequence diagram is shown. In this diagram, it is clearly seen that first we are assigning our Context values, later we proceed on interpreting our contexts and evaluating the language.

![resim](https://user-images.githubusercontent.com/59923068/173422040-68f25822-cd36-4074-88aa-0b9a8e5cc6b8.png)

## Problem Definition
Goals Oriented Action Planning (GOAP) controller should update goals and multiple actions when changes are made in the AI module.
In order to make the game more consistent and realistic, we should update Goals and Action Manager subclasses inside of the GOAP controller. We already know that the GOAP controller receives information from the AI module of the game, therefore, we should update the manager classes inside of the controller.
Updating the Manager classes can be done with the help of the Observer pattern. This pattern is a structural design pattern that defines a one to many relationships between objects. In order to make the GOAP controller more flexible, we should notify the Goal and Action managers in the system.
### Static Class Structure
Below, the static class diagram of this problem is shown. In this diagram, it is clearly seen that Goal and Action Managers are the concrete observers.
Concrete subject is defined as the Goal Action Subject.
In this diagram, the Subject knows its Observer objects. It helps us to add or remove Observer objects. Observer class defines an updating interface for objects that should be notified when the changes are made. Goal and Action
Subject stores the actions and goals that the manager classes have.
Goal Manager and Action Manager classes maintain a reference to GoalActionSubject. These classes implement the updating method of their interface to keep their states consistent.

![resim](https://user-images.githubusercontent.com/59923068/173422145-383534df-ca92-45b6-bb55-6c17042c50e1.png)

### Dynamic Class Diagram
The diagram shown below is the sequence diagram of this problem. GoalActionSubject notifies its observers when a change is made. By doing so, we are able to keep the observers’ states consistent. Notify is always called by the GoalActionSubject.
After being informed of changes, Goal Manager and Action Managers can query their subject for reaching goals and actions.

![resim](https://user-images.githubusercontent.com/59923068/173422185-ecbbb2c9-1032-4658-a54a-117f0d56b3e5.png)

## Problem Definition
Coordination between Manager objects should be done effectively.
Coordination in Manager classes has an important role in our gameplay since the Manager classes coordinate the characters and teams important tasks and information. However, these classes have dependency and coordination issues that we should solve effectively by implementing a design pattern. Managers' objects , behaviors and coordinations should be separated from each other in order to have a flexible and consistent gameplay.

### Static Class Diagram

For this problem, we have designed the class diagram in order to solve the cooperation issues in the Manager class. The Manager classes are designed to manage characters or team issues in the game.
They have a huge importance in our game since without the managers our game would not work consistently and effectively. Concrete Colleagues are defined as
Navigation Manager, Weapons Manager, Target Manager, Degradation Manager and Team Manager. These colleagues are implemented in the report that was given to us, however they need to be more flexible in order to work effectively and correctly for a consistent gameplay. These colleagues can exchange information and may be dependent on one another. These dependency and cooperation issues must be solved with the Mediator design pattern.
Concrete Mediator object is defined as Cooperative Mediator and it has instances of all the colleagues. With these instances, we can trigger or coordinate the colleagues and have different kinds of operations. We can also resolve issues around dependencies by implementing extra methods within the Cooperative Mediator class.
![resim](https://user-images.githubusercontent.com/59923068/173422282-b55ba816-d600-4940-97d1-2f4331e6f554.png)


### Dynamic Class Diagram
Below, we have shown the Mediator’s dynamic class diagram for providing flexibility. We created this diagram to show how objects are interacting with each other and how they cooperate.
In this diagram, we have shown an example usage of the Mediator object. This usage resembles the fifth test case which is shown in the Test Results section. In this example, the client updates the Degradation Manager and the Mediator sets Teams role according to the information coming from the Degradation Manager. When the Team Role changes, Team Manager calls the change method of the
Mediator. Then we return back to the client.
Below, you can examine the dynamic structure of this sample.

![resim](https://user-images.githubusercontent.com/59923068/173422351-6b130a5e-ae34-4923-9a2f-8c3d3d78c0a2.png)

## Problem Definition
The World Model should process different kinds of datas.
For this problem, the world model should process different kinds of datas coming towards the World Model interface. This interface receives information from Artificial Intelligence, sensors and Facts modules. The World Model should handle datas in order to update the world of the game. This model should concrete on requesting and receiving datas from multiple sources.

### Static Class Diagram
For this problem, we have designed the class diagram in order to solve the World Model’s fixed interface problem. In this diagram, we have created a new Command superclass for extending the World Model’s interface. By doing so, we have created three different command objects which are shown below.
The three command objects are chosen as ReadFactCommand, QueryFactCommand and CreateFactCommand. These commands do their executions. These commands operate differently from each other, as it can be seen from their name. For example, read class reads the queries while create command creates the queries. All executions are different from each other.
Also World Model stores different kinds of commands inside of the command list. We can put commands inside of the World Model by calling the putCommand function. Other than that, we can request some data with the request method.

![resim](https://user-images.githubusercontent.com/59923068/173422480-284c896e-1609-4d6d-9d91-2577bdfbb973.png)

### Dynamic Class Diagram
In this section, we have created a dynamic class diagram in order to show the interactions between classes. In this diagram, we have putCommands on the World Model and then requested some datas as a client. These requests have been answered by the execute methods of the command object classes. As seen from the diagram below, we have demonstrated a usage of the Command pattern for providing flexibility.

![resim](https://user-images.githubusercontent.com/59923068/173422543-6981e6cd-fc06-4e6f-8fc2-563e7418a6f9.png)

Implementations are present in the codes. 






