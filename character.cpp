#include "character.hpp"

#include <iostream>

Character::Character(int posX, int posY)
: mSprite()
, speed(500)
{
	setPosition(posX, posY);
	initSprite();
}

void Character::initSprite(){
	if (!texture.loadFromFile("Media/character.png"))
	{
    	std::cout << "error while loading the texture" << std::endl;
    	exit(EXIT_FAILURE);
	}
	mSprite.setTexture(texture);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, getTransform());
}

void Character::update(sf::Time dt, sf::Vector2f dir){
	move(dir*speed*dt.asSeconds());
}

sf::FloatRect Character::getBoundingRect() const{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}