#pragma once

#include "common.hpp"
#include "Image.hpp"
#include "Program.hpp"

namespace glimac {

// Represent a texture with Uniform Location, loaded image, GLuint index
class Texture {

public:

    // Constructeur
    Texture();
    // Destructeur
    ~Texture();

    // Renvoit le pointeur vers les données
    void setUniformLocation(Program &program, const GLchar* name);

    void setImage(const FilePath &filepath);

    GLuint getTexture(){
        return m_texture;
    }

    GLuint* getTexturePointer(){
        return &m_texture;
    }

    unsigned int getImageWidth(){
        return m_image->getWidth();
    }

    unsigned int getImageHeight(){
        return m_image->getHeight();
    }

    const glm::vec4* getImagePixels() const{
        return m_image->getPixels();
    }

    GLuint getUniformLocation(){
        return m_uTexture;
    }

private:
    GLint m_uTexture; // Uniform Location
    std::unique_ptr<Image> m_image; // Image texture
    GLuint m_texture; // Texture index to bind
};

}
