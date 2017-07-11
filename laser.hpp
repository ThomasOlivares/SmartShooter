#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Laser : public sf::Transformable, public sf::Drawable
{
	public :
						Laser(unsigned int id_, sf::Vector2f position);
		void 			initSprite();
		void 			update(sf::Time dt);
		virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		double 			getDammages(sf::Time dt) const;
		double 			getDirection() const;
		sf::FloatRect 	getBoundingRect() const;
		unsigned int 	getId();
		void 			rotate(double degree);
		double 			getRotation() const;
		void 			changeOrientation(double value);
		
	private :
		unsigned int 	id;
		int 			dammages;
		int 			angularSpeed;
		float 			direction;
		sf::RectangleShape 		mSprite;
};