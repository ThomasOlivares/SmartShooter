#include "application.hpp"
#include "train.hpp"

#include <stdexcept>
#include <iostream>
#include <string.h>

int main(int argc, char* argv[])
{
	if (argc <= 1){
	}
	else if (!strcmp("train", argv[1]) || !strcmp("t", argv[1]))
	{
		Train trainHandler(50, {5, 10, 8, 2});
		trainHandler.run(20);
	}
	else if (!strcmp("play", argv[1]) || !strcmp("p", argv[1]))
	{
		Application app(argv[2], argv[3]);
		app.run();
	}
}