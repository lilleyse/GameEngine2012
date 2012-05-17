// Authors: Sean and Ian Lilley

#include "MessageHandler.h"

MessageHandler::MessageHandler(){}
MessageHandler::~MessageHandler(){}

void MessageHandler::broadcastMessage(Message& message)
{
	//See if the message type exists in the map
	MessageMap::iterator found = this->messageMap.find(message.getType());
	if(found != this->messageMap.end())
	{
		//Call all receivers for the message type
		MessageReceiverList& messageReceiverList = found->second;
		for(MessageReceiverList::iterator iter = messageReceiverList.begin(); iter != messageReceiverList.end(); iter++)
		{
			(*iter)(message);
		}
	}
}

void MessageHandler::registerReceiver(MessageType messageType, ReceiverFunction receiver)
{
	if(!this->hasReceiver(messageType,receiver))
	{
		this->messageMap[messageType].push_back(receiver);
	}
}

void MessageHandler::deregisterReceiver(MessageType messageType, ReceiverFunction receiver)
{
	//See if the message type exists in the map
	MessageMap::iterator found = this->messageMap.find(messageType);
	if(found != this->messageMap.end())
	{
		//Remove receiver from list
		MessageReceiverList& messageReceiverList = found->second;
		messageReceiverList.remove(receiver);

		//Remove message type from map if there are no more receivers
		if(messageReceiverList.size() == 0)
		{	
			messageMap.erase(messageType);
		}
	}
}

bool MessageHandler::hasReceiver(MessageType messageType, ReceiverFunction receiver)
{
	//See if the message type exists in the map
	MessageMap::iterator found = this->messageMap.find(messageType);
	if(found != this->messageMap.end())
	{
		//See if the list contains the receiver
		MessageReceiverList& messageReceiverList = found->second;
		MessageReceiverList::iterator listIter;
		for(listIter = messageReceiverList.begin(); listIter != messageReceiverList.end(); ++listIter)
		{
			if((*listIter).object_ptr == receiver.object_ptr)
			{
				return true;
			}
		}
	}
	return false;
}

bool MessageHandler::hasMessageType(MessageType messageType)
{
	return this->messageMap.find(messageType) != this->messageMap.end();
}

void MessageHandler::printState()
{
	MessageMap::iterator mapIter;
	for(mapIter = this->messageMap.begin(); mapIter != this->messageMap.end(); ++mapIter)
	{
		std::cout << "Message ID: " << mapIter->first << std::endl;
		MessageReceiverList::iterator listIter;
		MessageReceiverList& list = mapIter->second;
		for(listIter = list.begin(); listIter != list.end(); ++listIter)
		{
			std::cout << "  " << (*listIter).object_ptr << std::endl;
		}
	}
}