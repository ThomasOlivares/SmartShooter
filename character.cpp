#include "character.hpp"
#include "utility.hpp"

#include <string>
#include <iostream>

Character::Character(unsigned int id_, int posX, int posY, 
	sf::Texture& texture, const sf::Font& font)
: id(id_)
, mSprite()
, speed(speedCharacter)
, laserAngle(0)
, health(healthCharacter)
, direction(sf::Vector2f(0, 0))
, healthDisplay()
{
	for (int i = 0; i<6; i++){
		scores.push_back(0);
	}
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
}

sf::Vector2f Character::getDirection(){
	return direction;
}

void Character::setDirection(sf::Vector2f direction_){
	direction = direction_;
}

void Character::setLaserDirection(float laserDir_){
	laserDir = laserDir_;
}

double Character::getHealth(){
	return health;
}

void Character::addHealth(double value){
	health += value;
}

double Character::getScore(){
	double finalScore = 0;
	for (auto itr = scores.begin(); itr!=scores.end(); ++itr){
		finalScore += *itr;
	}
	return finalScore;
}

double Character::getScore(int i){
	return scores[i];
}

std::vector<double> Character::getScoreVector(){
	return scores;
}

void Character::setScore(double score_, int where){
	scores[where] = score_;
}

void Character::addScore(double score_, int where){
	scores[where]+=score_;
}

void Character::takeDammages(double value){
	health -= value;
}

sf::FloatRect Character::getBoundingRect() const{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}

unsigned int Character::getId() const{
	return id;
}