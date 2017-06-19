#pragma once

#include "textNode.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>

class Character : public sf::Transformable, public sf::Drawable
{
	public :
						Character(int posX, int posY, sf::Texture& texture, sf::Font& font);
		void 			initSprite(sf::Texture& texture);
		virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void 			setDirection(sf::Vector2f direction_);
		void 			update(sf::Time dt);
		void 			addHealth(int value);
		sf::FloatRect 	getBoundingRect() const;
		
	private :
		int 			health;
		float 			speed;
		sf::Sprite 		mSprite;
		sf::Texture 	texture;
		sf::Vector2f 	direction;
		TextNode 		healthDisplay;

};