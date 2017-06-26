#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <iostream>
#include <cassert>
#include "neuralNetwork.hpp"

using namespace std;

NeuralNetwork::NeuralNetwork()
: nbLayers(0)
{
}

NeuralNetwork::NeuralNetwork(vector<int> neuronPerLayer_) 
: nbLayers(neuronPerLayer_.size())
{
	for (int i = 0; i<nbLayers; i++){
		neuronPerLayer.push_back(neuronPerLayer_[i]);
	}
	initStructure();
	initWeights();
}

/*We initialize all the weight values to wValue*/
NeuralNetwork::NeuralNetwork(vector<int> neuronPerLayer_, double wValue) 
: nbLayers(neuronPerLayer_.size())
{
	for (int i = 0; i<nbLayers; i++){
		neuronPerLayer.push_back(neuronPerLayer_[i]);
	}
	initStructure();
	initWeights(wValue);
}

NeuralNetwork::NeuralNetwork(char* pathname)
{
	FILE* f = fopen(pathname, "r");
	int temp;
	fread(&temp, sizeof(int), 1, f);
	nbLayers = temp;
	for (int numLayer = 0; numLayer < nbLayers; numLayer++){
		int temp;
		fread(&temp, sizeof(int), 1, f);
		neuronPerLayer.push_back(temp);
	}
	initStructure();
	for (int numLayer = 0; numLayer<layers.size()-1; numLayer++){
		std::vector<std::vector<double> > weightOnLayer;
		for (int i= 0; i<neuronPerLayer[numLayer]+1; i++){
			std::vector<double> weightOnNeuron;
			for (int j = 0 ; j<neuronPerLayer[numLayer+1]; j++){
				double temp;
				fread(&temp, sizeof(double), 1, f);
				weightOnNeuron.push_back(temp);
			}
			weightOnLayer.push_back(weightOnNeuron);
		}
		weight.push_back(weightOnLayer);
	}
	fclose(f);
}

NeuralNetwork::NeuralNetwork(NeuralNetwork& p1, NeuralNetwork& p2, double alpha, 
		double mutationPourcent, double mutationMaxValue)
: nbLayers(p1.getNbLayers())
{
	for (int i = 0; i<nbLayers; i++){
		neuronPerLayer.push_back(p1.getNbNeurons(i));
	}
	initStructure();
	initWeights(p1, p2, alpha, mutationPourcent, mutationMaxValue);
}

double NeuralNetwork::getWeight(int numLayer, int i, int j) const{
	assert(numLayer < nbLayers);
	assert(i < weight[numLayer].size());
	assert(j < weight[numLayer][i].size());
	return weight[numLayer][i][j];
}

void NeuralNetwork::setWeight(int numTheta, int i, int j, double modif){
	weight[numTheta][i][j] = modif;
}

void NeuralNetwork::initStructure(){
	for(int i = 0; i<nbLayers; i++){
		int nbNeurons = neuronPerLayer[i];
		vector<double> layer;
		for (int j = 0; j<nbNeurons; j++){
			layer.push_back(0);
		}

		// We push the constant neuron, except for the output layer
		if (i != nbLayers - 1){
			layer.push_back(1); // Constant neuron
		}
		
		layers.push_back(layer);
	}	
}
/* Initialisation of the input layer using the data from the game
*/
void NeuralNetwork::setImput(vector<double> tab){
	if (tab.size() != layers[0].size() - 1){ // -1 for constant neuron
		std::cerr << "size of given imputs(" << tab.size()  <<
			") doesn't fetch size of neural network(" << layers[0].size() - 1 << 
			")" <<std::endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i<tab.size(); i++){
		layers[0][i] = tab[i];
	}
}

void NeuralNetwork::setImput(double value){
	for (int i = 0; i<layers[0].size()-1; i++){
		layers[0][i] = value;
	}
}

/* Random initialisation of all the weight of the neural network
*/
void NeuralNetwork::initWeights(){
	for (int numCouche = 0; numCouche < nbLayers - 1; numCouche++){
		// Here we have all the weight beetween two layers
		vector<vector<double> > theta;
		for(int i = 0; i<neuronPerLayer[numCouche]+1; i++){
			// Here we have all the weight of the connexions send by one neural
			vector<double> neuralWeight;
			for (int j = 0; j < neuronPerLayer[numCouche+1]; j++){
				double weight = (double)(rand()%10000)/10000.f
							  - (double)(rand()%10000)/10000.f;
				neuralWeight.push_back(weight);
			}
			theta.push_back(neuralWeight);
		}
		weight.push_back(theta);
	}
}

