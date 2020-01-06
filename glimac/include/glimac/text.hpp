/**
 * \file text.hpp
 * \brief Gestion des elements avec bmp et ddds
 * \author MANSION Amélia & SGRO' Manon
 * \version 0.1
 * \date 20 décembre 2019
 *
 * Gestion des elements avec bmp et ddds
 *
 */

#ifndef TEXT_HPP
#define TEXT_HPP


#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Controls.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Texture.hpp>
#include <glimac/objloader.hpp>
#include <cstddef>
#include <vector>



GLuint loadBMP_custom(const char * imagepath);

GLuint loadDDS(const char * imagepath);


#endif
