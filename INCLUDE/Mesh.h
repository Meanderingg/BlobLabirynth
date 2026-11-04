#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

class Mesh
{
public:
    Mesh();
    ~Mesh();
    void draw() const;

private:
    GLuint
        VaoId,
        VboPositions,
        VboColors,
        VboTexCoords,
        EboId;

    Mesh(const Mesh& other) {};
    void operator=(const Mesh& other) {};
};

#endif