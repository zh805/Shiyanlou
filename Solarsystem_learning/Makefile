CXX = g++
EXEC = solarsystem
SOURCES = main.cpp stars.cpp solarsystem.cpp
OBJECTS = main.o stars.o solarsystem.o
LDFLAGS = -lglut -lGL -lGLU -std=c++11

all :
	$(CXX) $(SOURCES) $(LDFLAGS) -o $(EXEC)

clean:
	rm -f $(EXEC) *.gdb *.o
