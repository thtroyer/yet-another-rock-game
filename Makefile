CC=g++
CFLAGS=-lSDL -lGL -lGLU -lpthread -lSDL -lSDL_gfx 
LDFLAGS=-g -I/usr/include/SDL
HEADERS=MyLine.cpp MyLine.h MyPoint.cpp MyPoint.h Rock.h Rock.cpp Ship.cpp Ship.h Shot.cpp Shot.h Game.h Game.cpp random.h 
OBJECTS= Level.o MyLine.o MyPoint.o Rock.o Ship.o Shot.o Game.o random.o 

yarg: main.o $(OBJECTS)
	g++ main.o $(OBJECTS) $(CFLAGS) -o yarg

main.o: main.cpp $(HEADERS) 
	g++ -c $(LDFLAGS) main.cpp

Level.o : Level.cpp Level.h
	g++ -c $(LDFLAGS) Level.cpp

MyLine.o : MyLine.cpp MyLine.h
	g++ -c $(LDFLAGS) MyLine.cpp

MyPoint.o : MyPoint.cpp MyPoint.h
	g++ -c $(LDFLAGS) MyPoint.cpp

Rock.o : Rock.cpp Rock.h
	g++ -c $(LDFLAGS) Rock.cpp

Ship.o : Ship.cpp Ship.h
	g++ -c $(LDFLAGS) Ship.cpp

Shot.o : Shot.cpp Shot.h
	g++ -c $(LDFLAGS) Shot.cpp

Game.o : Game.cpp Game.h
	g++ -c $(LDFLAGS) Game.cpp

random.o : random.h random.cpp
	g++ -c random.cpp

warn: main.cpp
	g++ -Wall $(LDFLAGS) $(CFLAGS) main.cpp

error: main.cpp
	g++ -Wall -pendantic $(CFLAGS) main.cpp

clean:
	rm *.o yarg
