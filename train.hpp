#pragma once

#include "neuralNetwork.hpp"

struct IA{
	NeuralNetwork network;
	double score;
	int age; // could be removed if not used
};

class Train
{
	public :
							Train(int nPopulation_, std::vector<int> neuronsPerLayer_);
		void 				run(int nIterations);

	private :
		void 				initPopulation(int n, std::vector<int> neuronsPerLayer);
		void 				describe() const;
		void 				play();
		void 				selection();
		void 				reproduction();
		int 				selectParent(int size);
		void 				save(int i);

	private :
		std::vector<struct IA> 	networks;
		int 					nPopulation;
		std::vector<int> 		neuronsPerLayer;
};

int 				maxIndex(int tab[], int size);
std::vector<int> 	getRandomVector(int size);