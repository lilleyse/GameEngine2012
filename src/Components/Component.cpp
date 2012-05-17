#include "Component.h"

Component::Component(){}
Component::~Component(){}

void Component::receiveMessage(Message& message)
{
	std::cout << "Message: \"" << message.messageInfo << "\" received by: " << (this) << std::endl;
}
void Component::enterFrame(Message& message)
{
	EnterFrameMessage& enterFrameMessage = (EnterFrameMessage&)message;
	std::cout << "fps: " << enterFrameMessage.framerate << " received by: " << (this) << std::endl;
}