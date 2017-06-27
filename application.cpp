#include "application.hpp"
#include "character.hpp"
#include "utility.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include <iostream>

using namespace std;

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application(char* path1, char* path2)
: mWindow(sf::VideoMode(getWindowDimensions().x, getWindowDimensions().y)
	, "Smart Shooter", sf::Style::Close)
, mWorld()
, mPlayer1(path1)
, mPlayer2(path2)
{
}

/* For both players, we give them imput, compute the layers 
and give the output to the World class*/
void Application::handleEvent(){
	sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed){
            mWindow.close();
        }
    }
	mPlayer1.setImput(mWorld.getImputs(0));
	mPlayer2.setImput(mWorld.getImputs(1));
	mPlayer1.computeLayers();
	mPlayer2.computeLayers();
	std::vector<double> decision1 = mPlayer1.output();
	std::vector<double> decision2 = mPlayer2.output();
	mWorld.handleEvent(decision1, decision2);
}

void Application::update(sf::Time dt)
{
	mWorld.update(dt);
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

	bool finished = false;
	std::pair<int, int> finalScore(0, 0);

	while (mWindow.isOpen() && !finished)
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			handleEvent();
			update(TimePerFrame);
			if (mWorld.checkGameOver()){
				finished = true;
				mWorld.setFinalScores();
				finalScore = mWorld.getFinalScores();
			}
		}
		render();
	}

	if (finalScore.first > 0){
		std::cout << "left won with " << finalScore.first << " score" << std::endl;
	}
	else{
		std::cout << "right won with " << finalScore.second << " score" << std::endl;
	}
}
