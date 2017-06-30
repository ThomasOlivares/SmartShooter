#pragma once

#include "neuralNetwork.hpp"

#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class NetworkWindow : public sf::Drawable
{
	public :
							NetworkWindow(NeuralNetwork& network_);
		void 				update();
		virtual void 		draw(sf::RenderTarget& target, 
								sf::RenderStates states) const;

	private :
		void 				initNeurons();
		void 				initWeights();

	private :
		NeuralNetwork 												network;
		std::vector<std::vector<sf::CircleShape> >  				layers;
		std::vector<std::vector<std::vector<sf::RectangleShape> > > weights;
};