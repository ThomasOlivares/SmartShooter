#include "world.hpp"
#include "utility.hpp"

#include <iostream>
#include <time.h>

World::World()
: textures()
{
	srand(time(NULL)); //initialize the random values
	initTextures();
	initPlayers();
}

void World::initPlayers(){
	players.push_back(Character(leftColumn, getWindowDimensions().y/2, textures[Player]));
	players.push_back(Character(rightColumn, getWindowDimensions().y/2, textures[Player]));
}

void World::initTextures(){
	sf::Texture texture;
	if (!texture.loadFromFile("Media/character.png"))
	{
    	std::cout << "error while loading the texture" << std::endl;
    	exit(EXIT_FAILURE);
	}
	textures.insert(std::pair<Texture, sf::Texture>(Player, texture));

	if (!texture.loadFromFile("Media/health.png"))
	{
    	std::cout << "error while loading the texture" << std::endl;
    	exit(EXIT_FAILURE);
	}
	textures.insert(std::pair<Texture, sf::Texture>(Health, texture));
}

void World::update(sf::Time dt, sf::Vector2f dir){
	for (auto itr = players.begin(); itr != players.end(); itr++){
		itr->update(dt, dir);
		checkPlayerOutWindow(*itr);
	}
	collectPickups();
	destroyEntities();
	addPickups(5);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for (auto itr = players.begin(); itr != players.end(); itr++){
		itr->draw(target, states);
	}
	for (auto itr = pickups.begin(); itr != pickups.end(); itr++){
		itr->draw(target, states);
	}
}

/* If the player wants to go outside the window, we keep it inside
Later we could use a return value to train the neural network*/
void World::checkPlayerOutWindow(Character& player){
	int y = player.getBoundingRect().top;
	int height = player.getBoundingRect().height;
	if (y < 0){
		player.setPosition(player.getPosition().x, 0);
	}
	else if (y + height > getWindowDimensions().y){
		player.setPosition(player.getPosition().x, getWindowDimensions().y - height);
	}
}

/* If a player collide a pickup, his health is augmented by the healthValue 
of the pickup and the pickup is destroyed*/
void World::collectPickups(){
	for (auto player = players.begin(); player != players.end(); player++){
		sf::FloatRect rect = player->getBoundingRect();
		for (auto itr = pickups.begin(); itr != pickups.end(); itr++){
			sf::FloatRect pickupRect = itr->getBoundingRect();
			if (rect.intersects(pickupRect)){
				player->addHealth(itr->getHealth());
				itr->destroy();
			}
		}
	}
}

// Destroy the entities marked to be destroyed
void World::destroyEntities(){
	for (auto itr = pickups.begin(); itr != pickups.end();){
		if (itr->isDestroyed()){
			itr = pickups.erase(itr);
		}
		else{
			itr++;
		}
	}
}

// If pickups were destroyed, replace them
void World::addPickups(int max){
	int countLeft = 0;
	int countRight = 0;
	for (auto itr = pickups.begin(); itr != pickups.end(); itr++){
		if (itr->getPosition().x == leftColumn){
			countLeft++;
		}
		else{
			countRight++;
		}
	}
	while (countLeft < max){
		int posY = rand()%getWindowDimensions().y;
		pickups.push_back(Pickup(leftColumn, posY, textures[Health]));
		countLeft++;
	}
	while (countRight < max){
		int posY = rand()%getWindowDimensions().y;
		pickups.push_back(Pickup(rightColumn, posY, textures[Health]));
		countRight++;
	}
}