#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Texture.hpp"

namespace glimac {

Texture::Texture(){};
Texture::~Texture(){};
// Renvoit le pointeur vers les données
void Texture::setUniformLocation(Program &program, const GLchar* name){
    m_uTexture = glGetUniformLocation(program.getGLId(), name);
}

void Texture::setImage(const FilePath &filepath){
    m_image = loadImage(filepath);
    if(m_image == NULL){
        std::cerr << "La texture " << filepath << " n'a pas pu etre chargée. \n" << std::endl;
        exit(0);
    }
}

}
