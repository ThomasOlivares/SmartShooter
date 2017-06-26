#pragma once

#include "neuralNetwork.hpp"
#include "world.hpp"
#include "utility.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class ApplicationTrain
{
	public:
										ApplicationTrain(NeuralNetwork& mPlayer1_
											, NeuralNetwork& mPlayer2_);
		std::pair<double, double>		run();
		

	private:
		void 							handleEvent();
		std::pair<double, double>		update(sf::Time dt);


	private:
		static const sf::Time	TimePerFrame;

		World 					mWorld;
		NeuralNetwork  			mPlayer1;
		NeuralNetwork  			mPlayer2;
};
