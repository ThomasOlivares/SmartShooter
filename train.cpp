#include "train.hpp"
#include "applicationTrain.hpp"

#include <random>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <string>

Train::Train(int nPopulation_, std::vector<int> neuronsPerLayer_)
: nPopulation(nPopulation_)
, neuronsPerLayer(neuronsPerLayer_)
{
	// Initialisation of the randoms values
	time_t  timev;
	time(&timev);
	srand(timev);

	initPopulation(nPopulation_, neuronsPerLayer);
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
	for (int i = 0; i < nPopulation/2; i++){
		int first = v[v.size() - 1];
		v.pop_back();
		int second = v[v.size() - 1];
		v.pop_back();
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

	double score = networks[0].score;
	double Maxscore = networks[0].score;
	int count = 0;
	for (auto itr = ++networks.begin(); itr != networks.end(); ){
		if (score == itr->score){
			itr = networks.erase(itr);
			count++;
		}
		else if(itr->score > Maxscore ){
			std::cout << "sorting failed" << std::endl;
			exit(EXIT_FAILURE);
		}
		else{
			score = itr->score;
			itr++;
		}
	}
	std::cout << count << " duplicates removed" << std::endl;
	double max = networks.size()*(100.f - pourcentageElimination)/100.f;
	while(networks.size() > max){
		networks.pop_back();
	}
	std::cout << "new size : " << networks.size() << std::endl;
	std::cout << "Best result : " << networks[0].score << std::endl;
	std::cout << "Worst result : " << networks[networks.size()-1].score << std::endl;
}

void Train::reproduction(){
	int size = networks.size();
	for(int i = networks.size(); i < nPopulation; i++){
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
	int randomsIndexes[sizeTournament];
	for (int i = 0; i<sizeTournament; i++){
		randomsIndexes[i] = rand()%(size);
	}
	return maxIndex(randomsIndexes, sizeTournament);
}

void Train::save(int i){
	NeuralNetwork& best = networks[0].network;
	best.setImput(1);
	best.computeLayers();
	double value = best.output()[0];
	std::cout << "ret value : " << value << std::endl;
	std::string name = "Best_with_" + std::to_string(i) + "_iterations.txt";
	best.save(name);
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
    for (int i = 0; i<size; i++){
		std::cout << res[i];
	}
	std::cout << std::endl;
}