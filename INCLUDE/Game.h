#ifndef GAME_H
#define GAME_H

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Object.h"

class Game {
public:
    Game();
    void update();
    void render();
    void LoadTexture(const char* texturePath, GLuint& texture);
    void KeyUp(unsigned char key, int _, int __);
    void KeyDown(unsigned char key, int _, int __);
    void CreateShaders();

    constexpr static float xMin = -960.f, xMax = 960.f, yMin = -540.f, yMax = 540.f;
    std::vector<bool> keystates;
private:
    Mesh mesh;
    std::vector<std::unique_ptr<Object>> objects;
    GLint matrixLocation;
    glm::mat4 projection;
    GLuint programId;
};

#endif