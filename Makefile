FLAG=-lsfml-graphics \
	 -lsfml-window \
	 -lsfml-system

CLASSES=application.o \
		applicationTrain.o \
		character.o \
		laser.o \
		main.o \
		networkWindow.o \
		neuralNetwork.o \
		pickup.o \
		train.o \
		utility.o \
		world.o

COMPILER=g++

LDFLAGS=-O3

RDFLAGS=-std=c++11

all : main

main : $(CLASSES)
	$(COMPILER) $(LDFLAGS) $(CLASSES) -o SmartShooter $(RDFLAGS) $(FLAG)

application.o : application.cpp application.hpp
	$(COMPILER) $(LDFLAGS) -c application.cpp $(RDFLAGS)

applicationTrain.o : applicationTrain.cpp applicationTrain.hpp
	$(COMPILER) $(LDFLAGS) -c applicationTrain.cpp $(RDFLAGS)

character.o : character.cpp character.hpp
	$(COMPILER) $(LDFLAGS) -c character.cpp $(RDFLAGS)

laser.o : laser.cpp laser.hpp
	$(COMPILER) $(LDFLAGS) -c laser.cpp $(RDFLAGS)

main.o : main.cpp
	$(COMPILER) $(LDFLAGS) -c main.cpp $(RDFLAGS)

networkWindow.o : networkWindow.cpp networkWindow.hpp
	$(COMPILER) $(LDFLAGS) -c networkWindow.cpp $(RDFLAGS)

neuralNetwork.o : neuralNetwork.cpp neuralNetwork.hpp
	$(COMPILER) $(LDFLAGS) -c neuralNetwork.cpp $(RDFLAGS)

pickup.o : pickup.cpp pickup.hpp
	$(COMPILER) $(LDFLAGS) -c pickup.cpp $(RDFLAGS)

train.o : train.cpp train.hpp
	$(COMPILER) $(LDFLAGS) -c train.cpp $(RDFLAGS)

utility.o : utility.cpp utility.hpp
	$(COMPILER) $(LDFLAGS) -c utility.cpp $(RDFLAGS)

world.o : world.cpp world.hpp
	$(COMPILER) $(LDFLAGS) -c world.cpp $(RDFLAGS)

clean : 
	rm *.o SmartShooter