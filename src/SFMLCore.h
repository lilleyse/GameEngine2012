// Authors: Sean and Ian Lilley

#pragma once

#include <sstream>
#include <iostream>

#include <SFML/Window.hpp>

#include "GameState.h"
#include "Entity.h"
#include "Components/Component.h"
#include "Messages/Message.h"
#include "Messages/EnterFrameMessage.h"

class SFMLCore
{
public:
    SFMLCore(void);
    virtual ~SFMLCore(void);
private:

	sf::Window* window;
	void showFPS();
	std::string title;
	sf::Clock clock;
	int frameCount;
	float framerate;

};

