#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Character : public sf::Transformable, public sf::Drawable
{
	public :
						Character(int posX, int posY);
		void 			initSprite();
		virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void 			update(sf::Time dt, sf::Vector2f dir);
		sf::FloatRect 	getBoundingRect() const;
		
	private :
		int 			health;
		float 			speed;
		sf::Sprite 		mSprite;
		sf::Texture 	texture;
};