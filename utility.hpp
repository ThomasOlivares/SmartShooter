#pragma once

// General
#define sizePopulation   100
#define nbIterations     300

// Score
#define maxScore         40

// Pickups
#define healthValue 	 20
#define maxPickup 		 1
#define pickupBonus      100 // Bonus score
#define pickupCoefficient 0

// Lasers
#define laserSpeed       2  // angular speed
#define laserDammages    0
#define laserBonus       0
#define laserAngleCoefficient 0

#define color1 			 sf::Color::Red
#define color2 			 sf::Color::Blue
#define laserLength      800
#define laserThickness   2


//Characters
#define healthCharacter  100
#define leftColumn 		 100  // Positions of the two character and pickups associated
#define rightColumn 	 500
#define speedCharacter 	 500

//Time
#define maxTime 		 30

// During selection, size of the list of candidates (chosen randomly)
#define sizeTournament   5

// Poucentage of networks removed after selection
#define pourcentageElimination 50

// Mutation parameters
#define mutationPerCent 10.f
#define mutationValue 1

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>

void 			centerOrigin(sf::Sprite& sprite);
void 			centerOrigin(sf::CircleShape circle);
void 			centerOrigin(sf::RectangleShape rect);
void 			centerOriginY(sf::RectangleShape rect);
void 			centerOrigin(sf::Text& text);
sf::Vector2i 	getWindowDimensions();
sf::Vector2i 	getNetworkWindowDimensions();
float 			length(sf::Vector2f vector);
sf::Vector2f 	unitVector(sf::Vector2f vector);
double 			distance(sf::Vector2f p1, sf::Vector2f p2);