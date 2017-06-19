#pragma once

#include "character.hpp"
#include "pickup.hpp"
#include "bullet.hpp"

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
		void 			createBullet(Character player, sf::Texture& texture, 
			int direction);
		virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		int 			update(sf::Time dt);
		void 			checkPlayerOutWindow(Character& player);
		void 			collectPickups();
		void 			collisionDetection();
		void			destroyEntities();
		void 			addPickups(int max);
		int 			checkGameOver();

	private :
		std::map<Texture, sf::Texture>			textures;
		sf::Font 								mFont;
		std::vector<Character> 					players;
		std::vector<Pickup> 					pickups;
		std::vector<Bullet> 					bullets;
};
