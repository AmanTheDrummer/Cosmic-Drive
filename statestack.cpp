#include "statestack.h"

void statestack::pushState(shared_ptr<state> State)
{
	gamestack.push(State); 
	//pushes a state in stack
}

void statestack::popState()
{
	if (!gamestack.empty())
	{
		gamestack.pop(); 
		//checks if stack is empty else pops first state in stack
	}
}

shared_ptr<state> statestack::getCurrentState()
{
	if (!gamestack.empty())
	{
		return gamestack.top(); 
		//returns top element if stack is not empty else returns nullptr
	}
	else return nullptr;
}
