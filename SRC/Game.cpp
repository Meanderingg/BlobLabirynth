#include "Game.h"
#include "loadShaders.h"
#include <SOIL.h>

Game::Game() {
    keystates = std::vector<bool>(256, false);
    projection = glm::ortho(xMin, xMax, yMin, yMax);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
}

void Game::LoadTexture(const char* texturePath, GLuint& texture) {
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

void Game::CreateShaders() {
    this->programId = LoadShaders(ASSET_DIR "/shader.vert", ASSET_DIR "/shader.frag");
    glUseProgram(programId);
    this->matrixLocation = glGetUniformLocation(programId, "myMatrix");

    glUniform1i(glGetUniformLocation(programId, "myTexture"), 0);
}

void Game::update() {
    for (auto& object : objects) {
        object->update(*this);
    }
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto& object : objects) {
        object->render(matrixLocation, projection);
    }
    glutSwapBuffers();
    glFlush();
}

void Game::KeyDown(unsigned char key, int _, int __)
{
	keystates[key] = true;
}

void Game::KeyUp(unsigned char key, int _, int __)
{
	keystates[key] = false;
}