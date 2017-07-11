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
	if (id == 0){
		rotate(-angularSpeed*direction);
	}
	else{
		rotate(angularSpeed*direction);
	}
}

void Laser::rotate(double degree){
	if (id==1){
		sf::Transformable::rotate(degree);
	}
	else{
		sf::Transformable::rotate(-degree);
	}
}

double Laser::getRotation() const{
	if (id==1){
		return sf::Transformable::getRotation();
	}
	else{
		return 180 - sf::Transformable::getRotation();
	}
}

double Laser::getDirection() const{
	return direction;
}

double Laser::getDammages(sf::Time dt) const{
	return dammages*dt.asSeconds();
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
