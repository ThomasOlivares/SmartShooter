#include "bullet.hpp"
#include "utility.hpp"

#include <iostream>

Bullet::Bullet(unsigned int id_, int posX, int posY, sf::Texture& texture)
: id(id_)
, dammages(bulletDammages)
, absoluteSpeed(bulletSpeed)
, speed(sf::Vector2f(0, 0))
, destroyed(false)
, mSprite()
{
	setPosition(posX, posY);
	initSprite(texture);
	centerOrigin(mSprite);
}

void Bullet::update(sf::Time dt){
	move((float)absoluteSpeed*speed*dt.asSeconds());
}

void Bullet::initSprite(sf::Texture& texture){
	mSprite.setTexture(texture);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, getTransform());
}

void Bullet::setSpeed(sf::Vector2f speed_){
	speed = speed_;
}

unsigned int Bullet::getId(){
	return id;
}

void Bullet::destroy(){
	destroyed = true;
}

bool Bullet::isDestroyed(){
	return destroyed;
}

int Bullet::getDammages(){
	return dammages;
}

sf::FloatRect Bullet::getBoundingRect() const{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}
