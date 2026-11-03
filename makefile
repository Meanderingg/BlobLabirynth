1: 04_01*
	g++ -o 1  ./SRC/*.cpp 04_01*.cpp -lGLEW -lGL -lGLU -lglut -IINCLUDE

2: 04_02*
	g++ -o 2  ./SRC/*.cpp 04_02*.cpp -lGLEW -lGL -lGLU -lglut -IINCLUDE

3: 04_03*
	g++ -o 3  ./SRC/*.cpp 04_03*.cpp -lGLEW -lGL -lGLU -lglut -IINCLUDE

4: 04_04*
	g++ -o 4  ./SRC/*.cpp 04_04*.cpp -lGLEW -lGL -lGLU -lglut -lSOIL -IINCLUDE

5: 04_05* 04_02*
	g++ -o 5  ./SRC/*.cpp 04_05*.cpp -lGLEW -lGL -lGLU -lglut -lSOIL -IINCLUDE
