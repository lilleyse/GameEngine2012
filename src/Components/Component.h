#pragma once

#include <iostream>

#include "../Messages/Message.h"
#include "../Messages/EnterFrameMessage.h"

class Component
{
public:
	Component();
	virtual ~Component();

	void receiveMessage(Message& message);
	void enterFrame(Message& message);
};