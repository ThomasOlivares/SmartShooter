#pragma once

// Pickups
#define healthCharacter 100
#define healthValue 	20
#define maxPickup 		1
#define pickupBonus     100

// Bullets
#define bulletDammages 	30
#define bulletSpeed 	1000
#define bulletPerSeconds 1

//Characters
#define leftColumn 		100  // Positions of the two character and pickups associated
#define rightColumn 	500
#define speedCharacter 	500

//Time
#define maxTime 		30

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>

void 			centerOrigin(sf::Sprite& sprite);
void 			centerOrigin(sf::CircleShape circle);
void 			centerOrigin(sf::RectangleShape rect);
void 			centerOrigin(sf::Text& text);
sf::Vector2i 	getWindowDimensions();
float 			length(sf::Vector2f vector);
sf::Vector2f 	unitVector(sf::Vector2f vector);