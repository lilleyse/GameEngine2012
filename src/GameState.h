// Authors: Sean and Ian Lilley

#pragma once

#include "MessageHandler.h"
#include "OpenGL/GLState.h"

class GameState
{

public:
	GameState();
	~GameState();

	MessageHandler& getMessageHandler();
	GLState& getGLState();

private:
	MessageHandler messageHandler;
	GLState glState;
	


};