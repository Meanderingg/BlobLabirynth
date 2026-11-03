// #include <windows.h>
#include <stdlib.h>         
#include <stdio.h>
#include <GL/glew.h>        
#include <GL/freeglut.h>    

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

float angle = 0;
float tx = 0; float ty = 0;
float xMin = -960.f, xMax = 960.f, yMin = -540.f, yMax = 540.f;

bool keystates[256];


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
		tx += 10;
	}
	if (keystates['a']) {
		tx -= 10;
	}
	if (keystates['w']) {
		ty += 10;
	}
	if (keystates['s']) {
		ty -= 10;
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
		-32.0f, -32.0f, 0.0f, 0.0f,		
		32.0f, -32.0f, 0.0f, 0.0f,  	
		32.0f,  32.0f, 0.0f, 0.0f,  	
		-32.0f,  32.0f, 0.0f, 0.0f,  	

        /*
		-50.0f, -50.0f, 0.0f, 0.0f,		
		50.0f, -50.0f, 0.0f, 0.0f,		
		50.0f, 50.0f, 0.0f, 0.0f,		
		-50.0f, 50.0f, 0.0f, 0.0f,
        */

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
	handleMovement();
	
	glClear(GL_COLOR_BUFFER_BIT);

	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(tx, ty, 0.0));
	matrScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25, 0.25, 0.0));
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
