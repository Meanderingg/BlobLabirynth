#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object {
public:
    using Object::Object;
    void update(Game& game) override;
    void handleMovement(Game& game);

    glm::vec2 direction;
    float speed = 10.f;
};

#endif