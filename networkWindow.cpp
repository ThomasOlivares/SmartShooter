#include "networkWindow.hpp"
#include "utility.hpp"

#include <iostream>
#include <math.h>

NetworkWindow::NetworkWindow(NeuralNetwork& network_)
: network(network_)
{
	initNeurons();
	initWeights();
}

void NetworkWindow::initNeurons(){
	int nbLayers = network.getNbLayers();
	double spaceX = (double)getNetworkWindowDimensions().x / (double)(nbLayers + 2);
	for (int numLayer = 0; numLayer < nbLayers; numLayer++){
		std::vector<sf::CircleShape> layer;
		int nbNeurons = network.getNbNeurons(numLayer)+1;
		if (numLayer == nbLayers-1){
			nbNeurons--;
		}
		double spaceY = (double)getNetworkWindowDimensions().y / (double)(nbNeurons + 2);
		for (int numNeuron = 0; numNeuron < nbNeurons; numNeuron++){
			sf::CircleShape neuron(10);
			neuron.setFillColor(sf::Color::Black);
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
			std::vector<sf::RectangleShape> temp2;
			for (int neuronSink = 0; neuronSink < nbNeuronsSink; neuronSink++){
				sf::Vector2f source = layers[numLayer][neuronSource].getPosition();
				sf::Vector2f sink = layers[numLayer+1][neuronSink].getPosition();
				float dist = distance(source, sink);
				sf::RectangleShape line(sf::Vector2f(dist, 1));
				line.setPosition(source);

				double value  = 255.0 - std::min(255.0, 50.0*(double)fabs(network.getWeight(numLayer, 
					neuronSource, neuronSink)));
				line.setFillColor(sf::Color(value, value, value));

				double angle = 180.0/3.14159*atan2(sink.y - source.y, sink.x - source.x);
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
		int nbNeurons = network.getNbNeurons(numLayer)+1;
		if(numLayer == nbLayers-1){
			nbNeurons--;
		}
		for (int numNeuron = 0; numNeuron < nbNeurons; numNeuron++){
			sf::CircleShape& neuron = layers[numLayer][numNeuron];
			double value  = network.getNeuronValue(numLayer, numNeuron);
			if (value > 0.5){
				neuron.setFillColor(sf::Color((int)(511.0*(value-0.5)), 0, 0));
			}
			else{
				neuron.setFillColor(sf::Color(0, (int)(511.0*(0.5-value)), 0));
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