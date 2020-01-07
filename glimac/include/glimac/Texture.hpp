/**
 * \file Texture.hpp
 * \brief Gestion des textures
 * \author MANSION Amélia & SGRO' Manon
 * \version 0.1
 * \date 20 décembre 2019
 *
 * Gestion des textures dans la scène
 *
 */

#pragma once

#include "common.hpp"
#include "Image.hpp"
#include "Program.hpp"

namespace glimac {

    /*! \class Texture
    * \brief Classe permettant la gestion des textures dans la scène
    *
    *  La classe gère la création et la manipulation de textures dans une scène 3D.
    */
    class Texture {

    public:
        // Constructor & destructor
        /*!
        *  \brief Constructeur
        *
        *  Constructeur de la classe Texture
        *
        *  \param null : aucuns parametres nécéssaires
        */
        Texture();
        /*!
        *  \brief Destructeur
        *
        *  Destructeur de la classe Texture
        *
        *  \param null : aucuns parametres nécéssaires
        */
        ~Texture();
        /*!
        *  \brief Mise à jour des informations de Uniform Location
        *
        *  Mise à jour des informations de Uniform Location
        *
        *  \param program : programme
        *  \param name : nom de la UL
        */
        void setUniformLocation(Program &program, const GLchar* name);
        /*!
        *  \brief Mise à jour des informations de l'image
        *
        *  Mise à jour des informations de l'image
        *
        *  \param filepath : chemin d'acces au fichier
        */
        void setImage(const FilePath &filepath);
        /*!
        *  \brief Informations de la texture
        *
        *  Récuperer les informations de la texture
        *
        *  \param null : aucuns parametres nécéssaires
        */
        GLuint getTexture() const{
            return m_texture;
        }
        /*!
        *  \brief Pointeur sur la texture
        *
        *  Récuperer un pointeur sur la texture
        *
        *  \param null : aucuns parametres nécéssaires
        */
        GLuint* getTexturePointer(){
            return &m_texture;
        }
        /*!
        *  \brief Informations sur la taille de l'image
        *
        *  Récuperer les informations sur la largeur de l'image
        *
        *  \param null : aucuns parametres nécéssaires
        */
        unsigned int getImageWidth() const{
            return m_image->getWidth();
        }
        /*!
        *  \brief Informations sur la taille de l'image
        *
        *  Récuperer les informations sur la hauteur de l'image
        *
        *  \param null : aucuns parametres nécéssaires
        */
        unsigned int getImageHeight() const{
            return m_image->getHeight();
        }
        /*!
        *  \brief Informations sur les pixels de l'image
        *
        *  Récuperer le vecteur pixel de l'image
        *
        *  \param null : aucuns parametres nécéssaires
        */
        const glm::vec4* getImagePixels() const{
            return m_image->getPixels();
        }
        /*!
        *  \brief Informations sur la Uniform Location
        *
        *  Récuperer les informations sur la Uniform Location
        *
        *  \param null : aucuns parametres nécéssaires
        */
        GLuint getUniformLocation() const{
            return m_uTexture;
        }

    private:
        GLint m_uTexture; /*!< Uniform Location*/
        std::unique_ptr<Image> m_image; /*!< Image Texture*/
        GLuint m_texture; /*!< Texture index qui necessite "bind"*/
    };

}
