// Authors: Sean and Ian Lilley

#pragma once

#include <string>

#include "MessageTypes.h"

class Message
{
public:
	
	Message(){}
	virtual ~Message(){}

	virtual MessageType getType()
	{
		return MESSAGE_DEFAULT;
	}

	std::string messageInfo;
};