#pragma once

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