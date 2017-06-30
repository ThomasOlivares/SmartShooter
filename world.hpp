#pragma once

#include "character.hpp"
#include "pickup.hpp"
#include "bullet.hpp"
#include "laser.hpp"

#include <map>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

class World : public sf::Drawable
{
	public :
		enum Texture{
			PlayerT, 
			PickupT, 
			BulletT, 
			TextureCount
		};

	public : 
						World();
		void 			initPlayers();
		void 			initTextures();
		void 			initFonts();
		void 			load(Texture name, char* pathname);
		void 			handleEvent(sf::Event& event);
		void 			handleEvent(std::vector<double> decision1, 
							std::vector<double> decision2);
		void 			createBullet(Character& player, sf::Texture& texture, 
							int direction);
		void 			orientLaser(Character& player, double value);
		virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool 			update(sf::Time dt);
		void 			checkPlayerOutWindow(Character& player);
		void 			collectPickups();
		void 			collisionDetection();
		void			destroyEntities();
		void 			addPickups(int max);
		bool 			checkGameOver();
		std::pair<int, int> getFinalScores();
		void 			setFinalScores();
		std::vector<double> getImputs(int id);

	private :
		std::map<Texture, sf::Texture>			textures;
		sf::Font 								mFont;
		std::vector<Character> 					players;
		std::vector<Pickup> 					pickups;
		std::vector<Laser>  					lasers;
		sf::Time 								mTime;
};
