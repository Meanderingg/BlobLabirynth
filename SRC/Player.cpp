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
    glm::vec2 topLeftCurrentCell = glm::vec2(game.xMin + 60 * this->gridPosition.x, game.yMax - 60 * this->gridPosition.y);
    // Check if gone to the right
    if (newPosition.x - topLeftCurrentCell.x >= 60) {
        this->gridPosition.x++;
    }
    // Check if gone down
    if (topLeftCurrentCell.y - newPosition.y >= 60) {
        this->gridPosition.y++;
    }
    // Check if gone to the left
    if (topLeftCurrentCell.x - newPosition.x >= 0 ) {
        this->gridPosition.x--;
    }
    // Check if gone up
    if (newPosition.y - topLeftCurrentCell.y >= 0) {
        this->gridPosition.y--;
    }

    std::cout << this->gridPosition.x << " " << this->gridPosition.y << "\n";
    int currentCell = this->labyrinthGrid[this->gridPosition.x][this->gridPosition.y];
    if (currentCell == 0) {
        // Check collision with left wall
        if (Game::collisionDetection(newPosition.x, newPosition.y, this->size.x, this->size.y, topLeftCurrentCell.x, topLeftCurrentCell.y - game.cellSize.y / 2, game.wallWidth, game.cellSize.y))
            return;
    }

 	if (!game.screenCollision(newPosition.x, newPosition.y, this->size.x, this->size.y)) {
		this->position = newPosition;
	}
}
