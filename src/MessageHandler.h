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

	/**
	*	\brief broadcasts a message to all registered objects, callable from anywhere
	*/
	void broadcastMessage(Message& message);
	
	/**
	*	\brief register a object to receive that message type
	*/
	void registerReceiver(MessageType messageType, ReceiverFunction receiver);

	/**
	*	\brief deregister an object from receiving that message type
	*/
	void deregisterReceiver(MessageType messageType, ReceiverFunction receiver);

	/**
	*	\brief checks if the message type is in the map
	*/
	bool hasMessageType(MessageType messageType);

	/**
	*	\brief prints the entire message map
	*/
	void printState();

private:

	bool hasReceiver(MessageType messageType, ReceiverFunction receiver);

	MessageMap messageMap;

};