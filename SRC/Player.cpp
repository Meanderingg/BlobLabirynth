#include "Player.h"
#include "Game.h"

#include "glm/gtc/constants.hpp"

Player::Player(glm::vec2 pos, glm::vec2 size, const Mesh* mesh, GLuint texture, const std::vector<std::vector<int>>& labyrinthGrid)
    : Object(pos, size, mesh, texture), labyrinthGrid(labyrinthGrid) {}

void Player::update(Game& game) {
    this->handleMovement(game);
}

bool Player::canMoveTo(Game& game, glm::vec2 gridPos) const {
    glm::vec2 screenPos = game.gridToScreenPosition(gridPos);
    return !game.screenCollision(screenPos.x, screenPos.y, this->size.x, this->size.y);
}

void Player::handleMovement(Game& game) {
	// Angle 0 means the sprite faces right
	struct KeyBinding { unsigned char key; glm::vec2 dir; float angle; };
	static const KeyBinding bindings[] = {
		{'d', glm::vec2( 1,  0), 0.f},
		{'w', glm::vec2( 0, -1), glm::half_pi<float>()},
		{'a', glm::vec2(-1,  0), glm::pi<float>()},
		{'s', glm::vec2( 0,  1), -glm::half_pi<float>()},
	};

	const KeyBinding* pressed = nullptr;

	for (const KeyBinding& binding : bindings) {
		if (!game.keystates[binding.key])
			continue;
		game.keystates[binding.key] = false;
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

	glm::vec2 newGridPosition = this->gridPosition + this->facing;
	if (this->canMoveTo(game, newGridPosition)) {
		this->gridPosition = newGridPosition;
		this->position = game.gridToScreenPosition(newGridPosition);
	}
}
