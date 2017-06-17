#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Pickup : public sf::Transformable, public sf::Drawable
{
	public :
						Pickup(int posX, int posY, sf::Texture& texture);
		void 			initSprite(sf::Texture& texture);
		virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void 			destroy();
		bool 			isDestroyed();
		int 			getHealth();
		sf::FloatRect 	getBoundingRect() const;
		
	private :
		bool 			destroyed;
		int 			health;
		sf::Sprite 		mSprite;
};