// Authors: Sean and Ian Lilley

#include "MessageHandler.h"

MessageHandler::MessageHandler()
{
	messageMap.resize(NUM_MESSAGES);
}
MessageHandler::~MessageHandler()
{

}

void MessageHandler::broadcastMessage(Message& message)
{
	// Call all receivers for the message type
	MessageReceiverList& messageReceiverList = messageMap[message.getType()];
	for(MessageReceiverList::iterator iter = messageReceiverList.begin(); iter != messageReceiverList.end(); iter++)
	{
		(*iter)(message);
	}
}

void MessageHandler::registerReceiver(MessageType messageType, ReceiverFunction receiver)
{
	// Try to find if the receiver is already in the list
	MessageReceiverList& messageReceiverList = this->messageMap[messageType];
	MessageReceiverList::iterator listIter;
	for(listIter = messageReceiverList.begin(); listIter != messageReceiverList.end(); ++listIter)
	{
		// TO-DO: does comparing delegates like this work? Before we were comparing .obj_pointer, which is bad
		if((*listIter) == receiver)
		{
			return; // If found in the list, do not add again
		}
	}

	// Add receiver to the list
	this->messageMap[messageType].push_back(receiver);
}

void MessageHandler::deregisterReceiver(MessageType messageType, ReceiverFunction receiver)
{

	// If the receiver exists in the list...
	MessageReceiverList& messageReceiverList = this->messageMap[messageType];
	MessageReceiverList::iterator listIter;
	for(listIter = messageReceiverList.begin(); listIter != messageReceiverList.end(); ++listIter)
	{
		// TO-DO: does comparing delegates like this work? Before we were comparing .obj_pointer, which is bad
		if((*listIter) == receiver)
		{
			// Remove the reciever from the list
			messageReceiverList.erase(listIter);
			return;
		}
	}
}

bool MessageHandler::hasMessageType(MessageType messageType)
{
	return this->messageMap[messageType].size() > 0;
}


void MessageHandler::printState()
{
	// Loop over the message map
	for(int i = 0; i < NUM_MESSAGES; i++)
	{
		std::cout << "Message ID: " << i << std::endl;
		MessageReceiverList::iterator listIter;
		MessageReceiverList& list = messageMap[i];

		// Print the receiver functions from the list
		for(listIter = list.begin(); listIter != list.end(); ++listIter)
		{
			std::cout << "  " << (*listIter).object_ptr << std::endl;
		}
	}
}