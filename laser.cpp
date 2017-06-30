#include "laser.hpp"
#include "utility.hpp"

#include <iostream>

Laser::Laser(unsigned int id_, sf::Vector2f position)
: id(id_)
, dammages(laserDammages)
, angularSpeed(laserSpeed)
{
	setPosition(position);
	initSprite();
	setOrigin(sf::Vector2f(0, laserThickness/2));
	if (id == 0){
		rotate(0);
	}
	else{
		rotate(180);
	}
	
}

void Laser::initSprite(){
	mSprite = sf::RectangleShape(sf::Vector2f(laserLength, laserThickness));
	if (id == 0){
		mSprite.setFillColor(color1);
	}
	else{
		mSprite.setFillColor(color2);
	}
	centerOriginY(mSprite);
}

void Laser::update(sf::Time dt){
	rotate(angularSpeed*direction);
}

int Laser::getDammages() const{
	return dammages;
}

void Laser::changeOrientation(double value){
	direction = value;
}

void Laser::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, getTransform());
}

unsigned int Laser::getId(){
	return id;
}

sf::FloatRect Laser::getBoundingRect() const{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}
