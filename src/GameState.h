// Authors: Sean and Ian Lilley

#pragma once

#include "MessageHandler.h"

class GameState
{

public:
	GameState();
	~GameState();

	MessageHandler& getMessageHandler();

private:
	MessageHandler messageHandler;


};