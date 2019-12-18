#pragma once

#include "common.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>


namespace glimac {

// Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Controls {

public:
    Controls(){};
    ~Controls(){};
    void computeMatricesFromInputs(float wW, float wH, SDL_Event e);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();


private :
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
};


}
