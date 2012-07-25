#pragma once

#include <list>

#include <tinyxml/tinyxml2.h>
using namespace tinyxml2;

#include "Components/Component.h"
#include "Components/RenderComponent.h"
#include "MessageHandler.h"
#include "GameState.h"

class Entity
{
public:
	Entity(GameState& gameState);
	~Entity();

	/**
	*	\brief Initialize this entity based on an xml file
	*/
	void initialize(std::string& filename);

	/**
	*	\brief Entity's callback function from the global message map,
			or you can call this function directly
	*/
	void receiveMessage(Message& message);

	/**
	*	\brief Register the component to that message type
	*/
	void registerComponent(MessageType messageType, ReceiverFunction receiver);
	
	/**
	*	\brief Deregister the component from that message type
	*	If no more components are attached to that message type, remove the entity from the global message map
	*/
	void deregisterComponent(MessageType messageType, ReceiverFunction receiver);


	void addComponent(Component* component);
	void deleteComponent(Component* component);

	virtual void printState();

private:

	
	bool hasComponent(Component* component);	

	GameState& gameState;
	std::string name;
	std::list<Component*> components;
	MessageHandler messageHandler;
	
};