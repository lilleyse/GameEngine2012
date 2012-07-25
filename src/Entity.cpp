#include "Entity.h"

Entity::Entity(GameState& gameState) : gameState(gameState){}
Entity::~Entity(){}


void Entity::initialize(std::string& filename)
{
	/*XMLDocument doc;
	doc.Parse(filename.c_str());

	for(XMLElement* componentXML = doc.FirstChildElement(); componentXML != 0; componentXML = doc.NextSiblingElement())
	{
		std::string componentType(componentXML->GetText());
		this->addComponent(component);
	}*/
}

void Entity::receiveMessage(Message& message)
{
	// Broadcast the message to all of the entity's components
	this->messageHandler.broadcastMessage(message);
}

void Entity::registerComponent(MessageType messageType, ReceiverFunction receiver)
{
	//Component* component = (Component*)receiver.object_ptr;
	//if(hasComponent(component))
	//{
		this->messageHandler.registerReceiver(messageType, receiver);
		this->gameState.getMessageHandler().registerReceiver(messageType,DELEGATE(Entity, Entity::receiveMessage, this));
	//}
}
void Entity::deregisterComponent(MessageType messageType, ReceiverFunction receiver)
{
	// May have to check if the component has been add to some component list
	
	// Deregister the component from receiving this message
	this->messageHandler.deregisterReceiver(messageType, receiver);
	
	// Now, if no components are asking for this message, remove the entity from the global message map
	if(!this->messageHandler.hasMessageType(messageType))
	{
		this->gameState.getMessageHandler().deregisterReceiver(messageType, DELEGATE(Entity, Entity::receiveMessage, this)); 
	}
}

void Entity::addComponent(Component* component)
{
	this->components.push_back(component);
	component->parentEntity = this;
}

void Entity::deleteComponent(Component* component)
{
	components.remove(component);
}

bool Entity::hasComponent(Component* component)
{
	return std::find(this->components.begin(), this->components.end(), component) != this->components.end();
}

void Entity::printState()
{
	std::cout << "Printing entity state:" << std::endl;
	this->messageHandler.printState();
}
