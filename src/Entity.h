#pragma once

#include <list>

#include "Components/Component.h"
#include "MessageHandler.h"
#include "GameState.h"

class Entity
{
public:
	Entity(GameState& gameState);
	~Entity();

	void receiveMessage(Message& message);

	void registerComponent(MessageType messageType, ReceiverFunction receiver);
	void deregisterComponent(MessageType messageType, ReceiverFunction receiver);

	void addComponent(Component* component);
	void deleteComponent(Component* component);

	virtual void printState();

private:

	GameState& gameState;
	std::string name;
	std::list<Component*> components;
	MessageHandler messageHandler;
};