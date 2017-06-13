FLAG=-lsfml-graphics \
	 -lsfml-window \
	 -lsfml-system

CLASSES=application.o \
		main.o \

COMPILER=g++

LDFLAGS=-g

RDFLAGS=-std=c++14

all : main

main : $(CLASSES)
	$(COMPILER) $(LDFLAGS) $(CLASSES) -o SmartShooter $(RDFLAGS) $(FLAG)

application.o : application.cpp
	$(COMPILER) $(LDFLAGS) -c application.cpp $(RDFLAGS)

main.o : main.cpp
	$(COMPILER) $(LDFLAGS) -c main.cpp $(RDFLAGS)

clean : 
	rm *.o BrickBreaker