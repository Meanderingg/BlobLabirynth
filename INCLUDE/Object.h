#ifndef OBJECT_H
#define OBJECT_H

#include "Mesh.h"
#include "glm/glm.hpp"
#include <GL/glew.h> 

class Game;

class Object {
public:
    Object(glm::vec2 pos, glm::vec2 size, const Mesh* mesh, GLuint texture);
    virtual ~Object() = default;

    virtual void update(Game& game) {};
    virtual void render(GLint matrixLocation, const glm::mat4& projection) const;
protected:
    glm::vec2 position, size;
    const Mesh* mesh;
    GLuint texture;
    float angle = 0.f;
};

#endif