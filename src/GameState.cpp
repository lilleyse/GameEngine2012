#include "GameState.h"

GameState::GameState(){}
GameState::~GameState(){}

MessageHandler& GameState::getMessageHandler()
{
	return this->messageHandler;
}