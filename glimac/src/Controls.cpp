/**
 * \file Controls.cpp
 * \brief Gestion des caméras
 * \author MANSION Amélia & SGRO' Manon
 * \version 0.1
 * \date 20 décembre 2019
 *
 * Gestion des caméras dans la scène (sur les axes x,y,z)
 *
 */

#include "glimac/Controls.hpp"

namespace glimac {

Controls::Controls(){
    // Initial position : on +Z
    position = glm::vec3(0,0,20);
    // Initial horizontal angle : toward -Z
    horizontalAngle = 3.14f;
    // Initial vertical angle : none
    verticalAngle = 0.0f;
    // Initial Field of View
    initialFoV = 45.0f;

    speed = 0.05f; // 3 units / second

    // Direction : Spherical coordinates to Cartesian coordinates conversion
	direction = glm::vec3 (
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	// Up vector
    up = glm::cross( right, direction );
}

void Controls::calculateVectors(){
    
    // Direction : Spherical coordinates to Cartesian coordinates conversion
	direction = glm::vec3 (
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	// Up vector
    up = glm::cross( right, direction );
}

glm::mat4 Controls::getViewMatrix(){
	return this->ViewMatrix;
}
glm::mat4 Controls::getProjectionMatrix(){
	return this->ProjectionMatrix;
}

glm::vec3 Controls::getPosition(){
    return position;
}
void Controls::setPosition(glm::vec3 newPos){
    position = newPos;
}
float Controls::getHorizontalAngle(){
    return horizontalAngle;
}
void Controls::setHorizontalAngle(float newAngle){
    horizontalAngle = newAngle;
}
float Controls::getVerticalAngle(){
    return verticalAngle;
}
void Controls::setVerticalAngle(float newAngle){
    verticalAngle = newAngle;
}
glm::vec3 Controls::getUp(){
    return up;
}
void Controls::setUp(glm::vec3 newVec){
    up = newVec;
}
float Controls::getSpeed(){
    return speed;
}
void Controls::setSpeed(float newSpeed){
    speed = newSpeed;
}
glm::vec3 Controls::getRight(){
    return right;
}
void Controls::setRight(glm::vec3 newRight){
    right = newRight;
}
glm::vec3 Controls::getDirection(){
    return direction;
}
void Controls::setDirection(glm::vec3 newDirection){
    direction = newDirection;
}

void Controls::computeFinalMatrices(){

	
    float FoV = initialFoV;//  * MouseWheel();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    this->ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

    this->ViewMatrix = glm::lookAt(
        position,           // Camera is here
        position+direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

    return;
}

}
