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
	VboId,
	EboId,
	ColorBufferId,
	ProgramId,
	myMatrixLocation,
	matrTranslLocation,
	matrRotlLocation,
	codColLocation,
	texture;

GLfloat
	winWidth = 1920, winHeight = 1080;

glm::mat4
	myMatrix, resizeMatrix, matrTransl, matrRot;

int codCol;
float angle = 0;
float tx = 0; float ty = 0;
float xMin = -960.f, xMax = 960.f, yMin = -540.f, yMax = 540.f;


void ProcessNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'l':
		angle += 0.2f;
		break;
	case 'r':
		angle -= 0.2f;
		break;
	}
	if (key == 27)
		exit(0);
}

void ProcessSpecialKeys(int key, int xx, int yy) 
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		tx -= 10;
		break;
	case GLUT_KEY_RIGHT:
		tx += 10;
		break;
	case GLUT_KEY_UP:
		ty += 10;
		break;
	case GLUT_KEY_DOWN:
		ty -= 10;
		break;
	}
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
	unsigned char* image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CreateShaders(void)
{
	ProgramId = LoadShaders(ASSET_DIR "/shader.vert", ASSET_DIR "/shader.frag");
	glUseProgram(ProgramId);
}

void CreateVBO(void)
{

	GLfloat Vertices[] = {

		  -384.0f, -384.0f, 0.0f, 1.0f,	  1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		   384.0f, -384.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		   384.0f,  384.0f, 0.0f, 1.0f,   1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		  -384.0f,  384.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,	0.0f, 1.0f
	};

	GLuint Indices[] = {
	  0, 1, 2,
	  0, 2, 3
	};

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
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
	glDeleteBuffers(1, &VboId);
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
	glClearColor(0.53f, 0.81f, 0.93f, 1.0f);

	CreateVBO();

	LoadTexture(ASSET_DIR "/assets/blob.png");

	CreateShaders();

	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");

	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);
}

void RenderFunction(void)
{	
	glClear(GL_COLOR_BUFFER_BIT);

	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(tx, ty, 0.0));
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));

	myMatrix = resizeMatrix * matrTransl * matrRot;
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
	glutKeyboardFunc(ProcessNormalKeys);
	glutSpecialFunc(ProcessSpecialKeys);
	glutCloseFunc(Cleanup);

	glutMainLoop();

	return 0;
}
