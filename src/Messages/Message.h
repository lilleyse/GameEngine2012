// Authors: Sean and Ian Lilley

#pragma once

#include <string>

#include "MessageTypes.h"

class Message
{
public:
	
	Message()
	{
		messageType = MESSAGE_ENTER_FRAME;
	}

	~Message()
	{
	
	}

	MessageType getType()
	{
		return messageType;
	}

	MessageType messageType;
	std::string messageInfo;
};