/* Initialisation of the weight of the neural network using the data in argument
*/
void NeuralNetwork::initWeights(double wValue){
	for (int numCouche = 0; numCouche < nbLayers - 1; numCouche++){
		// Here we have all the weight beetween two layers
		vector<vector<double> > theta;
		for(int i = 0; i<neuronPerLayer[numCouche]+1; i++){
			// Here we have all the weight of the connexions send by one neural
			vector<double> neuralWeight;
			for (int j = 0; j < neuronPerLayer[numCouche+1]; j++){
				neuralWeight.push_back(wValue);
			}
			theta.push_back(neuralWeight);
		}
		weight.push_back(theta);
	}
}

/* Creation of a weight using others from 2 neural networks*/
void NeuralNetwork::initWeights(NeuralNetwork& p1, NeuralNetwork& p2, double alpha, 
		double mutationPourcent, double mutationMaxValue)
{
	for (int numLayer = 0; numLayer < nbLayers - 1; numLayer++){
		// Here we have all the weight beetween two layers
		vector<vector<double> > theta;
		for(int i = 0; i<neuronPerLayer[numLayer]+1; i++){
			// Here we have all the weight of the connexions send by one neural
			vector<double> neuralWeight;
			for (int j = 0; j < neuronPerLayer[numLayer+1]; j++){
				double weight = alpha*p1.getWeight(numLayer, i, j)
							  + (1-alpha)*p2.getWeight(numLayer, i, j);
				if ((double)(rand()%1000)/1000.f < mutationPourcent){
					weight += mutationMaxValue * ((double)(rand()%1000/1000.f) - 
												  (double)(rand()%1000/1000.f));
				}
				neuralWeight.push_back(weight);
			}
			theta.push_back(neuralWeight);
		}
		weight.push_back(theta);
	}
}

/* We calculate all the values of neurons using the fisrt layer and the weight
*/
void NeuralNetwork::computeLayers(){
	// We begin at 1 because layer 0 is already completed
	for (int numLayer = 1; numLayer<nbLayers; numLayer++){
		vector<double> previous = layers[numLayer-1];

		// If we are not on the last layer we don't compute the last neural (constant)
		int max = layers[numLayer].size();
		if (numLayer != nbLayers-1){
			max--;
		}

		for (int i = 0; i<max; i++){
			double value = 0;  //value of one neuron
			for (int j = 0; j<previous.size(); j++){
				value += (double)((previous)[j]) * weight[numLayer-1][j][i];
			}
			value = sigmoid(value);
			layers[numLayer][i] = value;
		}
	}
}

/* Return the last layer (output layer)
*/
vector<double> NeuralNetwork::output() const{

	return layers[nbLayers-1];
}

void NeuralNetwork::printWeight() const{
	for (int numLayer = 0; numLayer<weight.size(); numLayer++){
		cout << "theta : " << numLayer << endl;
		for (int i= 0; i<neuronPerLayer[numLayer]; i++){
			for (int j = 0 ; j<neuronPerLayer[numLayer+1]; j++){
				cout << weight[numLayer][i][j] << " / ";
			}
		}
	cout << endl;
	}
}

int NeuralNetwork::getNbLayers() const{
	return nbLayers;
}

int NeuralNetwork::getNbNeurons(int num) const{
	return neuronPerLayer[num];
}

void NeuralNetwork::save(string name){
	FILE* f = fopen(name.c_str(), "w");
	fwrite(&nbLayers, sizeof(int), 1, f);
	for (int numLayer = 0; numLayer < nbLayers; numLayer++){
		int temp = neuronPerLayer[numLayer];
		fwrite(&temp, sizeof(int), 1, f);
	}
	for (int numLayer = 0; numLayer<weight.size(); numLayer++){
		for (int i= 0; i<neuronPerLayer[numLayer]+1; i++){
			for (int j = 0 ; j<neuronPerLayer[numLayer+1]; j++){
				double temp = weight[numLayer][i][j];
				fwrite(&temp, sizeof(double), 1, f);
			}
		}
	}
	fclose(f);
}


double sigmoid(double z){
	return 1/(1+exp(-z));
}
