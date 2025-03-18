#pragma once
#include <memory>
#include <stack>
#include "state.h"
using namespace std;

class statestack
{
private:
	stack <shared_ptr<state>> gamestack; //stack of game states being managed

public:
	void pushState(shared_ptr<state> State);
	void popState();
	shared_ptr<state> getCurrentState();
};
