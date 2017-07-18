#pragma once

#include <vector>
#include <string>

class NeuralNetwork{
	
	public :
						NeuralNetwork();
						NeuralNetwork(std::vector<int> neuronPerLayer_);
						NeuralNetwork(std::vector<int> neuronPerLayer_, double wValue);
						NeuralNetwork(char* pathname);
						NeuralNetwork(NeuralNetwork& p1, NeuralNetwork& p2, double alpha, 
							double mutationPourcent, double mutationMaxValue);

	public :
		void 				initStructure();
		double 				getWeight(int numLayer, int i, int j) const;
		void 				setWeight(int numTheta, int i, int j, double modif);
		void 				setImput(std::vector<double> tab);
		void 				setImput(double value);
		void 				initWeights();
		void 				initWeights(double wValue);
		void 				initWeights(NeuralNetwork& p1, NeuralNetwork& p2, double alpha, 
								double mutationPourcent, double mutationMaxValue);
		void 				computeLayers();
		std::vector<double> output() const;
		void 				printWeight() const;
		int 				getNbLayers() const;
		int 				getNbNeurons(int num) const;
		double 				getNeuronValue(int layer, int neuron) const;
		void 				save(std::string name);

	protected :
		int 												nbLayers;
		std::vector<int> 									neuronPerLayer;
		std::vector<std::vector<double> > 					layers;
		std::vector<std::vector<std::vector<double> > > 	weight;
};

double sigmoid(double z);
