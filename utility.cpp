#include "utility.hpp"
#include <cassert>

void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::CircleShape circle)
{
	sf::FloatRect bounds = circle.getLocalBounds();
	circle.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOriginY(sf::RectangleShape rect)
{
	sf::FloatRect bounds = rect.getLocalBounds();
	rect.setOrigin(0, std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::RectangleShape rect)
{
	sf::FloatRect bounds = rect.getLocalBounds();
	rect.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

sf::Vector2i getWindowDimensions(){
	return sf::Vector2i(600, 600);
}

sf::Vector2i getNetworkWindowDimensions(){
	return sf::Vector2i(600, 600);
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0.f, 0.f));
	return vector / length(vector);
}

double distance(sf::Vector2f p1, sf::Vector2f p2){
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}