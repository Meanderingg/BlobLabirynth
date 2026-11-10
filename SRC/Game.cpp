#include "Game.h"
#include "Player.h"
#include "Labyrinth.h"
#include "loadShaders.h"
#include <SOIL.h>
#include <iostream>

Game::Game() {
    keystates = std::vector<bool>(256, false);
    projection = glm::ortho(xMin, xMax, yMin, yMax);
    cellLayout = glm::vec2(32, 18);
    cellSize = glm::vec2(60.f, 60.f);

    glutFullScreen();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    labyrinth = Labyrinth(cellLayout.x, cellLayout.y);
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

void Game::CreateObjects() {
    LoadTexture(ASSET_DIR "/assets/blob.png", blobTexture);

    float wallWidth = 2.f;
    glm::vec2 topLeftCell = glm::vec2(this->xMin + this->cellSize.x / 2, this->yMax - this->cellSize.y / 2);

    objects.push_back(std::make_unique<Player>(glm::vec2(topLeftCell.x, topLeftCell.y), glm::vec2(55.f, 55.f), &mesh, blobTexture));

    // 60x60 size for each cell
    // width: 32 cells
    // height: 18 cells
    for (int i = 0; i < cellLayout.x; i++)
        for (int j = 0; j < cellLayout.y; j++) {
            float x = this->xMin + this->cellSize.x / 2 + i * this->cellSize.x;
            float y = this->yMax - this->cellSize.y / 2 - j * this->cellSize.y;
            // Objects are positioned by their center, so each wall sits at the middle of its cell side.
            // Thickness is 2 because a 1-unit wall is under 1 pixel when the window is smaller than 1920x1080.

            // Deciding which wall is not drawn

            if (labyrinth.getCell(i, j) == 0){
                //objects.push_back(std::make_unique<Object>(glm::vec2(x, y + this->cellSize.y / 2), glm::vec2(this->cellSize.x, wallWidth), &mesh, 0));  // top
                //objects.push_back(std::make_unique<Object>(glm::vec2(x + this->cellSize.x / 2, y), glm::vec2(wallWidth, this->cellSize.y), &mesh, 0));  // right
                //objects.push_back(std::make_unique<Object>(glm::vec2(x, y - this->cellSize.y / 2), glm::vec2(this->cellSize.x, wallWidth), &mesh, 0));  // bottom
                objects.push_back(std::make_unique<Object>(glm::vec2(x - this->cellSize.x / 2, y), glm::vec2(wallWidth, this->cellSize.y), &mesh, 0));  // left
                }

            if (labyrinth.getCell(i, j) == 1){
                objects.push_back(std::make_unique<Object>(glm::vec2(x, y + this->cellSize.y / 2), glm::vec2(this->cellSize.x, wallWidth), &mesh, 0));  // top
                //objects.push_back(std::make_unique<Object>(glm::vec2(x + this->cellSize.x / 2, y), glm::vec2(wallWidth, this->cellSize.y), &mesh, 0));  // right
                //objects.push_back(std::make_unique<Object>(glm::vec2(x, y - this->cellSize.y / 2), glm::vec2(this->cellSize.x, wallWidth), &mesh, 0));  // bottom
                //objects.push_back(std::make_unique<Object>(glm::vec2(x - this->cellSize.x / 2, y), glm::vec2(wallWidth, this->cellSize.y), &mesh, 0));  // left
                }

            if (labyrinth.getCell(i, j) == 2){
                //objects.push_back(std::make_unique<Object>(glm::vec2(x, y + this->cellSize.y / 2), glm::vec2(this->cellSize.x, wallWidth), &mesh, 0));  // top
                //objects.push_back(std::make_unique<Object>(glm::vec2(x + this->cellSize.x / 2, y), glm::vec2(wallWidth, this->cellSize.y), &mesh, 0));  // right
                //objects.push_back(std::make_unique<Object>(glm::vec2(x, y - this->cellSize.y / 2), glm::vec2(this->cellSize.x, wallWidth), &mesh, 0));  // bottom
                //objects.push_back(std::make_unique<Object>(glm::vec2(x - this->cellSize.x / 2, y), glm::vec2(wallWidth, this->cellSize.y), &mesh, 0));  // left
                }
        }
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
	if (key == 27) {  // Esc
		glutLeaveMainLoop();
		return;
	}

	keystates[key] = true;
}

void Game::KeyUp(unsigned char key, int _, int __)
{
	keystates[key] = false;
}

glm::vec4 Game::calculateBorders(float posX, float posY, float spriteW, float spriteH)
{
    return glm::vec4(posX + spriteW / 2, posX - spriteW / 2, posY + spriteH / 2, posY - spriteH / 2);
}

bool Game::screenCollision(float posX, float posY, float spriteW, float spriteH)
{
    glm::vec4 borders = calculateBorders(posX, posY, spriteW, spriteH); 
    if (borders[0] > this->xMax || borders[1] < this->xMin || borders[2] > this->yMax || borders[3] < this->yMin)
        return true;
    else
        return false;
} 

bool Game::collisionDetection(float positionXA, float positionYA, float widthA, float heightA, float positionXB, float positionYB, float widthB, float heightB)
{
    // AABB-Collision here
	glm::vec4 bordersA = calculateBorders(positionXA, positionYA, widthA, heightA);
	glm::vec4 bordersB = calculateBorders(positionXB, positionYB, widthB, heightB);

	bool left = bordersA[0] < bordersB[1];
	bool right = bordersA[1] > bordersB[0];
	bool down = bordersA[2] < bordersB[3];
	bool up = bordersA[3] > bordersB[2];
	
	return !left && !right && !up && !down;
}

glm::vec2 Game::gridToScreenPosition(glm::vec2 gridPosition) {
    glm::vec2 topLeftCell = glm::vec2(this->xMin + this->cellSize.x / 2, this->yMax - this->cellSize.y / 2);
    float offsetX = gridPosition.x * this->cellSize.x;
    float offsetY = gridPosition.y * this->cellSize.y;

    return glm::vec2(topLeftCell.x + offsetX, topLeftCell.y - offsetY);
}

Game::~Game() {
    glDeleteProgram(this->programId);
    glDeleteTextures(1, &this->blobTexture);
}
