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
    void CreateObjects();
    static glm::vec4 calculateBorders(float posX, float posY, float spriteW, float spriteH);
    static bool collisionDetection(float positionXA, float positionYA, float widthA, float heightA, float positionXB, float positionYB, float widthB, float heightB);
    glm::vec2 gridToScreenPosition(glm::vec2 gridPosition);
    bool screenCollision(float posX, float posY, float spriteW, float spriteH);
    ~Game();

    constexpr static float xMin = -960.f, xMax = 960.f, yMin = -540.f, yMax = 540.f;
    std::vector<bool> keystates;
private:
    Mesh mesh;
    std::vector<std::unique_ptr<Object>> objects;
    GLint matrixLocation;
    glm::mat4 projection;
    GLuint programId;
    GLuint blobTexture = 0;
    glm::vec2 cellLayout;
    glm::vec2 cellSize;
};

#endif