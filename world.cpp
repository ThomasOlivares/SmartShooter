#include "world.hpp"
#include "utility.hpp"

#include <iostream>
#include <time.h>

/*TODO : 
- bullet collision
- bullet destroy after going out of window
- health printing
- end of the game (victory/defeat)
*/

World::World()
: textures()
{
	srand(time(NULL)); //initialize the random values
	initTextures();
	initPlayers();
}

void World::initPlayers(){
	players.push_back(Character(leftColumn, getWindowDimensions().y/2, 
		textures[PlayerT], mFont));
	players.push_back(Character(rightColumn, getWindowDimensions().y/2, 
		textures[PlayerT], mFont));
}

void World::initTextures(){
	load(PlayerT, "Media/character.png");
	load(PickupT, "Media/health.png");
	load(BulletT, "Media/bullet.png");
}

void World::initFonts(){
	// Load it from a file
	if (!mFont.loadFromFile("Media/Sansation.ttf"))
	{
    	printf("Error while loading font\n");
    	exit(EXIT_FAILURE);
	}
}

void World::load(Texture name, char* pathname){
	sf::Texture texture;
	if (!texture.loadFromFile(pathname))
	{
    	std::cout << "error while loading textures" << std::endl;
    	exit(EXIT_FAILURE);
	}
	textures.insert(std::pair<Texture, sf::Texture>(name, texture));
}

void World::handleEvent(sf::Event& event){
	// Player1
    sf::Vector2f direction = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        direction += sf::Vector2f(0, -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        direction += sf::Vector2f(0, 1);
    }
    players[0].setDirection(direction);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        createBullet(players[0], textures[BulletT], 1);
    }

	// Player2
	direction = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        direction += sf::Vector2f(0, -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        direction += sf::Vector2f(0, 1);
    }
    players[1].setDirection(direction);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        createBullet(players[1], textures[BulletT], -1);
    }
}

void World::update(sf::Time dt){
	for (auto itr = players.begin(); itr != players.end(); itr++){
		itr->update(dt);
		checkPlayerOutWindow(*itr);
	}
	for (auto itr = bullets.begin(); itr != bullets.end(); itr++){
		itr->update(dt);
	}
	collectPickups();
	destroyEntities();
	addPickups(maxPickup);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for (auto itr = players.begin(); itr != players.end(); itr++){
		itr->draw(target, states);
	}
	for (auto itr = pickups.begin(); itr != pickups.end(); itr++){
		itr->draw(target, states);
	}
	for (auto itr = bullets.begin(); itr != bullets.end(); itr++){
		itr->draw(target, states);
	}
}

void World::createBullet(Character player, sf::Texture& texture, int direction){
	sf::FloatRect rect = player.getBoundingRect();
	float x = rect.left + rect.width/2;
	float y = rect.top + rect.height/2;
	Bullet bullet = Bullet(x, y, texture);
	bullet.setSpeed(sf::Vector2f(direction, 0));
	bullets.push_back(bullet);
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
		pickups.push_back(Pickup(leftColumn, posY, textures[PickupT]));
		countLeft++;
	}
	while (countRight < max){
		int posY = rand()%getWindowDimensions().y;
		pickups.push_back(Pickup(rightColumn, posY, textures[PickupT]));
		countRight++;
	}
}