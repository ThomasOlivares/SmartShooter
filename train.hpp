#pragma once

#include "neuralNetwork.hpp"

// During selection, size of the list of candidates (chosen randomly)
#define sizeTournament 2

// Poucentage of networks removed after selection
#define pourcentageElimination 50

#define mutationPerCent 10.f
#define mutationValue 1

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