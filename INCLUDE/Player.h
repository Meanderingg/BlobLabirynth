#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object {
public:
    Player(glm::vec2 pos, glm::vec2 size, const Mesh* mesh, GLuint texture, const std::vector<std::vector<int>>& labyrinthGrid);
    void update(Game& game) override;
    void handleMovement(Game& game);
    bool canMoveTo(Game& game, glm::vec2 gridPos) const;
    bool collidesWithWalls(const Game& game, glm::vec2 pos) const;
    
    std::vector<std::vector<int>> labyrinthGrid;
    glm::vec2 gridPosition = glm::vec2(0, 0);
    glm::vec2 facing = glm::vec2(0, 0);  
    float speed = 5.f;
    bool blockedByWall = false;

};

#endif
