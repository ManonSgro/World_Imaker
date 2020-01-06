#pragma once

#include <GL/glew.h>
#include "glm.hpp"

#include <iostream>
#include <cstddef>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <memory>
#include <unordered_map>

#include<Eigen/SparseLU>
#include <Eigen/Dense>

/*! \namespace glimac
 * 
 * \brief Outils de gestion d'une scène 3D
 * 
 * Espace de nommage regroupant les outils de gestion 
 * d'une scène 3D en OpenGL.
 */
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
