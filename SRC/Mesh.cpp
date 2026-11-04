#include "Mesh.h"

#include <GL/glew.h>

Mesh::Mesh() {
    GLfloat Vertices[] = {
        -0.5, -0.5, 0.0f, 1.0f,		
        0.5, -0.5, 0.0f, 1.0f,		
        0.5, 0.5, 0.0f, 1.0f,		
        -0.5, 0.5, 0.0f, 1.0f,
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
	  0, 2, 3,
	};

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(this->VaoId);

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
};

void Mesh::draw() const {
    glBindVertexArray(this->VaoId);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &this->VboPositions);
	glDeleteBuffers(1, &this->VboColors);
	glDeleteBuffers(1, &this->VboTexCoords);
	glDeleteBuffers(1, &this->EboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &this->VaoId);
}