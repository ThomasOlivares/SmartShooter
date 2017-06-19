#include "application.hpp"
#include "character.hpp"
#include "utility.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include <iostream>

using namespace std;

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: mWindow(sf::VideoMode(getWindowDimensions().x, getWindowDimensions().y)
	, "Smart Shooter", sf::Style::Close)
, mWorld()
, direction(sf::Vector2f(0, 0))
{
}

void Application::handleEvent(){
	sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed){
            mWindow.close();
        }
        else{
        	mWorld.handleEvent(event);
        }
    }
}

int Application::update(sf::Time dt)
{
	return mWorld.update(dt);
}

void Application::render()
{
	mWindow.clear(sf::Color(255, 255, 255));

	mWorld.draw(mWindow, sf::RenderStates::Default);

	mWindow.display();
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	int finalScore = 0;

	while (mWindow.isOpen() && finalScore == 0)
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			handleEvent();
			finalScore = update(TimePerFrame);
		}
		render();
	}

	if (finalScore > 0){
		std::cout << "left won with " << finalScore << " health" << std::endl;
	}
	else{
		std::cout << "right won with " << -finalScore << " health" << std::endl;
	}
}
