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
    m_position = glm::vec3(0,0,5);
    // Initial horizontal angle : toward -Z
    m_horizontalAngle = 3.14f;
    // Initial vertical angle : none
    m_verticalAngle = 0.0f;
    // Initial Field of View
    m_initialFoV = 45.0f;

    m_speed = 0.05f; 

    // Direction : Spherical coordinates to Cartesian coordinates conversion
	m_direction = glm::vec3 (
		cos(m_verticalAngle) * sin(m_horizontalAngle),
		sin(m_verticalAngle),
		cos(m_verticalAngle) * cos(m_horizontalAngle)
	);

	// Right vector
	m_right = glm::vec3(
		sin(m_horizontalAngle - 3.14f/2.0f),
		0,
		cos(m_horizontalAngle - 3.14f/2.0f)
	);

	// Up vector
    m_up = glm::cross( m_right, m_direction );
}

void Controls::calculateVectors(){
    
    // Direction : Spherical coordinates to Cartesian coordinates conversion
	m_direction = glm::vec3 (
		cos(m_verticalAngle) * sin(m_horizontalAngle),
		sin(m_verticalAngle),
		cos(m_verticalAngle) * cos(m_horizontalAngle)
	);

	// Right vector
	m_right = glm::vec3(
		sin(m_horizontalAngle - 3.14f/2.0f),
		0,
		cos(m_horizontalAngle - 3.14f/2.0f)
	);

	// Up vector
    m_up = glm::cross( m_right, m_direction );
}

glm::mat4 Controls::getViewMatrix() const{
	return this->m_ViewMatrix;
}
glm::mat4 Controls::getProjectionMatrix() const{
	return this->m_ProjectionMatrix;
}

glm::vec3 Controls::getPosition() const{
    return m_position;
}
void Controls::setPosition(glm::vec3 newPos){
    m_position = newPos;
}
float Controls::getHorizontalAngle() const{
    return m_horizontalAngle;
}
void Controls::setHorizontalAngle(float newAngle){
    m_horizontalAngle = newAngle;
}
float Controls::getVerticalAngle() const{
    return m_verticalAngle;
}
void Controls::setVerticalAngle(float newAngle){
    m_verticalAngle = newAngle;
}
glm::vec3 Controls::getUp() const{
    return m_up;
}
void Controls::setUp(glm::vec3 newVec){
    m_up = newVec;
}
float Controls::getSpeed() const{
    return m_speed;
}
void Controls::setSpeed(float newSpeed){
    m_speed = newSpeed;
}
glm::vec3 Controls::getRight() const{
    return m_right;
}
void Controls::setRight(glm::vec3 newRight){
    m_right = newRight;
}
glm::vec3 Controls::getDirection() const{
    return m_direction;
}
void Controls::setDirection(glm::vec3 newDirection){
    m_direction = newDirection;
}

void Controls::computeFinalMatrices(){

	
    float FoV = m_initialFoV;//  * MouseWheel();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    this->m_ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

    this->m_ViewMatrix = glm::lookAt(
        m_position,           // Camera is here
        m_position+m_direction, // and looks here : at the same position, plus "direction"
        m_up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

    return;
}

}
