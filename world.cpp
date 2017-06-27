#include "world.hpp"
#include "utility.hpp"

#include <cassert>
#include <iostream>
#include <time.h>

World::World()
: textures()
, mTime(sf::seconds(0))
{
	srand(time(NULL)); //initialize the random values
	initTextures();
	initFonts();
	initPlayers();
}

void World::initPlayers(){
	players.push_back(Character(0, leftColumn, getWindowDimensions().y/2, 
		textures[PlayerT], mFont));
	players.push_back(Character(1, rightColumn, getWindowDimensions().y/2, 
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

void World::handleEvent(std::vector<double> decision1, std::vector<double> decision2){
	// Player1
    players[0].setDirection(sf::Vector2f(0, 2*decision1[0] - 1));
    // We shoot with the probability decision[1]
    double shoot = (double)(rand()%10000)/10000.f;
    if (shoot < decision1[1]){
    	createBullet(players[0], textures[BulletT], 1);
    }

    // Player2
    players[1].setDirection(sf::Vector2f(0, 2*decision2[0] - 1));
    shoot = (double)(rand()%10000)/10000.f;
    if (shoot < decision2[1]){
    	createBullet(players[1], textures[BulletT], -1);
    }
}

bool World::update(sf::Time dt){
	mTime +=dt;
	for (auto itr = players.begin(); itr != players.end(); itr++){
		itr->update(dt);
		checkPlayerOutWindow(*itr);
	}
	for (auto itr = bullets.begin(); itr != bullets.end(); itr++){
		itr->update(dt);
	}
	collectPickups();
	collisionDetection();
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

void World::createBullet(Character& player, sf::Texture& texture, int direction){
	if (player.canShoot()){
		sf::FloatRect rect = player.getBoundingRect();
		float x = rect.left + rect.width/2;
		float y = rect.top + rect.height/2;
		Bullet bullet = Bullet(player.getId(), x, y, texture);
		bullet.setSpeed(sf::Vector2f(direction, 0));
		bullets.push_back(bullet);
	}
}

/* If the player wants to go outside the window, we keep it inside
Later we could use a return value to train the neural network*/
void World::checkPlayerOutWindow(Character& player){
	int y = player.getBoundingRect().top + player.getBoundingRect().height/2;
	int height = player.getBoundingRect().height;
	if (y < 0){
		player.addScore(y);
		assert(y<0);
		player.setPosition(player.getPosition().x, 0);
	}
	else if (y > getWindowDimensions().y){
		player.addScore(getWindowDimensions().y - y);
		assert((getWindowDimensions().y - y)<0);
		player.setPosition(player.getPosition().x, getWindowDimensions().y);
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
				player->addScore(pickupBonus);
				itr->destroy();
			}
		}
	}
}

void World::collisionDetection(){
	for (auto player = players.begin(); player != players.end(); player++){
		sf::FloatRect rect = player->getBoundingRect();
		for (auto itr = bullets.begin(); itr != bullets.end(); itr++){
			sf::FloatRect bulletRect = itr->getBoundingRect();
			if (rect.intersects(bulletRect)){
				player->takeDammages(itr->getDammages());
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
	for (auto itr = bullets.begin(); itr != bullets.end();){
		if (itr->isDestroyed()){
			itr = bullets.erase(itr);
		}
		else if (itr->getPosition().x < 0 || itr->getPosition().x > getWindowDimensions().x){
			itr = bullets.erase(itr);
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
		pickups.push_back(Pickup(0, leftColumn, posY, textures[PickupT]));
		countLeft++;
	}
	while (countRight < max){
		int posY = rand()%getWindowDimensions().y;
		pickups.push_back(Pickup(1, rightColumn, posY, textures[PickupT]));
		countRight++;
	}
}

/* return a number corresponding to the health of the winner
positive value means left player won, negative means right player won*/
bool World::checkGameOver(){
	if (players[0].getHealth() <= 0){
		return true;
	}
	else if (players[1].getHealth() <= 0){
		return true;
	}
	else if(mTime.asSeconds() > maxTime){
		return true;
	}
	return false;
}

std::pair<int, int> World::getFinalScores(){
	return std::pair<int, int>(players[0].getScore() ,players[1].getScore());
}

void World::setFinalScores(){
	players[0].addScore(players[0].getHealth() - players[1].getHealth());
	players[1].addScore(players[1].getHealth() - players[0].getHealth());
}

// return the values which we will give to the left neural network
std::vector<double> World::getImputs(int id){
	std::vector<double> result;
	double dimX = getWindowDimensions().x;
	double dimY = getWindowDimensions().y;

	// We transform the players positions into a value beetween -1 and 1
	result.push_back((2*players[id].getPosition().y - dimY)/dimY);
	result.push_back((2*players[1-id].getPosition().y - dimY)/dimY);

	// Same for pickup
	bool found = false;
	for (auto itr = pickups.begin(); itr != pickups.end(); itr++){
		if (itr->getId() == id && !itr->isDestroyed()){
			result.push_back((2*itr->getPosition().y - dimY)/dimY);
			found = true;
		}
	}
	if (!found){
		result.push_back(0);
	}

	// Same for bullet
	found = false;
	for (auto itr = bullets.begin(); itr != bullets.end(); itr++){
		if (itr->getId() == 1-id){
			result.push_back((2*itr->getPosition().y - dimY)/dimY);
			double position = (2*itr->getPosition().x - dimX)/dimX;
			if (id == 0){
				result.push_back(position);
			}
			else{
				result.push_back(-position);
			}
			found = true;
		}
	}
	if (!found){
		/* window is beetween 0 and 1 so 10 is really outside, and 
			the player shouldn't care about it*/
		result.push_back(10);
		result.push_back(10);
	}


	return result;
}
