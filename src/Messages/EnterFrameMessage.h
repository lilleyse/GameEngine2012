// Authors: Sean and Ian Lilley

#pragma once

#include <string>

#include "MessageTypes.h"
#include "Message.h"

class EnterFrameMessage : public Message
{
public:
	
	EnterFrameMessage(){}
	virtual ~EnterFrameMessage(){}

	virtual MessageType getType()
	{
		return MESSAGE_ENTER_FRAME;
	}

	float framerate;
};