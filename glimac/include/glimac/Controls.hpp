#pragma once

#include "common.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>


namespace glimac {

// Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Controls {

public:
    Controls();
    ~Controls();
    void calculateVectors();
    void computeMatricesFromInputs(float wW, float wH);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    glm::vec3 getPosition();
    void setPosition(glm::vec3 newPos);
    float getHorizontalAngle();
    void setHorizontalAngle(float newAngle);
    float getVerticalAngle();
    void setVerticalAngle(float newAngle);
    glm::vec3 getUp();
    void setUp(glm::vec3 newVec);
    float getSpeed();
    void setSpeed(float newSpeed);
    glm::vec3 getRight();
    void setRight(glm::vec3 newRight);
    glm::vec3 getDirection();
    void setDirection(glm::vec3 newDirection);


private :
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    glm::vec3 position;
    float horizontalAngle;
    float verticalAngle;
    float initialFoV;

    float speed;

    // Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction;

	// Right vector
	glm::vec3 right;

	// Up vector
    glm::vec3 up;
};


}
