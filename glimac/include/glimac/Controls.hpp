#pragma once

#include <vector>

#include "common.hpp"


#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
//#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>


namespace glimac {

// Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Controls {

public:
void computeMatricesFromInputs(float wW, float wH, SDL_Event e);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
Controls();


private :
glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
};


}
