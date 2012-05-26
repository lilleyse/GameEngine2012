// Authors: Sean and Ian Lilley

#include "SFMLCore.h"

SFMLCore::SFMLCore(void)
{
	//Create the window
	int width = 1024;
	int height = 768;
	title = "Game Engine";
	window = new sf::Window(sf::VideoMode(width, height, 32), title);
	
	window->setActive();
	//window->setVerticalSyncEnabled(true);

	//RANDOM STUFF --------------
	GameState gameState;
	Entity entity(gameState);
	Component* component1 = new Component();
	Component* component2 = new Component();
	entity.addComponent(component1);
	entity.addComponent(component2);
	entity.registerComponent(MESSAGE_DEFAULT,DELEGATE(Component, Component::receiveMessage,component1));
	//entity.deregisterComponent(MESSAGE_DEFAULT,DELEGATE(Component, Component::receiveMessage,component1));
	entity.registerComponent(MESSAGE_DEFAULT,DELEGATE(Component, Component::receiveMessage,component1));

	entity.registerComponent(MESSAGE_ENTER_FRAME,DELEGATE(Component, Component::enterFrame, component1));
	entity.registerComponent(MESSAGE_ENTER_FRAME,DELEGATE(Component, Component::enterFrame, component2));

	Message message;
	message.messageInfo = "Hi there!";
	gameState.getMessageHandler().broadcastMessage(message);

	EnterFrameMessage enterFrameMessage;
	enterFrameMessage.framerate = 1000.0f;

	gameState.getMessageHandler().printState();
	entity.printState();
	//--------------------------

	int numFrames = 0;
	sf::Clock clock;

	//Handle events
	frameCount = 0;
    while (window->isOpen())
    {
		window->display();
		this->showFPS();

        sf::Event myEvent;
		while (window->pollEvent(myEvent))
        {
			//convert sfml events to messages
			if (myEvent.type == sf::Event::Closed)
            {
                window->close();
            }
        }
    }
}


void SFMLCore::showFPS()
{
	//Show fps
	frameCount++;
	float currentTime = clock.getElapsedTime().asSeconds();
	
	if(currentTime >= 0.5f)
	{	
		std::ostringstream ss;
		ss << title << " (fps: " << (frameCount/currentTime) << " )";
		window->setTitle(ss.str());

		clock.restart();
		frameCount = 0;
	}
}


SFMLCore::~SFMLCore(void){}