#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Controls.hpp"

namespace glimac {

glm::mat4 Controls::getViewMatrix(){
	return this->ViewMatrix;
}
glm::mat4 Controls::getProjectionMatrix(){
	return this->ProjectionMatrix;
}




// Initial position : on +Z
glm::vec3 position = glm::vec3(0,0,5);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 0.05f; // 3 units / second

void Controls::computeMatricesFromInputs(float wW, float wH, SDL_Event e){
    int posX = e.button.x;
    int posY = e.button.y;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	// Up vector
    glm::vec3 up = glm::cross( right, direction );

    // Move
    if (e.type == SDL_KEYDOWN){
        if (e.key.keysym.sym == SDLK_KP_8){
            position += up * speed;
        }
        if (e.key.keysym.sym == SDLK_KP_2){
            position -= up * speed;
        }
        if (e.key.keysym.sym == SDLK_KP_6){
            position += right * speed;
        }
        if (e.key.keysym.sym == SDLK_KP_4){
            position -= right * speed;
        }
        if (e.key.keysym.sym == SDLK_KP_PLUS){
            position += direction * speed;
        }
        if (e.key.keysym.sym == SDLK_KP_MINUS){
            position -= direction * speed;
        }
        if (e.key.keysym.sym == SDLK_KP_9){
            horizontalAngle += speed;
        }
        if (e.key.keysym.sym == SDLK_KP_7){
            horizontalAngle -= speed;
        }
        if (e.key.keysym.sym == SDLK_KP_3){
            verticalAngle += speed;
        }
        if (e.key.keysym.sym == SDLK_KP_1){
            verticalAngle -= speed;
        }
        if (e.key.keysym.sym == SDLK_KP_5){
            position = glm::vec3(0,0,5);
            horizontalAngle = 3.14f;
            verticalAngle = 0.0f;
        }
    }

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
