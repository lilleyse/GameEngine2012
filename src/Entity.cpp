#include "Entity.h"

Entity::Entity(GameState& gameState) : gameState(gameState){}
Entity::~Entity(){}

void Entity::receiveMessage(Message& message)
{
	this->messageHandler.broadcastMessage(message);
}

void Entity::registerComponent(MessageType messageType, ReceiverFunction receiver)
{
	//only register components that have been added
	this->messageHandler.registerReceiver(messageType, receiver);
	this->gameState.getMessageHandler().registerReceiver(messageType,DELEGATE(Entity, Entity::receiveMessage, this));
}
void Entity::deregisterComponent(MessageType messageType, ReceiverFunction receiver)
{
	this->messageHandler.deregisterReceiver(messageType, receiver);
	if(!this->messageHandler.hasMessageType(messageType))
	{
		//ReceiverFunction function = ReceiverFunction::from_method<Entity,&Entity::receiveMessage>(this);
		this->gameState.getMessageHandler().deregisterReceiver(messageType, DELEGATE(Entity, Entity::receiveMessage, this)); 
	}
}

void Entity::addComponent(Component* component)
{
	this->components.push_back(component);
}

void Entity::deleteComponent(Component* component)
{
	components.remove(component);
}

void Entity::printState()
{
	std::cout << "Printing entity state:" << std::endl;
	this->messageHandler.printState();
}
