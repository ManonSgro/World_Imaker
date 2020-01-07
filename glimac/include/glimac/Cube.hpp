/**
 * \file Cube.hpp
 * \brief Gestion des cubes
 * \author MANSION Amélia & SGRO' Manon
 * \version 0.1
 * \date 20 décembre 2019
 *
 * Gestion des cubes dans la scène (sur les axes x,y,z)
 *
 */

#pragma once
#include "common.hpp"

namespace glimac {

    /*! \class Cube
    * \brief Classe representant un cube
    *
    *  La classe gère la création et la manipulation d'un cube dans une scène 3D.
    */
    class Cube {

        public:
            // Constructor & destructor
            /*!
            *  \brief Constructeur
            *
            *  Constructeur de la classe Cube
            *
            *  \param null : aucuns parametres nécéssaires
            */
            Cube():
                m_nVertexCount(0) {
                build();
            }
            /*!
                *  \brief Destructeur
                *
                *  Destructeur de la classe Cube
                *
                *  \param null : aucuns parametres nécéssaires
                */
            ~Cube(){}; 

            // General
            /*!
            *  \brief Alloue et construit les données
            *
            *  Constructeur: alloue le tableau de données et construit les attributs des vertex
            *
            *  \param null : aucuns parametres nécéssaires
            */
            void build();
            /*!
            *  \brief Comparaison de cubes
            *
            *  Compare deux cubes par surcharge de l'opérateur >
            *
            *  \param cubeToCompare : cube à comparer à celui en sélection
            */
            bool operator > (const Cube& cubeToCompare) const
            {
                return (m_textureIndex > cubeToCompare.m_textureIndex);
            }
            /*!
            *  \brief Déplacement des Vertices
            *
            *  Modifie les coordonées (x, y ,z) des Vertices du cube
            *
            *  \param tx : float des nouvelles coordonees sur l'axe x
            *  \param ty : float des nouvelles coordonees sur l'axe y
            *  \param tz : float des nouvelles coordonees sur l'axe z
            */
            void translateVertices(GLfloat tx, GLfloat ty, GLfloat tz);


