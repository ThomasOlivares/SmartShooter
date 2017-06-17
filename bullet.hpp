#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Bullet : public sf::Transformable, public sf::Drawable
{
	public :
						Bullet(int posX, int posY, sf::Texture& texture);
		void 			initSprite(sf::Texture& texture);
		void 			update(sf::Time dt);
		virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void 			destroy();
		bool 			isDestroyed();
		void 			setSpeed(sf::Vector2f speed_);
		int 			getDammages();
		sf::FloatRect 	getBoundingRect() const;
		
	private :
		int 			dammages;
		int 			absoluteSpeed;
		sf::Vector2f 	speed;
		bool 			destroyed;
		sf::Sprite 		mSprite;
};