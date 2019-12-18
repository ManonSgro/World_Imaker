#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cursor.hpp"

namespace glimac {

Cube Cursor::translateCursor(SDL_Event e, Cube cube){
    if(e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_a){
            cube.setTrans(cube.getTrans().x - 1, cube.getTrans().y, cube.getTrans().z);
        }
        if (e.key.keysym.sym == SDLK_q){
            cube.setTrans(cube.getTrans().x + 1, cube.getTrans().y, cube.getTrans().z);
        }
        if (e.key.keysym.sym == SDLK_z){
            cube.setTrans(cube.getTrans().x, cube.getTrans().y  - 1, cube.getTrans().z);
        }
        if (e.key.keysym.sym == SDLK_s){
            cube.setTrans(cube.getTrans().x, cube.getTrans().y + 1, cube.getTrans().z);
        }
        if (e.key.keysym.sym == SDLK_e){
            cube.setTrans(cube.getTrans().x, cube.getTrans().y, cube.getTrans().z - 1);
        }
        if (e.key.keysym.sym == SDLK_d){
            cube.setTrans(cube.getTrans().x, cube.getTrans().y, cube.getTrans().z + 1);
        }
    }
    return cube;
}

}

