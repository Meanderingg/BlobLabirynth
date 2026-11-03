labyrinth: *.cpp
	g++ -o lab.out  ./SRC/*.cpp *.cpp -lGLEW -lGL -lGLU -lglut -lSOIL -IINCLUDE

clean: rm *.out
