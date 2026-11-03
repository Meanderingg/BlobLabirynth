// #include <windows.h>
#include <stdlib.h>         
#include <stdio.h>
#include <GL/glew.h>        
#include <GL/freeglut.h>    

#include <iostream>
#include "loadShaders.h"	
#include "glm/glm.hpp"		
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SOIL.h"	

GLuint
	VaoId,
	VboPositions,
	VboColors,
	VboTexCoords,
	EboId,
	ColorBufferId,
	ProgramId,
	myMatrixLocation,
	matrTranslLocation,
	matrRotlLocation,
	matrScaleLocation,
	texture;

GLfloat
	winWidth = 1920, winHeight = 1080;

glm::mat4
	myMatrix, resizeMatrix, matrTransl, matrRot, matrScale;

// Environment variables
float angle = 0;
float positionX = 0, positionY = 0;
int directionX, directionY;

// Screen size
float xMin = -960.f, xMax = 960.f, yMin = -540.f, yMax = 540.f;

// Sprite size
float spriteWidth = 64.0f;
float spriteHeight = 64.0f;

// Movement speed
float speed = 10.f;

bool keystates[256];

// Frame counter
int tomas_idea = 0;

glm::vec4 calculateBorders(float posX, float posY, float spriteW, float spriteH)
{
    return glm::vec4(posX + spriteW / 2, posX - spriteW / 2, posY + spriteH / 2, posY - spriteH / 2);
}

bool screenCollision(float posX, float posY)
{
    glm::vec4 borders = calculateBorders(posX, posY, spriteWidth, spriteHeight); 
    if (borders[0] > xMax || borders[1] < xMin || borders[2] > yMax || borders[3] < yMin)
        return true;
    else
        return false;
} 

void collisionDetection(float widthA, float widthB, float heightA, float heightB)
{
    ;   
}
void NormalKeyDown(unsigned char key, int _, int __)
{
	keystates[key] = true;
}

void NormalKeyUp(unsigned char key, int _, int __)
{
	keystates[key] = false;
}

void LoadTexture(const char* texturePath)
{

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void handleMovement() {
	if (keystates['d']) {
		directionX = 1;
	}

	if (keystates['a']) {
        directionX = -1;
	}

	if (keystates['w']) {
        directionY = 1;
	}

	if (keystates['s']) {
        directionY = -1;
	}

    float newPositionX = positionX + directionX * speed;
    float newPositionY = positionY + directionY * speed;

    if(! screenCollision(newPositionX, newPositionY))
    {
        positionX = newPositionX;
        positionY = newPositionY;
    }
}

void CreateShaders(void)
{
	ProgramId = LoadShaders(ASSET_DIR "/shader.vert", ASSET_DIR "/shader.frag");
	glUseProgram(ProgramId);
}

void CreateVBO(void)
{

	GLfloat Vertices[] = {
		-spriteWidth / 2, -spriteHeight / 2, 0.0f, 1.0f,		
		spriteWidth / 2, -spriteHeight / 2, 0.0f, 1.0f,		
		spriteWidth / 2, spriteHeight / 2, 0.0f, 1.0f,		
		-spriteWidth / 2, spriteHeight / 2, 0.0f, 1.0f,		
	};

	GLfloat Colors[] = {
 		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 0.0f,
	};

	GLfloat TexCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
	};

	GLuint Indices[] = {
	  0, 1, 2,
	  0, 2, 3
	};

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboPositions);
	glBindBuffer(GL_ARRAY_BUFFER, VboPositions);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &VboColors);
	glBindBuffer(GL_ARRAY_BUFFER, VboColors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &VboTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, VboTexCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords), TexCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &EboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void DestroyVBO(void)
{

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboPositions);
	glDeleteBuffers(1, &VboColors);
	glDeleteBuffers(1, &VboTexCoords);
	glDeleteBuffers(1, &EboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	CreateVBO();

	LoadTexture(ASSET_DIR "/assets/blob.png");

	CreateShaders();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");

	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);
}

void RenderFunction(void)
{
	tomas_idea++;
	
	if (tomas_idea % 3 == 0)
		handleMovement();
	
	glClear(GL_COLOR_BUFFER_BIT);

	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(positionX, positionY, 0.0));
	matrScale = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 0.0));
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));

	myMatrix = resizeMatrix * matrScale * matrTransl * matrRot;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glutSwapBuffers();
	glFlush();
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Utilizarea texturilor");

	glewInit();

	Initialize();
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutKeyboardFunc(NormalKeyDown);
	glutKeyboardUpFunc(NormalKeyUp);
	glutCloseFunc(Cleanup);

	glutMainLoop();

	return 0;
}
