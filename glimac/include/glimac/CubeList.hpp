#pragma once

#include <vector>
#include <Eigen/Dense>
#include <fstream>

#include "common.hpp"
#include "Cube.hpp"

namespace glimac {

class CubeList {

public:

    // Constructeur
    CubeList();
    ~CubeList();

    // Get size
    uint getSize(){
        return m_cubeList.size();
    };

    // Get VBO attributes
    const GLuint getVBOPositionAttribute(){
        return VERTEX_ATTR_POSITION;
    }
    const GLuint getVBONormalAttribute(){
        return VERTEX_ATTR_NORMAL;
    }
    const GLuint getVBOTextureAttribute(){
        return VERTEX_ATTR_TEXTURE;
    }


    // Get VAO list
    GLuint* getVAOListItem(int index){
        return &vaoList[index];
    }
    std::vector<GLuint>* getVAOList(){
        return &vaoList;
    }

    // Get IBO list
    GLuint* getIBOListItem(int index){
        return &iboList[index];
    }
    std::vector<GLuint>* getIBOList(){
        return &iboList;
    }

    // Get VBO list
    GLuint* getVBOListItem(int index){
        return &vboList[index];
    }
    std::vector<GLuint>* getVBOList(){
        return &vboList;
    }

    // Set VAO list

    // Set IBO list

    // Generate VBO
    void generateVBO();

    // Generate VAO
    void generateVAO();

    // Generate IBO
    void generateIBO();

    // Get vertex count
    GLsizei getVertexCount(int index){
        return m_cubeList[index].getVertexCount();
    };

    // Get data pointer
    const Vertex3DTexture* getDataPointer(int index) const{
        return m_cubeList[index].getDataPointer();
    };

    // Get ibo count
    GLsizei getIBOCount(int index) const{
        return m_cubeList[index].getIBOCount();
    };

    // Get ibo count
    const uint32_t* getIBOPointer(int index) const{
        return m_cubeList[index].getIBOPointer();
    };

    // Get texture index
    GLuint getTextureIndex(int index){
        return m_cubeList[index].getTextureIndex();
    };

    // Set texture
    void setTextureIndex(int index, GLuint textureIndex);

    // Set cube index
    void setCubeIndex(int index, GLuint cubeIndex);
    GLuint getCubeIndex(int index){
        return m_cubeList[index].getCubeIndex();
    };

    // Scale
    void setScale(GLuint cubeIndex, GLfloat x, GLfloat y, GLfloat z);
    glm::vec3 getScale(int index){
        return m_cubeList[index].getScale();
    };
    // Rotate
    void setRot(GLuint cubeIndex, GLfloat degrees, GLfloat x, GLfloat y, GLfloat z);
    glm::vec3 getRot(int index){
        return m_cubeList[index].getRot();
    };
    GLfloat getRotDeg(int index){
        return m_cubeList[index].getRotDeg();
    };
    // Translate
    void setTrans(GLuint cubeIndex, GLfloat x, GLfloat y, GLfloat z);
    glm::vec3 getTrans(int index){
        return m_cubeList[index].getTrans();
    };

    //Ajouter/supprimer cube
    void addOrigin();
    //void addCube(Cube cube, std::vector<GLuint> &iboList, std::vector<GLuint> &vaoList, std::vector<GLuint> &vboList, GLuint VERTEX_ATTR_POSITION, GLuint VERTEX_ATTR_NORMAL, GLuint VERTEX_ATTR_TEXTURE);
    void addCube(Cube cube);
    void deleteCube(int index);

    // Translate
    void translateCube(int index, GLfloat tx, GLfloat ty, GLfloat tz);

    //bool compareCubes(const int index1, const int index2);
    void sortCubes();

    void save(std::string filepath, int item_LightD, std::vector<int> positionLightD, int item_LightP, std::vector<int> positionLightP);
    void read(std::string filePath, std::vector<int> &destination);
    void load(std::vector<int> file, std::vector<int> &cursorPosition, int &currentActive, int &item_LightD, std::vector<int> &positionLightD, int &item_LightP, std::vector<int> &positionLightP);

    void printCubes();
    Eigen::VectorXd radialBasisFunction(Eigen::MatrixXd points);
    double interpolatePoints(double x, double y, Eigen::MatrixXd points);

//private:
    std::vector<Cube> m_cubeList;

    std::vector<GLuint> vboList;
    std::vector<GLuint> vaoList;
    std::vector<GLuint> iboList;
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;
};

}
