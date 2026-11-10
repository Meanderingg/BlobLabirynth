// #include <windows.h>
#include <GL/glew.h>        
#include <GL/freeglut.h>    
#include <iostream>
#include "glm/glm.hpp"		
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Game.h"

std::unique_ptr<Game> game;

GLfloat
	winWidth = 1920, winHeight = 1080;

// Frame counter
int tomas_idea = 0;

void Cleanup(Game* game)
{
	delete game;
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("BlobLabyrinth");

	glewInit();

    std::cout<<"???";
	game = std::make_unique<Game>();
	game->CreateShaders();
	game->CreateObjects();

	glutDisplayFunc([] { game->render(); });
	glutIdleFunc([] { game->update(); game->render(); });
	glutKeyboardFunc([](unsigned char key, int x, int y) { game->KeyDown(key, x, y); });
	glutKeyboardUpFunc([](unsigned char key, int x, int y) { game->KeyUp(key, x, y); });
	glutCloseFunc([] { game.reset(); });

	glutMainLoop();
	return 0;
}
