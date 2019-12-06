#pragma once

#pragma once

#include <vector>

#include "common.hpp"

namespace glimac {

// Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Cube {

public:

    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Cube();
    Cube(GLfloat edge):
        m_nVertexCount(0) {
        build(edge); // Construction (voir le .cpp)
    }

    // Alloue et construit les données (implantation dans le .cpp)
    void build(GLfloat edge);

    // Renvoit le pointeur vers les données
    const Vertex3DTexture* getDataPointer() const {
        return &m_Vertices[0];
    }

    // Renvoit le nombre de vertex
    GLsizei getVertexCount() const {
        return m_nVertexCount;
    }

    // Renvoit le nombre de vertex
    GLsizei getIBOCount() const {
        return m_Index.size();
    }

    // Renvoit le pointeur vers les données
    const uint32_t* getIBOPointer() const {
        return &m_Index[0];
    }

    void translateVertices(GLfloat tx, GLfloat ty, GLfloat tz);

    // Gestion textures
    void setTextureIndex(GLuint index);
    GLuint getTextureIndex(){
        return m_textureIndex;
    };

private:
    std::vector<Vertex3DTexture> m_Vertices;
    GLsizei m_nVertexCount; // Nombre de sommets
    std::vector<uint32_t> m_Index; // indices ibo
    GLfloat m_edge; // à voir si on ne peut pas plutôt stocker une matrice sur laquelle appliquer des transformations puis une fonction pour faire le liens entre cette matrice et les vertices...

    GLuint m_textureIndex;
};

}