            // Getter & setter
            /*!
            *  \brief Renvoit le pointeur vers les données
            *
            *  Renvoit le pointeur vers les données du cube
            *
            *  \param null : aucuns parametres nécéssaires
            */
            const Vertex3DTexture* getDataPointer() const {
                return &m_Vertices[0];
            }
            /*!
            *  \brief Renvoit le nombre de vertex
            *
            *  Renvoit le nombre de vertex du cube
            *
            *  \param null : aucuns parametres nécéssaires
            */
            GLsizei getVertexCount() const {
                return m_nVertexCount;
            }
            /*!
            *  \brief Renvoit le nombre de IBO
            *
            *  Renvoit le nombre de IBO du cube
            *
            *  \param null : aucuns parametres nécéssaires
            */
            GLsizei getIBOCount() const {
                return m_Index.size();
            }
            /*!
            *  \brief Renvoit le pointeur vers IBO
            *
            *  Renvoit le pointeur vers IBO du cube
            *
            *  \param null : aucuns parametres nécéssaires
            */
            const uint32_t* getIBOPointer() const {
                return &m_Index[0];
            }
            /*!
            *  \brief Renvoit le nombre de IBO pour le curseur
            *
            *  Renvoit le nombre de IBO du cube curseur
            *
            *  \param null : aucuns parametres nécéssaires
            */
            GLsizei getIBOCountBorder() const {
                return m_IndexBorder.size();
            }
            /*!
            *  \brief Renvoit le pointeur vers IBO pour le curseur
            *
            *  Renvoit le pointeur vers IBO du cube curseur
            *
            *  \param null : aucuns parametres nécéssaires
            */
            const uint32_t* getIBOPointerBorder() const {
                return &m_IndexBorder[0];
            }
            /*!
            *  \brief Modifie la texture
            *
            *  Modifie l'index de la texture que porte le cube
            *
            *  \param index : GLuint du nouvel index de la texture
            */
            void setTextureIndex(GLuint index);
            /*!
            *  \brief Informations sur la texture
            *
            *  Renvoit l'index de la texture que porte le cube
            *
            *  \param null : aucuns parametres nécéssaires
            */
            GLuint getTextureIndex() const{
                return m_textureIndex;
            };
            /*!
            *  \brief Modifie l'index du cube
            *
            *  Modifie l'index que porte le cube
            *
            *  \param index : GLuint du nouvel index du cube
            */
            void setCubeIndex(GLuint index);
            /*!
            *  \brief Informations sur le cube
            *
            *  Renvoit l'index que porte le cube
            *
            *  \param null : aucuns parametres nécéssaires
            */
            GLuint getCubeIndex() const{
                return m_cubeIndex;
            };
            /*!
            *  \brief Modifie la taille du cube
            *
            *  Modifie l'échelle / la taille que porte le cube (s'applique selon les axes cf. parametres)
            *
            *  \param x : GLfloat des nouvelles coordonees sur l'axe x
            *  \param y : GLfloat des nouvelles coordonees sur l'axe y
            *  \param z : GLfloat des nouvelles coordonees sur l'axe z
            */
            void setScale(GLfloat x, GLfloat y, GLfloat z);
            /*!
            *  \brief Informations sur la taille du cube
            *
            *  Renvoit l'échelle / la taille que porte le cube (retourne un vecteur avec les informations pour x,y,z)
            *
            *  \param null : aucuns parametres nécéssaires
            */
            glm::vec3 getScale() const{
                return m_scale;
            };
            /*!
            *  \brief Modifie la taille du cube (accepte le type float)
            *
            *  Modifie l'échelle / la taille que porte le cube (s'applique selon les axes cf. parametres)
            *
            *  \param x : GLfloat des nouvelles coordonees sur l'axe x
            *  \param y : GLfloat des nouvelles coordonees sur l'axe y
            *  \param z : GLfloat des nouvelles coordonees sur l'axe z
            */
            void setScaleFloat(GLfloat x, GLfloat y, GLfloat z); 
            /*!
            *  \brief Modifie la rotation du cube
            *
            *  Modifie l'angle de rotation que porte le cube (s'applique selon les axes et un angle cf. parametres)
            *
            *  \param degrees : GLfloat de l'angle de rotation
            *  \param x : GLfloat des nouvelles coordonees sur l'axe x
            *  \param y : GLfloat des nouvelles coordonees sur l'axe y
            *  \param z : GLfloat des nouvelles coordonees sur l'axe z
            */
            void setRot(GLfloat degrees, GLfloat x, GLfloat y, GLfloat z);
            /*!
            *  \brief Informations sur la rotation du cube
            *
            *  Renvoit la rotation que porte le cube 
            *
            *  \param null : aucuns parametres nécéssaires
            */
            glm::vec3 getRot() const{
                return m_rot;
            };
            /*!
            *  \brief Informations sur la rotation du cube
            *
            *  Renvoit le degres de rotation que porte le cube 
            *
            *  \param null : aucuns parametres nécéssaires
            */
            GLfloat getRotDeg() const{
                return m_rotDeg;
            };
            /*!
            *  \brief Modifie la position du cube
            *
            *  Effectue une translation de sorte que porte le cube soit déplacé (s'applique selon les axes cf. parametres)
            *
            *  \param x : GLfloat des nouvelles coordonees sur l'axe x
            *  \param y : GLfloat des nouvelles coordonees sur l'axe y
            *  \param z : GLfloat des nouvelles coordonees sur l'axe z
            */
            void setTrans(GLfloat x, GLfloat y, GLfloat z);
            /*!
            *  \brief Informations sur la translation du cube
            *
            *  Renvoit les coordonées que porte le cube dans le plan
            *
            *  \param null : aucuns parametres nécéssaires
            */
            glm::vec3 getTrans() const{
                return m_trans;
            };

        private:
            std::vector<Vertex3DTexture> m_Vertices; /*!< Tableau de vertices (vecteur)*/
            GLsizei m_nVertexCount; /*!< Nombre de sommets*/
            std::vector<uint32_t> m_Index; /*!< Indices des IBO*/
            std::vector<uint32_t> m_IndexBorder; /*!< Indices des IBO pour le curseur*/
            GLfloat m_edge; /*!< Cube size*/

            GLuint m_textureIndex; /*!< Indices des textures*/
            GLuint m_cubeIndex; /*!< Indices des cubes*/

            glm::vec3 m_scale; /*!< Vecteur de taille*/
            glm::vec3 m_rot; /*!< Vecteur de rotation*/
            GLfloat m_rotDeg; /*!< Angle de rotation*/
            glm::vec3 m_trans; /*!< Vecteur de translation*/
    };

}
