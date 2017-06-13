#pragma once

#include "world.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
	public:
								Application();
		void					run();
		

	private:
		void 					handleEvent();
		void					update(sf::Time dt);
		void					render();


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		sf::Vector2f 			direction;
		World 					mWorld;
};
