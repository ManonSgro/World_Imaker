#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include "glimac/common.hpp"
#include "glimac/CubeList.hpp"

namespace glimac {

    // Créer liste (vecteur), ajouter/supprimer cube, trier cubes selon texture ?
    CubeList::CubeList(){};
    CubeList::~CubeList(){};

    // Set texture
    void CubeList::setTextureIndex(int index, GLuint textureIndex){
        m_cubeList[index].setTextureIndex(textureIndex);
    };

    // Set cube index
    void CubeList::setCubeIndex(int index, GLuint cubeIndex){
        m_cubeList[index].setCubeIndex(cubeIndex);
    }

    // Scale
    void CubeList::setScale(GLuint cubeIndex, GLfloat x, GLfloat y, GLfloat z){
        m_cubeList[cubeIndex].setScale(x, y, z);
    }
    // Rotate
    void CubeList::setRot(GLuint cubeIndex, GLfloat degrees, GLfloat x, GLfloat y, GLfloat z){
        m_cubeList[cubeIndex].setRot(degrees, x, y, z);
    }
    // Translate
    void CubeList::setTrans(GLuint cubeIndex, GLfloat x, GLfloat y, GLfloat z){
        m_cubeList[cubeIndex].setTrans(x, y, z);
    }

    // Push back a new cube at the end of the list
    void CubeList::addCube(Cube cube){
        m_cubeList.push_back(cube);
        m_cubeList[m_cubeList.size()-1].setCubeIndex(m_cubeList.size()-1);
    }

    // Erase a cube at index "index" if exists
    void CubeList::deleteCube(int index){
        if(index<=m_cubeList.size()){
            m_cubeList.erase(m_cubeList.begin()+index-1);
        }
        
    }

    // Translate
    void CubeList::translateCube(int index, GLfloat tx, GLfloat ty, GLfloat tz){
        m_cubeList[index].translateVertices(tx, ty, tz);
    };

    // Sort cubes according to texture
    /*bool CubeList::compareCubes(const int index1, const int index2)
    {
        return m_cubeList[index1].getTextureIndex() < m_cubeList[index2].getTextureIndex();
    }*/
    void CubeList::sortCubes(){
        std::sort(m_cubeList.begin(), m_cubeList.end(), std::greater<Cube>());
    }

    // Print cubes
    void CubeList::printCubes(){
        for(int i=0; i<m_cubeList.size(); i++){
            std::cout << "Index " << i << ": " << m_cubeList[i].getTextureIndex() << "-- cube index: " << m_cubeList[i].getCubeIndex() << std::endl;
        }
    }

}

