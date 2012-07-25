#pragma once

#include <iostream>

#include "../Messages/Message.h"
#include "../Messages/EnterFrameMessage.h"

//Entity and Component reference each other, so this breaks the cyclic dependency
class Entity;

class Component
{
public:

	Component();
	virtual ~Component();

	void receiveMessage(Message& message);
	void enterFrame(Message& message);

	Entity* parentEntity;	
	
};