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

float speed = 0.0005f; // 3 units / second
float mouseSpeed = 0.005f;


void Controls::computeMatricesFromInputs(float wW, float wH, SDL_Event e){
    int posX = e.button.x;
    int posY = e.button.y;
    static double lastTime = SDL_GetTicks();
    double currentTime = SDL_GetTicks();
    float deltaTime = float(currentTime - lastTime);

   // Compute new orientation
	//horizontalAngle += mouseSpeed * deltaTime  * float(wW - posX );
	//verticalAngle   += mouseSpeed * deltaTime  * float(wH - posY );


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
        if (e.key.keysym.sym == SDLK_UP){
            position += up * speed;
        }
        if (e.key.keysym.sym == SDLK_DOWN){
            position -= up * speed;
        }
        if (e.key.keysym.sym == SDLK_RIGHT){
            position += right * speed;
        }
        if (e.key.keysym.sym == SDLK_LEFT){
            position -= right * speed;
        }
        if (e.key.keysym.sym == SDLK_KP_PLUS){
            position += direction * speed;
        }
        if (e.key.keysym.sym == SDLK_KP_MINUS){
            position -= direction * speed;
        }
        if (e.key.keysym.sym == SDLK_m){
            horizontalAngle += speed;
            position *= glm::vec3(-sinf(cos(verticalAngle) * sin(horizontalAngle)*(M_PI/180)) * cosf((sin(verticalAngle))*(M_PI/180)),
                                    -sinf((sin(verticalAngle))*(M_PI/180)),
                                    cosf((cos(verticalAngle) * sin(horizontalAngle))*(M_PI/180)) * cosf((sin(verticalAngle))*(M_PI/180)));
        }
        if (e.key.keysym.sym == SDLK_n){
            horizontalAngle -= speed;
        }
        if (e.key.keysym.sym == SDLK_o){
            verticalAngle += speed;
        }
        if (e.key.keysym.sym == SDLK_p){
            verticalAngle -= speed;
        }
        if (e.key.keysym.sym == SDLK_a){
            position = glm::vec3(0,0,5);
            horizontalAngle = 3.14f;
            verticalAngle = 0.0f;
        }
    }


    float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    this->ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

    this->ViewMatrix = glm::lookAt(
        position,           // Camera is here
        position+direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

    return;
}

Controls::Controls(){}

}
