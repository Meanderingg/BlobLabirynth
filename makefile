labyrinth: *.cpp
	g++ -o game.out  ./SRC/*.cpp *.cpp -lGLEW -lGL -lGLU -lglut -lSOIL -IINCLUDE

clean: rm *.out
