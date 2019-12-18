#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"

namespace glimac {

void Cube::build() {
    GLfloat edge = 0.5;
    m_Vertices = {
        //Face sol
        Vertex3DTexture(glm::vec3(-edge, -edge, -edge), glm::vec3(0, -1, 0), glm::vec2(0,0)), //0
        Vertex3DTexture(glm::vec3(edge, -edge, -edge), glm::vec3(0, -1, 0), glm::vec2(1,0)), //1
        Vertex3DTexture(glm::vec3(edge, -edge, edge), glm::vec3(0, -1, 0), glm::vec2(1,1)), //2
        Vertex3DTexture(glm::vec3(-edge, -edge, edge), glm::vec3(0, -1, 0), glm::vec2(0,1)), //3

        //Face devant
        Vertex3DTexture(glm::vec3(-edge, edge, edge), glm::vec3(0, 0, 1), glm::vec2(0,0)), //4
        Vertex3DTexture(glm::vec3(edge, edge, edge), glm::vec3(0, 0, 1), glm::vec2(1,0)), //5
        Vertex3DTexture(glm::vec3(edge, -edge, edge), glm::vec3(0, 0, 1), glm::vec2(1,1)), //6
        Vertex3DTexture(glm::vec3(-edge, -edge, edge), glm::vec3(0, 0, 1), glm::vec2(0,1)), //7

        //Face gauche
        Vertex3DTexture(glm::vec3(-edge, edge, edge), glm::vec3(-1, 0, 0), glm::vec2(0,0)), //8
        Vertex3DTexture(glm::vec3(-edge, edge, -edge), glm::vec3(-1, 0, 0), glm::vec2(1,0)), //9
        Vertex3DTexture(glm::vec3(-edge, -edge, -edge), glm::vec3(-1, 0, 0), glm::vec2(1,1)), //10
        Vertex3DTexture(glm::vec3(-edge, -edge, edge), glm::vec3(-1, 0, 0), glm::vec2(0,1)), //11

        //Face derrière
        Vertex3DTexture(glm::vec3(-edge, edge, -edge), glm::vec3(0, 0, -1), glm::vec2(0,0)), //12
        Vertex3DTexture(glm::vec3(edge, edge, -edge), glm::vec3(0, 0, -1), glm::vec2(1,0)), //13
        Vertex3DTexture(glm::vec3(edge, -edge, -edge), glm::vec3(0, 0, -1), glm::vec2(1,1)), //14
        Vertex3DTexture(glm::vec3(-edge, -edge, -edge), glm::vec3(0, 0, -1), glm::vec2(0,1)), //15

        //Face droite
        Vertex3DTexture(glm::vec3(edge, edge, edge), glm::vec3(1, 0, 0), glm::vec2(0,0)), //16
        Vertex3DTexture(glm::vec3(edge, edge, -edge), glm::vec3(1, 0, 0), glm::vec2(1,0)), //17
        Vertex3DTexture(glm::vec3(edge, -edge, -edge), glm::vec3(1, 0, 0), glm::vec2(1,1)), //18
        Vertex3DTexture(glm::vec3(edge, -edge, edge), glm::vec3(1, 0, 0), glm::vec2(0,1)), //19

        //Face haut
        Vertex3DTexture(glm::vec3(-edge, edge, -edge), glm::vec3(0, 1, 0), glm::vec2(0,0)), //20
        Vertex3DTexture(glm::vec3(edge, edge, -edge), glm::vec3(0, 1, 0), glm::vec2(1,0)), //21
        Vertex3DTexture(glm::vec3(edge, edge, edge), glm::vec3(0, 1, 0), glm::vec2(1,1)), //22
        Vertex3DTexture(glm::vec3(-edge, edge, edge), glm::vec3(0, 1, 0), glm::vec2(0,1)) //23
    };

    m_nVertexCount = m_Vertices.size();

    m_Index = {
        0,1,2,0,2,3,  4,5,6,4,6,7,  8,9,10,8,10,11,  12,13,14,12,14,15,  16,17,18,16,18,19,  20,21,22,20,22,23
     };

    m_edge = edge;

    m_textureIndex = 0; // first texture by default, changer ça pour qu'on puisse avoir des cubes sans texture ? Avec une couleur ? Avec une couleur par defaut ?
    m_cubeIndex = 0;

    // Default 3D transform
    m_scale = glm::vec3(1.0f);
    m_rot = glm::vec3(1.0f);
    m_rotDeg = 0.0f;
    m_trans = glm::vec3(0.0f);

    std::cout << "[Edit] New cube created at origin with size 1." << std::endl;
}

void Cube::translateVertices(GLfloat tx, GLfloat ty, GLfloat tz) {

    m_Vertices = {
        //Face sol
        Vertex3DTexture(glm::vec3(-m_edge+tx, -m_edge+ty, -m_edge+tz), glm::vec3(0, -1, 0), glm::vec2(0,0)), //0
        Vertex3DTexture(glm::vec3(m_edge+tx, -m_edge+ty, -m_edge+tz), glm::vec3(0, -1, 0), glm::vec2(1,0)), //1
        Vertex3DTexture(glm::vec3(m_edge+tx, -m_edge+ty, m_edge+tz), glm::vec3(0, -1, 0), glm::vec2(1,1)), //2
        Vertex3DTexture(glm::vec3(-m_edge+tx, -m_edge+ty, m_edge+tz), glm::vec3(0, -1, 0), glm::vec2(0,1)), //3

        //Face devant
        Vertex3DTexture(glm::vec3(-m_edge+tx, m_edge+ty, m_edge+tz), glm::vec3(0, 0, 1), glm::vec2(0,0)), //4
        Vertex3DTexture(glm::vec3(m_edge+tx, m_edge+ty, m_edge+tz), glm::vec3(0, 0, 1), glm::vec2(1,0)), //5
        Vertex3DTexture(glm::vec3(m_edge+tx, -m_edge+ty, m_edge+tz), glm::vec3(0, 0, 1), glm::vec2(1,1)), //6
        Vertex3DTexture(glm::vec3(-m_edge+tx, -m_edge+ty, m_edge+tz), glm::vec3(0, 0, 1), glm::vec2(0,1)), //7

        //Face gauche
        Vertex3DTexture(glm::vec3(-m_edge+tx, m_edge+ty, m_edge+tz), glm::vec3(-1, 0, 0), glm::vec2(0,0)), //8
        Vertex3DTexture(glm::vec3(-m_edge+tx, m_edge+ty, -m_edge+tz), glm::vec3(-1, 0, 0), glm::vec2(1,0)), //9
        Vertex3DTexture(glm::vec3(-m_edge+tx, -m_edge+ty, -m_edge+tz), glm::vec3(-1, 0, 0), glm::vec2(1,1)), //10
        Vertex3DTexture(glm::vec3(-m_edge+tx, -m_edge+ty, m_edge+tz), glm::vec3(-1, 0, 0), glm::vec2(0,1)), //11

        //Face derrière
        Vertex3DTexture(glm::vec3(-m_edge+tx, m_edge+ty, -m_edge+tz), glm::vec3(0, 0, -1), glm::vec2(0,0)), //12
        Vertex3DTexture(glm::vec3(m_edge+tx, m_edge+ty, -m_edge+tz), glm::vec3(0, 0, -1), glm::vec2(1,0)), //13
        Vertex3DTexture(glm::vec3(m_edge+tx, -m_edge+ty, -m_edge+tz), glm::vec3(0, 0, -1), glm::vec2(1,1)), //14
        Vertex3DTexture(glm::vec3(-m_edge+tx, -m_edge+ty, -m_edge+tz), glm::vec3(0, 0, -1), glm::vec2(0,1)), //15

        //Face droite
        Vertex3DTexture(glm::vec3(m_edge+tx, m_edge+ty, m_edge+tz), glm::vec3(1, 0, 0), glm::vec2(0,0)), //16
        Vertex3DTexture(glm::vec3(m_edge+tx, m_edge+ty, -m_edge+tz), glm::vec3(1, 0, 0), glm::vec2(1,0)), //17
        Vertex3DTexture(glm::vec3(m_edge+tx, -m_edge+ty, -m_edge+tz), glm::vec3(1, 0, 0), glm::vec2(1,1)), //18
        Vertex3DTexture(glm::vec3(m_edge+tx, -m_edge+ty, m_edge+tz), glm::vec3(1, 0, 0), glm::vec2(0,1)), //19

        //Face haut
        Vertex3DTexture(glm::vec3(-m_edge+tx, m_edge+ty, -m_edge+tz), glm::vec3(0, 1, 0), glm::vec2(0,0)), //20
        Vertex3DTexture(glm::vec3(m_edge+tx, m_edge+ty, -m_edge+tz), glm::vec3(0, 1, 0), glm::vec2(1,0)), //21
        Vertex3DTexture(glm::vec3(m_edge+tx, m_edge+ty, m_edge+tz), glm::vec3(0, 1, 0), glm::vec2(1,1)), //22
        Vertex3DTexture(glm::vec3(-m_edge+tx, m_edge+ty, m_edge+tz), glm::vec3(0, 1, 0), glm::vec2(0,1)) //23
    };
}

void Cube::setTextureIndex(GLuint index){
    m_textureIndex = index;
    std::cout << "[Edit] Cube " << m_cubeIndex << " have texture :" << m_textureIndex << "." << std::endl;

}

void Cube::setCubeIndex(GLuint index){
    m_cubeIndex = index;
}

// Scale
void Cube::setScale(GLfloat x, GLfloat y, GLfloat z){
    if(floor(x)==x && floor(y)==y && floor(z)==z){
        m_scale = glm::vec3(x, y, z);
        std::cout << "[Edit] Cube " << m_cubeIndex << " scale to (" << m_scale.x << ", " << m_scale.y << ", "<< m_scale.z << ")."<< std::endl;

    }else{
        std::cerr << "[ERROR] Enable to scale with float weight ! Cube " << m_cubeIndex << " still scaled to (" << m_scale.x << ", " << m_scale.y << ", "<< m_scale.z << ")."<< std::endl;
    }
}
void Cube::setScaleFloat(GLfloat x, GLfloat y, GLfloat z){
    m_scale = glm::vec3(x, y, z);
    std::cout << "[Edit] Cube " << m_cubeIndex << " scaled to (" << m_trans.x << ", " << m_trans.y << ", "<< m_trans.z << ")."<< std::endl;

}

// Rotate
void Cube::setRot(GLfloat degrees, GLfloat x, GLfloat y, GLfloat z){
    m_rot = glm::vec3(x, y, z);
    m_rotDeg = degrees;
}

// Translate
void Cube::setTrans(GLfloat x, GLfloat y, GLfloat z){
    if(floor(x)==x && floor(y)==y && floor(z)==z){
        m_trans = glm::vec3(x, y, z);
        std::cout << "[Edit] Cube " << m_cubeIndex << " translate to (" << m_trans.x << ", " << m_trans.y << ", "<< m_trans.z << ")."<< std::endl;

    }else{
        std::cerr << "[ERROR] Enable to translate to float coordinates ! Cube " << m_cubeIndex << " still at (" << m_trans.x << ", " << m_trans.y << ", "<< m_trans.z << ")."<< std::endl;
    }
}
}

