// Authors: Sean and Ian Lilley

#pragma once

#include <string>

#include "MessageTypes.h"
#include "Message.h"

class EnterFrameMessage : public Message
{
public:
	
	EnterFrameMessage() : Message()
	{
		messageType = MESSAGE_ENTER_FRAME;
	}
	~EnterFrameMessage()
	{

	}

	float framerate;
};