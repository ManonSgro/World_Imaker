/**
 * \file CubeList.hpp
 * \brief Gestion d'une liste de cubes
 * \author MANSION Amélia & SGRO' Manon
 * \version 0.1
 * \date 20 décembre 2019
 *
 * Gestion d'une liste de cubes
 *
 */

#pragma once

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include<Eigen/SparseLU>
#include <Eigen/Dense>
#include <fstream>

#include "common.hpp"
#include "Cube.hpp"

namespace glimac {

    /*! \class CubeList
    * \brief Classe representant une liste de cubes
    *
    *  La classe gère la création et la manipulation d'une liste de cubes dans une scène 3D.
    */
    class CubeList {

        public:

            // Constructor & destructor
            /*!
            *  \brief Constructeur
            *
            *  Constructeur de la classe Cube
            *
            *  \param null : aucuns parametres nécéssaires
            */
            CubeList();
            /*!
            *  \brief Destructeur
            *
            *  Destructeur de la classe Cube
            *
            *  \param null : aucuns parametres nécéssaires
            */
            ~CubeList();

            // Getter & setter
            /*!
            *  \brief Renvoit la taille de la liste
            *
            *  Renvoit la taille de la liste
            *
            *  \param null : aucuns parametres nécéssaires
            */
            uint getSize(){
                return m_cubeList.size();
            };

            /*!
            *  \brief Renvoit l'attribut position du VBO
            *
            *  Renvoit l'attribut position du VBO
            *
            *  \param null : aucuns parametres nécéssaires
            */
            const GLuint getVBOPositionAttribute(){
                return VERTEX_ATTR_POSITION;
            }

            /*!
            *  \brief Renvoit l'attribut normal du VBO
            *
            *  Renvoit l'attribut normal du VBO
            *
            *  \param null : aucuns parametres nécéssaires
            */
            const GLuint getVBONormalAttribute(){
                return VERTEX_ATTR_NORMAL;
            }

            /*!
            *  \brief Renvoit l'attribut texture du VBO
            *
            *  Renvoit l'attribut texture du VBO
            *
            *  \param null : aucuns parametres nécéssaires
            */
            const GLuint getVBOTextureAttribute(){
                return VERTEX_ATTR_TEXTURE;
            }

            /*!
            *  \brief Renvoit le pointeur sur un item de la VAO list
            *
            *  Renvoit le pointeur sur un item de la VAO list
            *
            *  \param index : index de l'item à renvoyer
            */
            GLuint* getVAOListItem(int index){
                return &vaoList[index];
            }
            /*!
            *  \brief Renvoit le pointeur sur la VAO list
            *
            *  Renvoit le pointeur sur la VAO list
            *
            *  \param null : aucun paramètre nécessaire
            */
            std::vector<GLuint>* getVAOList(){
                return &vaoList;
            }
            /*!
            *  \brief Renvoit le pointeur sur un item la IBO list
            *
            *  Renvoit le pointeur sur un item de la IBO list
            *
            *  \param index:index de l'item à renvoyer
            */
            GLuint* getIBOListItem(int index){
                return &iboList[index];
            }
            /*!
            *  \brief Renvoit le pointeur sur la IBO list
            *
            *  Renvoit le pointeur sur la IBO list
            *
            *  \param null : aucun paramètre nécessaire
            */
            std::vector<GLuint>* getIBOList(){
                return &iboList;
            }
            /*!
            *  \brief Renvoit le pointeur sur un item de la VBO list
            *
            *  Renvoit le pointeur sur un item de la VBO list
            *
            *  \param index : index de l'item à renvoyer
            */
            GLuint* getVBOListItem(int index){
                return &vboList[index];
            }
            /*!
            *  \brief Renvoit le pointeur sur la IBO list
            *
            *  Renvoit le pointeur sur la IBO list
            *
            *  \param null : aucun paramètre nécessaire
            */
            std::vector<GLuint>* getVBOList(){
                return &vboList;
            }
            /*!
            *  \brief Génère une liste de vertex buffer
            *
            *  Génère une liste de vertex buffer pour les cubes de la cube list
            *
            *  \param null : aucun paramètre nécessaire
            */
            void generateVBO();
            /*!
            *  \brief Génère une liste de vao
            *
            *  Génère une liste de vao pour les cubes de la cube list
            *
            *  \param null : aucun paramètre nécessaire
            */
            void generateVAO();
            /*!
            *  \brief Génère une liste de ibo
            *
            *  Génère une liste de ibo pour les cubes de la cube list
            *
            *  \param null : aucun paramètre nécessaire
            */
            void generateIBO();
            /*!
            *  \brief Renvoit le nombre de vertex
            *
            *  Renvoit le nombre de vertex d'un cube
            *
            *  \param index : index du cube associé aux vertex
            */
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
            Eigen::VectorXd radialBasisFunction(Eigen::MatrixXd points, std::string rbf="default", float epsilon=1.0);
            double interpolatePoints(double x, double y, Eigen::MatrixXd points, std::string rbf="default", float epsilon=1.0);

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
