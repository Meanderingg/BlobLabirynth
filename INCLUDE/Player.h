#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object {
public:
    using Object::Object;
    void update(Game& game) override;

    glm::vec2 direction;
};

#endif