#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Character : public sf::Transformable, public sf::Drawable
{
	public :
						Character(unsigned int id_, int posX, int posY, 
							sf::Texture& texture, const sf::Font& font);
		void 			initSprite(sf::Texture& texture);
		void 			initText(const sf::Font& font);
		virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void 			setDirection(sf::Vector2f direction_);
		void 			setLaserDirection(float laserDir_);
		int 			getHealth();
		int 			getScore();
		void 			addScore(int score_);
		void 			update(sf::Time dt);
		void 			addHealth(int value);
		void 			takeDammages(int value);
		bool 			canShoot();
		sf::FloatRect 	getBoundingRect() const;
		unsigned int 	getId() const;
		
	private :
		unsigned int 	id;
		int 			health;
		int 			score;
		float 			speed;
		float 			laserAngle;
		float 			laserDir;
		sf::Sprite 		mSprite;
		sf::Texture 	texture;
		sf::Vector2f 	direction;
		sf::Text  		healthDisplay;
		sf::Font 		mFont;
		sf::Time 		cooldown;
		const sf::Time 	fireRate;
};