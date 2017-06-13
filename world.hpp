#pragma once

#include "character.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

class World : public sf::Drawable
{
	public : 
						World();
		virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void 			update(sf::Time dt, sf::Vector2f dir);
		void 			checkPlayerOutWindow();

	private :
		Character 		mPlayer;
};
