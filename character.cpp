#include "character.hpp"
#include "utility.hpp"

#include <string>
#include <iostream>

Character::Character(int posX, int posY, sf::Texture& texture, sf::Font& font)
: mSprite()
, speed(speedCharacter)
, health(healthCharacter)
, direction(sf::Vector2f(0, 0))
, healthDisplay(font, std::to_string(health))
{
	setPosition(posX, posY);
	initSprite(texture);
	centerOrigin(mSprite);
	healthDisplay.setPosition(0, 20); //We set the text just below the character
}

void Character::initSprite(sf::Texture& texture){
	if (!texture.loadFromFile("Media/character.png"))
	{
    	std::cout << "error while loading the texture" << std::endl;
    	exit(EXIT_FAILURE);
	}
	mSprite.setTexture(texture);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, getTransform());
	healthDisplay.draw(target, getTransform());
}

void Character::update(sf::Time dt){
	move(direction*speed*dt.asSeconds());
}

void Character::setDirection(sf::Vector2f direction_){
	direction = direction_;
}

void Character::addHealth(int value){
	health += value;
}

sf::FloatRect Character::getBoundingRect() const{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}