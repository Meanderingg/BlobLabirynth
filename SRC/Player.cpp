#include "Player.h"
#include "Game.h"

void Player::update(Game& game) {
    this->handleMovement(game);
}

void Player::handleMovement(Game& game) {
	this->direction = glm::vec2(0, 0);
	
	if (game.keystates['d']) {
		this->direction.x = 1;
	}

	if (game.keystates['a']) {
        this->direction.x = -1;
	}

	if (game.keystates['w']) {
        this->direction.y = 1;
	}

	if (game.keystates['s']) {
        this->direction.y = -1;
	}

    float newPositionX = this->position.x + direction.x * this->speed;
    float newPositionY = this->position.y + direction.y * this->speed;

    if (!game.screenCollision(newPositionX, newPositionY, this->size.x, this->size.y) && 
		!Game::collisionDetection(newPositionX, newPositionY, this->size.x - 20, this->size.y - 20, 66, 66, this->size.x, this->size.y))
    {
        this->position.x = newPositionX;
        this->position.y = newPositionY;
    }
}