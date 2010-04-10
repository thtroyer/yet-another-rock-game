CC=g++
CFLAGS=-lSDL -lGL -lGLU -lpthread -lSDL -lfreetype -lftgl -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS=-g -I/usr/include/SDL
SOURCES=MyLine.cpp MyLine.h MyPoint.cpp MyPoint.h Rock.h Rock.cpp Ship.cpp Ship.h Shot.cpp Shot.h WarpEffect.h WarpEffect.cpp Game.h Game.cpp random.h 
OBJECTS= Level.o MyLine.o MyPoint.o Rock.o Ship.o Shot.o WarpEffect.o Game.o random.o 

yarg: main.o $(OBJECTS)
	$(CC) main.o $(OBJECTS) $(CFLAGS) -o yarg

main.o: main.cpp 
	$(CC) -c $(LDFLAGS) main.cpp

Level.o : Level.cpp Level.h
	$(CC) -c $(LDFLAGS) Level.cpp

MyLine.o : MyLine.cpp MyLine.h
	$(CC) -c $(LDFLAGS) MyLine.cpp

MyPoint.o : MyPoint.cpp MyPoint.h
	$(CC) -c $(LDFLAGS) MyPoint.cpp

Rock.o : Rock.cpp Rock.h
	$(CC) -c $(LDFLAGS) Rock.cpp

Ship.o : Ship.cpp Ship.h
	$(CC) -c $(LDFLAGS) Ship.cpp

Shot.o : Shot.cpp Shot.h
	$(CC) -c $(LDFLAGS) Shot.cpp

WarpEffect.o : WarpEffect.cpp WarpEffect.h
	$(CC) -c $(LDFLAGS) WarpEffect.cpp

Game.o : Game.cpp Game.h
	$(CC) -c $(LDFLAGS) Game.cpp

random.o : random.h random.cpp
	$(CC) -c random.cpp

warn: main.cpp
	$(CC) -Wall $(LDFLAGS) $(CFLAGS) main.cpp

error: main.cpp
	$(CC) -Wall -pendantic $(CFLAGS) main.cpp

clean:
	rm *.o yarg
