#pragma once

#include "GameState.h"

class GlobalState
{
public:
	GlobalState();
	~GlobalState();
private:
	
	//there will be more than one game state once we create a menu system
	GameState gameState;
	
	//where do a load a scene?
	//where do i register things to the factory?
	//need to pass GlobalState as parameter instead of GameState


	
};