#include "train.hpp"
#include "applicationTrain.hpp"
#include "utility.hpp"

#include <cassert>
#include <random>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <string>

Train::Train(int nPopulation_, std::vector<int> neuronsPerLayer_)
: networks()
, nPopulation(nPopulation_)
, neuronsPerLayer(neuronsPerLayer_)
{
	// Initialisation of the randoms values
	time_t  timev;
	time(&timev);
	srand(timev);

	initPopulation(nPopulation, neuronsPerLayer);
}

void Train::initPopulation(int n, std::vector<int> neuronsPerLayer){
	for (int i = 0; i < n; i++){
		struct IA ia;
		ia.network = NeuralNetwork(neuronsPerLayer);
		ia.age = 1;
		ia.score = 0;
		networks.push_back(ia);
	}
}

void Train::describe(int index) const{
	std::cout << "ia n°" << index + 1 << std::endl;
	struct IA ia = networks[index];
	std::cout << "age : " << ia.age << std::endl;
	std::cout << "score : " << ia.score << std::endl;
}

void Train::run(int nIterations){
	for (int i = 0; i<nIterations; i++){
		std::cout << "---------------------------------" << std::endl;
		std::cout << "itération n°" << i+1 << "/" << nIterations << std::endl;
		play();
		selection();
		reproduction();
	}
	save(nIterations);
}

void Train::play(){
	std::vector<int> v = getRandomVector(nPopulation);
	//#pragma omp parallel for private(v) schedule(dynamic)
	for (int i = 0; i < nPopulation/2; i++){
		int first = v[2*i];
		int second = v[2*i+1];
		ApplicationTrain app(networks[first].network, networks[second].network);
		std::pair<double, double> scores = app.run();
		networks[first].score = scores.first;
		networks[first].age++;
		networks[second].score = scores.second;
		networks[second].age++;
	}
}

void Train::selection(){
	std::sort(networks.begin(), networks.end(), 
		[&](struct IA n1, struct IA n2){return n1.score > n2.score;});
	std::cout << "Best result : " << networks[0].score << std::endl;
	std::cout << "Worst result : " << networks[networks.size()-1].score << std::endl;
	double max = networks.size()*(100.f - pourcentageElimination)/100.f;
	while(networks.size() > max){
		networks.pop_back();
	}
	std::cout << "Worst selected result : " << networks[networks.size()-1].score << std::endl;
}

void Train::reproduction(){
	int size = networks.size();
	//#pragma omp parallel for private(size) schedule(dynamic)
	for(int i = size; i < nPopulation; i++){
		int p1 = selectParent(size);
		int p2 = selectParent(size);
		NeuralNetwork& n1 = networks[p1].network;
		NeuralNetwork& n2 = networks[p2].network;
		double alpha = (double)(rand()%1000)/1000.f;
		struct IA child;
		child.network = NeuralNetwork(n1, n2, alpha, mutationPerCent/100.f
			, mutationValue);
		child.age = 1;
		child.score = 0;
		networks.push_back(child);
	}
}

int Train::selectParent(int size){
	int max = rand()%(size);
	for (int i = 0; i<sizeTournament-1; i++){
		int randomIndex = rand()%(size);
		if (networks[randomIndex].score > networks[max].score)
		{
			max = randomIndex;
		}
	}
	return max;
}

void Train::save(int i){
	NeuralNetwork& best1 = networks[0].network;
	describe(0);
	std::string name = std::to_string(i) + ".txt";
	best1.save(name);

	NeuralNetwork& best2 = networks[1].network;
	describe(1);
	name = std::to_string(i) + "_bis.txt";
	best2.save(name);
}

int maxIndex(int tab[], int size){
	int maxIndex = 0;
	for (int i = 1; i<size; i++){
		if (tab[i] > tab[maxIndex]){
			maxIndex = i;
		}
	}
	return maxIndex;
}

std::vector<int> getRandomVector(int size){
	std::vector<int> res;
	for (int i = 0; i<size; i++){
		res.push_back(i);
	}
	
	std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(res.begin(), res.end(), g);

    return res;
}