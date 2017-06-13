#include "world.hpp"
#include "utility.hpp"

#include <iostream>

World::World()
: mPlayer(200, 200)
{

}

void World::update(sf::Time dt, sf::Vector2f dir){
	mPlayer.update(dt, dir);
	checkPlayerOutWindow();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	mPlayer.draw(target, states);
}

/* If the player wants to go outside the window, we keep it inside
Later we could use a return value to train the neural network*/
void World::checkPlayerOutWindow(){
	int y = mPlayer.getBoundingRect().top;
	int height = mPlayer.getBoundingRect().height;
	if (y < 0){
		mPlayer.setPosition(mPlayer.getPosition().x, 0);
	}
	else if (y + height > getWindowDimensions().y){
		mPlayer.setPosition(mPlayer.getPosition().x, getWindowDimensions().y - height);
	}
}