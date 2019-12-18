#pragma once

#include <vector>
#include <Eigen/Dense>

#include <glimac/SDLWindowManager.hpp>

#include "common.hpp"
#include "Cube.hpp"

namespace glimac {


class Cursor {

public:

    Cursor(){};
    ~Cursor(){};
    Cube translateCursor(SDL_Event e, Cube cube);




};

}
