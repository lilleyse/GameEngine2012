// Authors: Sean and Ian Lilley

#pragma once

#include <iostream>
#include <map>
#include <list>
#include <algorithm>

#include <srutil/delegate/delegate.hpp>

#include "Messages/Message.h"

typedef srutil::delegate<void (Message&)> ReceiverFunction;
typedef std::list<ReceiverFunction> MessageReceiverList;
typedef std::map<MessageType, MessageReceiverList> MessageMap;

#define DELEGATE(className, function, object) ReceiverFunction::from_method<className,&function>(object)

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();

	//broadcasts a message to all registered objects, callable from anywhere
	void broadcastMessage(Message& message);
	
	//register a object to receive that message type
	void registerReceiver(MessageType messageType, ReceiverFunction receiver);

	//deregister an object from receiving that message type
	void deregisterReceiver(MessageType messageType, ReceiverFunction receiver);

	bool hasMessageType(MessageType messageType);

	void printState();

private:

	bool hasReceiver(MessageType messageType, ReceiverFunction receiver);

	MessageMap messageMap;

};