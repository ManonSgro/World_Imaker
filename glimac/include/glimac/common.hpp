#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Vertex3DTexture{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;

    Vertex3DTexture(){}
    Vertex3DTexture(glm::vec3 position, glm::vec3 normal, glm::vec2 texture):position(position), normal(normal), texture(texture){}
};


}
