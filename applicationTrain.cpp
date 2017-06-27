#include "applicationTrain.hpp"
#include "character.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include <iostream>

using namespace std;

const sf::Time ApplicationTrain::TimePerFrame = sf::seconds(1.f/60.f);

ApplicationTrain::ApplicationTrain(NeuralNetwork& mPlayer1_, NeuralNetwork& mPlayer2_)
: mWorld()
, mPlayer1(mPlayer1_)
, mPlayer2(mPlayer2_)
{
}

/* For both players, we give them imput, compute the layers 
and give the output to the World class*/
void ApplicationTrain::handleEvent(){
	mPlayer1.setImput(mWorld.getImputs(0));
	mPlayer2.setImput(mWorld.getImputs(1));
	mPlayer1.computeLayers();
	mPlayer2.computeLayers();
	std::vector<double> decision1 = mPlayer1.output();
	std::vector<double> decision2 = mPlayer2.output();
	mWorld.handleEvent(decision1, decision2);
}

void ApplicationTrain::update(sf::Time dt)
{
	mWorld.update(dt);
}

std::pair<double, double> ApplicationTrain::run()
{
	while (true)
	{
		handleEvent();
		update(TimePerFrame);
		if (mWorld.checkGameOver()){
			mWorld.setFinalScores();
			return mWorld.getFinalScores();
		}
	}
}
