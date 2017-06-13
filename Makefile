FLAG=-lsfml-graphics \
	 -lsfml-window \
	 -lsfml-system

CLASSES=application.o \
		character.o \
		main.o \
		utility.o \
		world.o

COMPILER=g++

LDFLAGS=-g

RDFLAGS=-std=c++14

all : main

main : $(CLASSES)
	$(COMPILER) $(LDFLAGS) $(CLASSES) -o SmartShooter $(RDFLAGS) $(FLAG)

application.o : application.cpp
	$(COMPILER) $(LDFLAGS) -c application.cpp $(RDFLAGS)

character.o : character.cpp
	$(COMPILER) $(LDFLAGS) -c character.cpp $(RDFLAGS)

main.o : main.cpp
	$(COMPILER) $(LDFLAGS) -c main.cpp $(RDFLAGS)

utility.o : utility.cpp
	$(COMPILER) $(LDFLAGS) -c utility.cpp $(RDFLAGS)

world.o : world.cpp
	$(COMPILER) $(LDFLAGS) -c world.cpp $(RDFLAGS)

clean : 
	rm *.o SmartShooter