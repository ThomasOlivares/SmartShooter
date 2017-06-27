#include "character.hpp"
#include "utility.hpp"

#include <string>
#include <iostream>

Character::Character(unsigned int id_, int posX, int posY, 
	sf::Texture& texture, const sf::Font& font)
: id(id_)
, mSprite()
, speed(speedCharacter)
, health(healthCharacter)
, score(0)
, direction(sf::Vector2f(0, 0))
, healthDisplay()
, cooldown(sf::seconds(0))
, fireRate(sf::seconds(bulletPerSeconds))
{
	setPosition(posX, posY);
	initSprite(texture);
	initText(font);
	centerOrigin(mSprite);
}

void Character::initSprite(sf::Texture& texture){
	mSprite.setTexture(texture);
}

void Character::initText(const sf::Font& font){
	healthDisplay.setFont(font);
	healthDisplay.setString(std::to_string(health));
	healthDisplay.setCharacterSize(15);
	healthDisplay.setPosition(0, 20); // We set the text just below the character
	healthDisplay.setStyle(sf::Text::Bold);
	healthDisplay.setColor(sf::Color::Red);

	centerOrigin(healthDisplay);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, getTransform());
	target.draw(healthDisplay, getTransform());
}

void Character::update(sf::Time dt){
	move(direction*speed*dt.asSeconds());
	healthDisplay.setString(std::to_string(health));
	cooldown += dt;
}

bool Character::canShoot(){
	if(cooldown > fireRate){
		cooldown = sf::seconds(0);
		return true;
	}
	return false;
}

void Character::setDirection(sf::Vector2f direction_){
	direction = direction_;
}

int Character::getHealth(){
	return health;
}

void Character::addHealth(int value){
	health += value;
}

int Character::getScore(){
	return score;
}

void Character::addScore(int score_){
	score+=score_;
}

void Character::takeDammages(int value){
	health -= value;
}

sf::FloatRect Character::getBoundingRect() const{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}

unsigned int Character::getId() const{
	return id;
}