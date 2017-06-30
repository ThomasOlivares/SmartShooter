#include "networkWindow.hpp"
#include "utility.hpp"

#include <math.h>

NetworkWindow::NetworkWindow(NeuralNetwork& network_)
: network(network_)
{
	initNeurons();
}

void NetworkWindow::initNeurons(){
	int nbLayers = network.getNbLayers();
	int spaceX = (nbLayers + 2) / getNetworkWindowDimensions().x;
	for (int numLayer = 0; numLayer < nbLayers; numLayer++){
		std::vector<sf::CircleShape> layer;
		int nbNeurons = network.getNbNeurons(numLayer);
		int spaceY = (nbNeurons + 2) / getNetworkWindowDimensions().y;
		for (int numNeuron = 0; numNeuron < nbNeurons; numNeuron++){
			sf::CircleShape neuron(10);
			neuron.setFillColor(sf::Color::White);
			neuron.setPosition((numLayer+1)*spaceX, (numNeuron+1)*spaceY);
			layer.push_back(neuron);
		}
		layers.push_back(layer);
	}
}

void NetworkWindow::initWeights(){
	int nbLayers = layers.size();
	for (int numLayer = 0; numLayer < nbLayers - 1; numLayer++){
		int nbNeuronsSource = layers[numLayer].size();
		std::vector<std::vector<sf::RectangleShape> > temp;
		for (int neuronSource = 0; neuronSource < nbNeuronsSource; neuronSource++){
			int nbNeuronsSink = layers[numLayer+1].size();
			// We don't compute the constant neuron
			if (numLayer!= nbLayers - 2){
				nbNeuronsSink--;
			}
			std::vector<sf::RectangleShape> temp2;
			for (int neuronSink = 0; neuronSink < nbNeuronsSource; neuronSink++){
				sf::Vector2f source = layers[numLayer][neuronSource].getPosition();
				sf::Vector2f sink = layers[numLayer+1][neuronSink].getPosition();
				float dist = distance(source, sink);
				sf::RectangleShape line(sf::Vector2f(dist, 5));
				line.setPosition(source);
				double angle = atan2(sink.y - source.y, sink.x - source.x);
				line.rotate(angle);
				temp2.push_back(line);
			}
			temp.push_back(temp2);
		}
		weights.push_back(temp);
	}
}

void NetworkWindow::update(){
	int nbLayers = network.getNbLayers();
	for (int numLayer = 0; numLayer < nbLayers; numLayer++){
		int nbNeurons = network.getNbNeurons(numLayer);
		for (int numNeuron = 0; numNeuron < nbNeurons; numNeuron++){
			sf::CircleShape& neuron = layers[numLayer][numNeuron];
			double value  = network.getNeuronValue(numLayer, numNeuron);
			if (value > 0){
				neuron.setFillColor(sf::Color((int)value, 0, 0));
			}
			else{
				neuron.setFillColor(sf::Color(0, (int)(-value), 0));
			}
		}
	}
}

void NetworkWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for (auto itr = layers.begin(); itr != layers.end(); itr++){
		for (auto itr2 = itr->begin(); itr2 != itr->end(); itr2++){
			target.draw(*itr2);
		}
	}
	for (auto itr = weights.begin(); itr != weights.end(); itr++){
		for (auto itr2 = itr->begin(); itr2 != itr->end(); itr2++){
			for (auto itr3 = itr2->begin(); itr3 != itr2->end(); itr3++){
				target.draw(*itr3);
			}
		}
	}
}