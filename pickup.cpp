#include "pickup.hpp"
#include "utility.hpp"

#include <iostream>

Pickup::Pickup(unsigned int id_, int posX, int posY, sf::Texture& texture)
: id(id_)
, mSprite()
, destroyed(false)
, health(healthValue)
{
	setPosition(posX, posY);
	initSprite(texture);
	centerOrigin(mSprite);
}

void Pickup::initSprite(sf::Texture& texture){
	mSprite.setTexture(texture);
}

void Pickup::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, getTransform());
}

void Pickup::destroy(){
	destroyed = true;
}

bool Pickup::isDestroyed(){
	return destroyed;
}

int Pickup::getHealth(){
	return health;
}

sf::FloatRect Pickup::getBoundingRect() const{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}

unsigned int Pickup::getId() const{
	return id;
}