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
	lasers.push_back(Laser(0, players[0].getPosition()));
	lasers.push_back(Laser(1, players[1].getPosition()));
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

/*
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
*/

void World::handleEvent(std::vector<double> decision1, std::vector<double> decision2){
	// Player1
    players[0].setDirection(sf::Vector2f(0, 2*decision1[0] - 1));
    orientLaser(players[0], decision1[1]);

    // Player2
    players[1].setDirection(sf::Vector2f(0, 2*decision2[0] - 1));
    orientLaser(players[1], decision2[1]);
}

bool World::update(sf::Time dt){
	mTime +=dt;
	for (auto itr = players.begin(); itr != players.end(); itr++){
		itr->update(dt);
		checkPlayerOutWindow(*itr);
		lasers[itr->getId()].setPosition(itr->getPosition());
	}
	for (auto itr = lasers.begin(); itr != lasers.end(); itr++){
		itr->update(dt);
	}
	addScoreLaser();
	addScorePickup();
	collectPickups();
	collisionDetection(dt);
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
	for (auto itr = lasers.begin(); itr != lasers.end(); itr++){
		itr->draw(target, states);
	}
}

void World::orientLaser(Character& player, double value){
	unsigned int id = player.getId();
	lasers[id].changeOrientation(2*value-1);
	double angle = lasers[id].getRotation();
	if (angle < 90 || angle > 270){
		player.addScore(-1, 5);
	}
}

/* If the player wants to go outside the window, we keep it inside
Later we could use a return value to train the neural network*/
void World::checkPlayerOutWindow(Character& player){
	int y = player.getBoundingRect().top + player.getBoundingRect().height/2;
	int height = player.getBoundingRect().height;
	if (y < 0){
		player.addScore(y, 5);
		assert(y<0);
		player.setPosition(player.getPosition().x, 0);
	}
	else if (y > getWindowDimensions().y){
		player.addScore(getWindowDimensions().y - y, 5);
		assert((getWindowDimensions().y - y)<0);
		player.setPosition(player.getPosition().x, getWindowDimensions().y);
	}
}

void World::addScoreLaser(){
	// player left
	double perfectAngle = getPerfectAngle(players[0], players[1]);
	double angle = lasers[0].getRotation();
	double dir = lasers[0].getDirection();
	if ((perfectAngle-angle)*dir > 0){
		players[0].addScore(laserAngleCoefficient*fabs(dir), 3);
	}

	// player right
	perfectAngle = getPerfectAngle(players[1], players[0]);
	angle = lasers[1].getRotation();
	dir = lasers[1].getDirection();
	if ((perfectAngle-angle)*dir > 0){
		players[1].addScore(laserAngleCoefficient*fabs(dir), 3);
	}
}
/*
void World::addScorePickup(){
	for (auto itr = pickups.begin(); itr < pickups.end(); itr++){
		if (itr->getId() == 0){
			double pickupPosition = itr->getPosition().y;
			double playerPosition = players[0].getPosition().y;
			double bonus = pickupConstant-abs(pickupPosition-playerPosition);
			players[0].addScore(pickupCoefficient*bonus);
		}
		else{
			double pickupPosition = itr->getPosition().y;
			double playerPosition = players[1].getPosition().y;
			double bonus = pickupConstant-abs(pickupPosition-playerPosition);
			players[1].addScore(pickupCoefficient*bonus);
		}
	}
}
*/
void World::addScorePickup(){
	for (auto itr = pickups.begin(); itr < pickups.end(); itr++){
		if (itr->getId() == 0){
			double pickupPosition = itr->getPosition().y;
			double playerPosition = players[0].getPosition().y;
			double diff = pickupPosition - playerPosition;
			double dir = players[0].getDirection().y;
			if (dir * diff > 0){
				players[0].addScore(pickupCoefficient*abs(dir), 1);
			}
			else{
				players[0].addScore(-pickupCoefficient*abs(dir), 1);
			}
			
		}
		else{
			double pickupPosition = itr->getPosition().y;
			double playerPosition = players[1].getPosition().y;
			double diff = pickupPosition - playerPosition;
			double dir = players[1].getDirection().y;
			if (dir * diff > 0){
				players[1].addScore(pickupCoefficient*abs(dir), 1);
			}
			else{
				players[1].addScore(-pickupCoefficient*abs(dir), 1);
			}
		}
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
				player->addScore(pickupBonus, 0);
				itr->destroy();
			}
		}
	}
}

void World::collisionDetection(sf::Time dt){
	for (auto player = players.begin(); player != players.end(); player++){
		sf::FloatRect rect = player->getBoundingRect();
		for (auto itr = lasers.begin(); itr != lasers.end(); itr++){
			sf::FloatRect laserRect = itr->getBoundingRect();
			int y = getLaserHeight(player->getPosition().x, *itr);
			sf::Vector2f impactPoint = sf::Vector2f(player->getPosition().x, y);
			if (rect.contains(impactPoint) 
					&& rect.intersects(laserRect) 
					&& player->getId() != itr->getId())
			{
				player->takeDammages(itr->getDammages(dt));
				players[1-player->getId()].addScore(laserBonus, 2);
			}
		}
	}
}

// get the point where the laser touch the other player axis
int World::getLaserHeight(int x, Laser laser) const{
	int x1 = laser.getPosition().x;
	int y1 = laser.getPosition().y;
	int x2 = x;
	double alpha = laser.getRotation();
	double beta = 180 - alpha;
	return y1 + abs(x2-x1)*tan(beta*3.14/180.f);
}

float World::getPerfectAngle(Character shooter, Character target){
	int deltaX = abs(shooter.getPosition().x - target.getPosition().x);
	int deltaY = shooter.getPosition().y - target.getPosition().y;
	return 180.0 + 180.0/3.14159*atan((double)deltaY/(double)deltaX);
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

std::pair<std::vector<double>, std::vector<double> > World::getDetailScores(){
	return std::pair<std::vector<double>, std::vector<double> >
		(players[0].getScoreVector() ,players[1].getScoreVector());
}


void World::setFinalScores(){
	/*
	if (players[0].getHealth() == 0){
		players[0].addScore(-maxScore);
		players[1].addScore(maxScore);
	}
	else if (players[1].getHealth() == 0){
		players[0].addScore(maxScore);
		players[1].addScore(-maxScore);
	}
	else{
		players[0].addScore(players[0].getHealth() - players[1].getHealth());
		players[1].addScore(players[1].getHealth() - players[0].getHealth());
	}
	players[0].setScore(players[0].getScore()/mTime.asSeconds());
	players[1].setScore(players[1].getScore()/mTime.asSeconds());
	*/
	players[0].addScore(players[0].getHealth() - players[1].getHealth(), 4);
	players[1].addScore(players[1].getHealth() - players[0].getHealth(), 4);
}

// return the values which we will give to the left neural network
std::vector<double> World::getImputs(int id){
	std::vector<double> result;
	double dimX = getWindowDimensions().x;
	double dimY = getWindowDimensions().y;

	// We transform the players positions into a value beetween -1 and 1
	result.push_back(-(2*players[id].getPosition().y - dimY)/dimY);
	result.push_back(-(2*players[1-id].getPosition().y - dimY)/dimY);

	if (id == 0){
		double angle = 180 - lasers[id].getRotation();
		if (angle < 0){
			angle += 360;
		}
		result.push_back(angle/360.0);
	}
	else{
		double angle = lasers[id].getRotation();
		result.push_back(angle/360.0);
	}
	
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

	return result;
}
