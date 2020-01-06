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
            uint getSize() const{
                return m_cubeList.size();
            };

            /*!
            *  \brief Renvoit l'attribut position du VBO
            *
            *  Renvoit l'attribut position du VBO
            *
            *  \param null : aucuns parametres nécéssaires
            */
            const GLuint getVBOPositionAttribute() const{
                return VERTEX_ATTR_POSITION;
            }

            /*!
            *  \brief Renvoit l'attribut normal du VBO
            *
            *  Renvoit l'attribut normal du VBO
            *
            *  \param null : aucuns parametres nécéssaires
            */
            const GLuint getVBONormalAttribute() const{
                return VERTEX_ATTR_NORMAL;
            }

            /*!
            *  \brief Renvoit l'attribut texture du VBO
            *
            *  Renvoit l'attribut texture du VBO
            *
            *  \param null : aucuns parametres nécéssaires
            */
            const GLuint getVBOTextureAttribute() const{
                return VERTEX_ATTR_TEXTURE;
            }

            /*!
            *  \brief Renvoit le pointeur sur un item de la VAO list
            *
            *  Renvoit le pointeur sur un item de la VAO list
            *
            *  \param index : index de l'item à renvoyer
            */
            GLuint* getVAOListItem(int index) {
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
            GLuint* getIBOListItem(int index) {
                return &iboList[index];
            }
            /*!
            *  \brief Renvoit le pointeur sur la IBO list
            *
            *  Renvoit le pointeur sur la IBO list
            *
            *  \param null : aucun paramètre nécessaire
            */
            std::vector<GLuint>* getIBOList() {
                return &iboList;
            }
            /*!
            *  \brief Renvoit le pointeur sur un item de la VBO list
            *
            *  Renvoit le pointeur sur un item de la VBO list
            *
            *  \param index : index de l'item à renvoyer
            */
            GLuint* getVBOListItem(int index) {
                return &vboList[index];
            }
            /*!
            *  \brief Renvoit le pointeur sur la IBO list
            *
            *  Renvoit le pointeur sur la IBO list
            *
            *  \param null : aucun paramètre nécessaire
            */
            std::vector<GLuint>* getVBOList() {
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
            *  \param index : index du cube associé
            */
            GLsizei getVertexCount(int index) const{
                return m_cubeList[index].getVertexCount();
            };
            /*!
            *  \brief Renvoit un pointeur sur données
            *
            *  Renvoit un pointeur sur données d'un cube
            *
            *  \param index : index du cube associé
            */
            const Vertex3DTexture* getDataPointer(int index) const{
                return m_cubeList[index].getDataPointer();
            };
            /*!
            *  \brief Renvoit le nombre d'ibo
            *
            *  Renvoit le nombre d'ibo d'un cube
            *
            *  \param index : index du cube associé
            */
            GLsizei getIBOCount(int index) const{
                return m_cubeList[index].getIBOCount();
            };
            /*!
            *  \brief Renvoit un pointeur sur ibo
            *
            *  Renvoit un pointeur sur ibo d'un cube
            *
            *  \param index : index du cube associé
            */
            const uint32_t* getIBOPointer(int index) const{
                return m_cubeList[index].getIBOPointer();
            };
            /*!
            *  \brief Renvoit l'index de la texture
            *
            *  Renvoit l'index de la texture d'un cube
            *
            *  \param index : index du cube associé
            */
            GLuint getTextureIndex(int index) const{
                return m_cubeList[index].getTextureIndex();
            };
            /*!
            *  \brief Modifie l'index de la texture
            *
            *  Modifie l'index de la texture d'un cube
            *
            *  \param index : index du cube associé
            *  \param textureIndex : nouvelle index de la texture
            */
            void setTextureIndex(int index, GLuint textureIndex);
            /*!
            *  \brief Modifie l'index d'un cube
            *
            *  Modifie l'index d'un cube dans la liste
            *
            *  \param index : index du cube associé
            *  \param cubeIndex : nouvelle index du cube
            */
            void setCubeIndex(int index, GLuint cubeIndex);
            /*!
            *  \brief Renvoit l'index d'un cube
            *
            *  Renvoit l'index d'un cube dans la liste
            *
            *  \param index : index du cube associé
            */
            GLuint getCubeIndex(int index){
                return m_cubeList[index].getCubeIndex();
            };
            /*!
            *  \brief Modifie l'echelle d'un cube
            *
            *  Modifie l'echelle d'un cube dans la liste
            *
            *  \param index : index du cube associé
            *  \param x : nouvelles coordonées x
            *  \param y : nouvelles coordonées y
            *  \param z : nouvelles coordonées z
            */
            void setScale(GLuint cubeIndex, GLfloat x, GLfloat y, GLfloat z);
            /*!
            *  \brief Renvoit l'echelle d'un cube
            *
            *  Renvoit le vecteur echelle d'un cube dans la liste
            *
            *  \param index : index du cube associé
            */
            glm::vec3 getScale(int index) const{
                return m_cubeList[index].getScale();
            };
            /*!
            *  \brief Modifie la rotation d'un cube
            *
            *  Modifie la rotation d'un cube dans la liste
            *
            *  \param index : index du cube associé
            *  \param degrees : degre de rotation
            *  \param x : nouvelles coordonées x
            *  \param y : nouvelles coordonées y
            *  \param z : nouvelles coordonées z
            */
            void setRot(GLuint cubeIndex, GLfloat degrees, GLfloat x, GLfloat y, GLfloat z);
            /*!
            *  \brief Renvoit la rotation d'un cube
            *
            *  Renvoit le vecteur rotation d'un cube dans la liste
            *
            *  \param index : index du cube associé
            */
            glm::vec3 getRot(int index) const{
                return m_cubeList[index].getRot();
            };
            /*!
            *  \brief Renvoit le degre de rotation d'un cube
            *
            *  Renvoit le degre de rotation d'un cube dans la liste
            *
            *  \param index : index du cube associé
            */
            GLfloat getRotDeg(int index) const{
                return m_cubeList[index].getRotDeg();
            };
            /*!
            *  \brief Modifie la position d'un cube
            *
            *  Modifie la position d'un cube dans la liste
            *
            *  \param index : index du cube associé
            *  \param x : nouvelles coordonées x
            *  \param y : nouvelles coordonées y
            *  \param z : nouvelles coordonées z
            */
            void setTrans(GLuint cubeIndex, GLfloat x, GLfloat y, GLfloat z);
            /*!
            *  \brief Renvoit la translation d'un cube
            *
            *  Renvoit le vecteur de translation d'un cube dans la liste
            *
            *  \param index : index du cube associé
            */
            glm::vec3 getTrans(int index) const{
                return m_cubeList[index].getTrans();
            };
            /*!
            *  \brief Ajout d'un cube
            *
            *  Ajout d'un cube à la liste
            *
            *  \param cube : cube à ajouter
            */
            void addCube(Cube cube);
            /*!
            *  \brief Suppression d'un cube
            *
            *  Suppression d'un cube de la liste
            *
            *  \param index : index du cube à supprimer
            */
            void deleteCube(int index);
            /*!
            *  \brief Tri de la liste
            *
            *  Tri de la liste de cubes
            *
            *  \param null : aucun paramètre nécessaire
            */
            void sortCubes();
            /*!
            *  \brief Sauvegarde
            *
            *  Sauvegardes des éléments
            *
            *  \param filepath : chemin de sauvegarde
            *  \param item_LightD : on / off (0 ou 1)
            *  \param positionLightD : vecteur position de la lumière directionnelle
            *  \param item_LightP : on / off (0 ou 1)
            *  \param positionLightP : vecteur position de la lumière ponctuelle
            */
            void save(std::string filepath, int item_LightD, std::vector<int> positionLightD, int item_LightP, std::vector<int> positionLightP);
            /*!
            *  \brief Lecture
            *
            *  Lecture des éléments
            *
            *  \param filepath : chemin d'accès
            *  \param destination : vecteur destination
            */
            void read(std::string filePath, std::vector<int> &destination);
            /*!
            *  \brief Chargement
            *
            *  Chargement des éléments
            *
            *  \param file : vecteur file
            *  \param cursorPosition : vecteur cursorPosition
            *  \param currentActive : vecteur currentActive
            *  \param item_LightD : on / off (0 ou 1)
            *  \param positionLightD : vecteur position de la lumière directionnelle
            *  \param item_LightP : on / off (0 ou 1)
            *  \param positionLightP : vecteur position de la lumière ponctuelle
            */
            void load(std::vector<int> file, std::vector<int> &cursorPosition, int &currentActive, int &item_LightD, std::vector<int> &positionLightD, int &item_LightP, std::vector<int> &positionLightP);
            /*!
            *  \brief Affichage en console
            *
            *  Affichage en console de la liste de cubes
            *
            *  \param null : aucun paramètre nécessaire
            */
            void printCubes();
            /*!
            *  \brief Generation de Radial Basis Function
            *
            *  Generation de Radial Basis Function
            *
            *  \param points : matrice de points
            *  \param rbf : choix de la RBF utilisée
            */
            Eigen::VectorXd radialBasisFunction(Eigen::MatrixXd points, std::string rbf="default");
            /*!
            *  \brief Interpolation de points
            *
            *  Interpolation de points
            *
            *  \param x : point x
            *  \param y : point y
            *  \param points : matrice de points
            *  \param rbf : choix de la RBF utilisée
            */
            double interpolatePoints(double x, double y, Eigen::MatrixXd points, std::string rbf="default");

        private:
            // Attributes
            std::vector<Cube> m_cubeList; /*!< Liste de cubes*/
            std::vector<GLuint> vboList; /*!< Liste vbo*/
            std::vector<GLuint> vaoList; /*!< Liste vao*/
            std::vector<GLuint> iboList; /*!< Liste ibo*/
            const GLuint VERTEX_ATTR_POSITION = 0;
            const GLuint VERTEX_ATTR_NORMAL = 1;
            const GLuint VERTEX_ATTR_TEXTURE = 2;
    };

}
