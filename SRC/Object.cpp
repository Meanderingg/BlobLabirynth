#include "Object.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Object::Object(glm::vec2 pos, glm::vec2 size, const Mesh* mesh, GLuint texture) {
    this->position = pos;
    this->size = size;
    this->mesh = mesh;
    this->texture = texture;
}

void Object::render(GLint matrixLocation, const glm::mat4& projection) const {
    glm::mat4 matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(this->position.x, this->position.y, 0.0));
	glm::mat4 matrScale = glm::scale(glm::mat4(1.0f), glm::vec3(this->size.x, this->size.y, 1.0));
    glm::mat4 matrRot = glm::rotate(glm::mat4(1.0f), this->angle, glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 myMatrix = projection * matrTransl * matrRot * matrScale;
    
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

    this->mesh->draw();
}