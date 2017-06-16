#pragma once

#include "character.hpp"
#include "pickup.hpp"

#include <map>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

class World : public sf::Drawable
{
	public :
		enum Texture{
			Player, 
			Health, 
			TextureCount
		};

	public : 
						World();
		void 			initPlayers();
		void 			initTextures();
		virtual void 	draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void 			update(sf::Time dt, sf::Vector2f dir);
		void 			checkPlayerOutWindow(Character& player);
		void 			collectPickups();
		void			destroyEntities();
		void 			addPickups(int max);

	private :
		std::map<Texture, sf::Texture>			textures;
		std::vector<Character> 					players;
		std::vector<Pickup> 					pickups;
};
