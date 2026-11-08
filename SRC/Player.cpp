#include "Player.h"
#include "Game.h"

Player::Player(glm::vec2 pos, glm::vec2 size, const Mesh* mesh, GLuint texture, const std::vector<std::vector<int>>& labyrinthGrid)
    : Object(pos, size, mesh, texture), labyrinthGrid(labyrinthGrid) {
        this->gridPosition = glm::vec2(0, 0);
    }

void Player::update(Game& game) {
    this->handleMovement(game);
}

void Player::handleMovement(Game& game) {
	this->direction = glm::vec2(0, 0);
	
	// Each key is cleared after it's read, so one press moves exactly one cell.
	if (game.keystates['d']) {
		this->direction.x = 1;
		game.keystates['d'] = false;
	}

	if (game.keystates['a']) {
        this->direction.x = -1;
		game.keystates['a'] = false;
	}

	// Grid rows grow downward (row 0 is the top row).
	if (game.keystates['w']) {
        this->direction.y = -1;
		game.keystates['w'] = false;
	}

	if (game.keystates['s']) {
        this->direction.y = 1;
		game.keystates['s'] = false;
	}


    glm::vec2 newGridPosition = glm::vec2(this->gridPosition.x + this->direction.x, this->gridPosition.y + this->direction.y);
    glm::vec2 newScreenPosition = game.gridToScreenPosition(newGridPosition);


    if (!game.screenCollision(newScreenPosition.x, newScreenPosition.y, this->size.x, this->size.y))
    {
        this->gridPosition = newGridPosition;
        this->position = newScreenPosition;
    }
}