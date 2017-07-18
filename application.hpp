#pragma once

#include "world.hpp"
#include "neuralNetwork.hpp"
#include "networkWindow.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
	public:
								Application(char* path1, char* path2);
		void					run();
		

	private:
		void 					handleEvent();
		void						update(sf::Time dt);
		void					render();


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		sf::RenderWindow		mWindowNetwork;
		NeuralNetwork  			mPlayer1;
		NeuralNetwork  			mPlayer2;
		NetworkWindow 			networkWindow;
		World 					mWorld;
};
