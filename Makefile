FLAG=-lsfml-graphics \
	 -lsfml-window \
	 -lsfml-system

CLASSES=application.o \
		bullet.o \
		character.o \
		main.o \
		pickup.o \
		utility.o \
		world.o

COMPILER=g++

LDFLAGS=-g

RDFLAGS=-std=c++11

all : main

main : $(CLASSES)
	$(COMPILER) $(LDFLAGS) $(CLASSES) -o SmartShooter $(RDFLAGS) $(FLAG)

application.o : application.cpp
	$(COMPILER) $(LDFLAGS) -c application.cpp $(RDFLAGS)

bullet.o : bullet.cpp
	$(COMPILER) $(LDFLAGS) -c bullet.cpp $(RDFLAGS)

character.o : character.cpp
	$(COMPILER) $(LDFLAGS) -c character.cpp $(RDFLAGS)

main.o : main.cpp
	$(COMPILER) $(LDFLAGS) -c main.cpp $(RDFLAGS)

pickup.o : pickup.cpp
	$(COMPILER) $(LDFLAGS) -c pickup.cpp $(RDFLAGS)

utility.o : utility.cpp
	$(COMPILER) $(LDFLAGS) -c utility.cpp $(RDFLAGS)

world.o : world.cpp
	$(COMPILER) $(LDFLAGS) -c world.cpp $(RDFLAGS)

clean : 
	rm *.o SmartShooter