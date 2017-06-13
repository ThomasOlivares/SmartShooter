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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        	direction = sf::Vector2f(0, -1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        	direction = sf::Vector2f(0, 1);
        }
        else{
        	direction = sf::Vector2f(0, 0);
        }
    }
}

void Application::update(sf::Time dt)
{
	mWorld.update(dt, direction);
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

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			handleEvent();
			update(TimePerFrame);
		}
		render();
	}
}
