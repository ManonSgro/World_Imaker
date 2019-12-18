#pragma once

#include <vector>
#include <Eigen/Dense>

#include "common.hpp"

namespace glimac {

// Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Cube {

public:

    // Constructeur: alloue le tableau de données et construit les attributs des vertex

    Cube();
    ~Cube(){};
    Cube():
        m_nVertexCount(0) {
        build(); // Construction (voir le .cpp)
    }

    // Alloue et construit les données (implantation dans le .cpp)
    void build();

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


    // Renvoit le nombre de vertex
    GLsizei getIBOCountBorder() const {
        return m_IndexBorder.size();
    }

    // Renvoit le pointeur vers les données
    const uint32_t* getIBOPointerBorder() const {
        return &m_IndexBorder[0];
    }

    void translateVertices(GLfloat tx, GLfloat ty, GLfloat tz);

    // Gestion textures
    void setTextureIndex(GLuint index);
    GLuint getTextureIndex(){
        return m_textureIndex;
    };

    // Set index
    void setCubeIndex(GLuint index);
    GLuint getCubeIndex(){
        return m_cubeIndex;
    };

    // Compare cubes
    bool operator > (const Cube& cubeToCompare) const
    {
        return (m_textureIndex > cubeToCompare.m_textureIndex);
    }

    // Scale
    void setScale(GLfloat x, GLfloat y, GLfloat z);
    glm::vec3 getScale(){
        return m_scale;
    };
    void setScaleFloat(GLfloat x, GLfloat y, GLfloat z); 

    // Rotate
    void setRot(GLfloat degrees, GLfloat x, GLfloat y, GLfloat z);
    glm::vec3 getRot(){
        return m_rot;
    };
    GLfloat getRotDeg(){
        return m_rotDeg;
    };

    // Translate
    void setTrans(GLfloat x, GLfloat y, GLfloat z);
    
    glm::vec3 getTrans(){
        return m_trans;
    };

private:
    std::vector<Vertex3DTexture> m_Vertices;
    GLsizei m_nVertexCount; // Nombre de sommets
    std::vector<uint32_t> m_Index; // indices ibo
    std::vector<uint32_t> m_IndexBorder; // indices ibo
    GLfloat m_edge; // à voir si on ne peut pas plutôt stocker une matrice sur laquelle appliquer des transformations puis une fonction pour faire le liens entre cette matrice et les vertices...

    GLuint m_textureIndex;
    GLuint m_cubeIndex; // the same as vbo/ibo/vao

    glm::vec3 m_scale;
    glm::vec3 m_rot;
    GLfloat m_rotDeg;
    glm::vec3 m_trans;
};

}
