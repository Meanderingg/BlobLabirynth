#include "Player.h"
#include "Game.h"

#include "glm/gtc/constants.hpp"

Player::Player(glm::vec2 pos, glm::vec2 size, const Mesh* mesh, GLuint texture, const std::vector<std::vector<int>>& labyrinthGrid)
    : Object(pos, size, mesh, texture), labyrinthGrid(labyrinthGrid) {}

void Player::update(Game& game) {
    this->handleMovement(game);
}

bool Player::canMoveTo(Game& game, glm::vec2 gridPosNew) const {
    unsigned char key;
    if (this->facing == glm::vec2(1,0)) key = 'd';
    if (this->facing == glm::vec2(0,-1)) key = 'w';
    if (this->facing == glm::vec2(-1,0)) key = 'a';
    if (this->facing == glm::vec2(0,1)) key = 's';

    glm::vec2 screenPos = game.gridToScreenPosition(gridPosNew);
    //std::cout<<gridPosition.x<<" "<<gridPosition.y<<'\n';
    //std::cout<<gridPosNew.x<<" "<<gridPosNew.y<<'\n';

    if(game.screenCollision(screenPos.x, screenPos.y, this->size.x, this->size.y))
        return false;

    if (this->labyrinthGrid[this->gridPosition.x][this->gridPosition.y] == 0 && key =='w')
        return true;

    if (this -> labyrinthGrid[this->gridPosition.x][this->gridPosition.y] == 1 && key == 'a')
        return true;

    if (this -> labyrinthGrid[this->gridPosition.x][this->gridPosition.y] == 2 && (key == 'a' || key == 'w'))
        return true;

    if(labyrinthGrid[gridPosNew.x][gridPosNew.y] == 0 && key =='s')
        return true;

    if(labyrinthGrid[gridPosNew.x][gridPosNew.y] == 1 && key =='d')
        return true;

    if(labyrinthGrid[gridPosNew.x][gridPosNew.y] == 2 && key =='d')
        return true;
    
    if(labyrinthGrid[gridPosNew.x][gridPosNew.y] == 2 && key =='s')
        return true;

    return false;

}

bool hasWon(Game& game, glm::vec2 gridPosition){
    
    return (gridPosition == game.cellLayout - glm::vec2(1, 1));
}

void Player::handleMovement(Game& game) {
    // Angle 0 means the sprite faces right
	struct KeyBinding { unsigned char key; glm::vec2 dir; float angle; };
	static const KeyBinding bindings[] = {
		{'d', glm::vec2(1,  0), 0.f},
		{'w', glm::vec2(0, 1), glm::half_pi<float>()},
		{'a', glm::vec2(-1,  0), glm::pi<float>()},
		{'s', glm::vec2(0,  -1), -glm::half_pi<float>()},
	};

	const KeyBinding* pressed = nullptr;

	for (const KeyBinding& binding : bindings) {
		if (!game.keystates[binding.key])
			continue;
		if (!pressed)
			pressed = &binding;
	}

	if (!pressed)
		return;

	if (pressed->dir != this->facing) {
		this->facing = pressed->dir;
		this->angle = pressed->angle;
		return;
	}

    glm::vec2 newPosition = this->position + this->speed * this->facing;

    if (game.screenCollision(newPosition.x, newPosition.y, this->size.x, this->size.y))
        return;
    if (this->collidesWithWalls(game, newPosition))
        return;

    this->position = newPosition;
    this->gridPosition = glm::vec2(
        std::floor((this->position.x - Game::xMin) / game.cellSize.x),
        std::floor((Game::yMax - this->position.y) / game.cellSize.y));

    if(hasWon(game, this->gridPosition))
        glutLeaveMainLoop();
}

bool Player::collidesWithWalls(const Game& game, glm::vec2 pos) const {
    const int cols = game.cellLayout.x;  
    const int rows = game.cellLayout.y;  

    // The cell the blob's center is in
    int cx = (int)std::floor((pos.x - Game::xMin) / game.cellSize.x);
    int cy = (int)std::floor((Game::yMax - pos.y) / game.cellSize.y);

    // Check a 3x3 grid around the center cell
    for (int i = cx - 1; i <= cx + 1; i++) {
        for (int j = cy - 1; j <= cy + 1; j++) {
            if (i < 0 || i >= cols || j < 0 || j >= rows)
                continue; 

            float cellLeft = Game::xMin + i * game.cellSize.x;
            float cellTop  = Game::yMax - j * game.cellSize.y;
            int cell = this->labyrinthGrid[i][j];

            if (cell == 0 &&  // left wall
                Game::collisionDetection(pos.x, pos.y, this->size.x, this->size.y,
                                         cellLeft, cellTop - game.cellSize.y / 2, game.wallWidth, game.cellSize.y))
                return true;

            if (cell == 1 &&  // top wall
                Game::collisionDetection(pos.x, pos.y, this->size.x, this->size.y,
                                         cellLeft + game.cellSize.x / 2, cellTop, game.cellSize.x, game.wallWidth))
                return true;
        }
    }
    return false;
}
