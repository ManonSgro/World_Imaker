/**
 * \file Controls.hpp
 * \brief Gestion des caméras
 * \author MANSION Amélia & SGRO' Manon
 * \version 0.1
 * \date 20 décembre 2019
 *
 * Gestion des caméras dans la scène (sur les axes x,y,z)
 *
 */

#pragma once
#include "common.hpp"


namespace glimac {

    /*! \class Controls
    * \brief Classe representant une camera
    *
    *  La classe gère la création et la manipulation de la caméra dans une scène 3D.
    */


    class Controls {

        public:
            // Constructor & destructor
            /*!
            *  \brief Constructeur
            *
            *  Constructeur de la classe Controls
            *
            *  \param null : aucuns parametres nécéssaires
            */
            Controls();
            /*!
            *  \brief Destructeur
            *
            *  Destructeur de la classe Controls
            *
            *  \param null : aucuns parametres nécéssaires
            */
            ~Controls(){};

            // General
            /*!
            *  \brief Mise à jour des informations caméra
            *
            *  Mise à jours de direction & right & up
            *
            *  \param null : aucuns parametres nécéssaires
            */
            void calculateVectors();
            /*!
            *  \brief Mise à jour des informations caméra
            *
            *  Mise à jour de la ProjectionMatrix & ViewMatrix
            *
            *  \param null : aucuns parametres nécéssaires
            */
            void computeFinalMatrices();

            // Getter & setter
            /*!
            *  \brief Informations de la ViewMatrix
            *
            *  Récuperer les informations de la ViewMatrix
            *
            *  \param null : aucuns parametres nécéssaires
            */
            glm::mat4 getViewMatrix() const;
            /*!
            *  \brief Informations de la ProjectionMatrix
            *
            *  Récuperer les informations de la ProjectionMatrix
            *
            *  \param null : aucuns parametres nécéssaires
            */
            glm::mat4 getProjectionMatrix() const;
            /*!
            *  \brief Informations de la position
            *
            *  Récuperer les informations du vecteur position
            *
            *  \param null : aucuns parametres nécéssaires
            */
            glm::vec3 getPosition() const;
            /*!
            *  \brief Edition de la position
            *
            *  Modifier les informations du vecteur position
            *
            *  \param newPos : nouveau vecteur position 
            */
            void setPosition(glm::vec3 newPos);
            /*!
            *  \brief Informations de l'angle horizontal
            *
            *  Récuperer les informations du vecteur HorizontalAngle
            *
            *  \param null : aucuns parametres nécéssaires
            */
            float getHorizontalAngle() const;
            /*!
            *  \brief Edition de l'angle horizontal
            *
            *  Modifier les informations du vecteur HorizontalAngle
            *
            *  \param newAngle : nouveau vecteur HorizontalAngle 
            */
            void setHorizontalAngle(float newAngle);
            /*!
            *  \brief Informations de l'angle vertical
            *
            *  Récuperer les informations du vecteur VerticalAngle
            *
            *  \param null : aucuns parametres nécéssaires
            */
            float getVerticalAngle() const;
            /*!
            *  \brief Edition de l'angle vertical
            *
            *  Modifier les informations du vecteur VerticalAngle
            *
            *  \param newAngle : nouveau VerticalAngle 
            */
            void setVerticalAngle(float newAngle);
            /*!
            *  \brief Informations de up
            *
            *  Récuperer les informations du vecteur up
            *
            *  \param null : aucuns parametres nécéssaires
            */
            glm::vec3 getUp() const;
            /*!
            *  \brief Edition de up
            *
            *  Modifier les informations du vecteur up
            *
            *  \param newVec : nouveau vecteur up
            */
            void setUp(glm::vec3 newVec);
            /*!
            *  \brief Informations sur speed
            *
            *  Récuperer les informations du float speed
            *
            *  \param null : aucuns parametres nécéssaires
            */
            float getSpeed() const;
            /*!
            *  \brief Edition de speed
            *
            *  Modifier les informations du float speed
            *
            *  \param newSpeed : nouveau float speed
            */
            void setSpeed(float newSpeed);
            /*!
            *  \brief Informations de right
            *
            *  Récuperer les informations du vecteur right
            *
            *  \param null : aucuns parametres nécéssaires
            */
            glm::vec3 getRight() const;
            /*!
            *  \brief Edition de right
            *
            *  Modifier les informations du vecteur right
            *
            *  \param newRight : nouveau vecteur right
            */
            void setRight(glm::vec3 newRight);
            /*!
            *  \brief Informations de direction
            *
            *  Récuperer les informations du vecteur direction
            *
            *  \param null : aucuns parametres nécéssaires
            */
            glm::vec3 getDirection() const;
            /*!
            *  \brief Edition de direction
            *
            *  Modifier les informations du vecteur direction
            *
            *  \param newDirection : nouveau vecteur rigdirectionht
            */
            void setDirection(glm::vec3 newDirection);


        private :
            // Attributes
            glm::mat4 m_ViewMatrix; /*!< Matrice de Vue*/
            glm::mat4 m_ProjectionMatrix; /*!< Matrice de Projection*/

            float m_horizontalAngle; /*!< Valeur de l'angle horizontal*/
            float m_verticalAngle; /*!< Valeur de l'angle vertical*/
            float m_initialFoV; /*!< Valeur du champ de vision (niveau de zoom)*/

            float m_speed; /*!< Valeur de la vitesse*/

            glm::vec3 m_position; /*!< Vecteur de postion*/
            glm::vec3 m_direction; //*!< Vecteur de sur l'axe z */
            glm::vec3 m_right; /*!< Vecteur de sur l'axe x */
            glm::vec3 m_up; /*!< Vecteur de sur l'axe y */

    };


}
