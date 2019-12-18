#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Geometry.hpp>
#include <cstddef>
#include <vector>

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
//#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

using namespace glimac;

/*struct Vertex3DTexture{
    glm::vec3 position;
    glm::vec2 texture;

    Vertex3DTexture(){}
    Vertex3DTexture(glm::vec3 position, glm::vec2 texture):position(position), texture(texture){}
};*/

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    float windowWidth = 800.0f;
    float windowHeight = 800.0f;
    SDLWindowManager windowManager(windowWidth, windowHeight, "World Imaker");

    glewExperimental = GL_TRUE;

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /** Apel de la classe **/
    Cube MyCube;

     /** Loading shaders **/
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/cubeTexture.vs.glsl",
        applicationPath.dirPath() + "shaders/cubeTexture.fs.glsl"
    );
    program.use();

    //Obtention de l'id de la variable uniforme
    //GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    //GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    //GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint uTexture = glGetUniformLocation(program.getGLId(), "myTextureSampler");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    /** Matrices **/
    //Projection Matrix
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), windowWidth/windowHeight, 0.1f, 100.0f); //param perspective(float fovy, float aspect, float znear, float far)

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
    //glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
    //glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // Get a handle for our "MVP" uniform
    // Only during the initialisation
    GLuint MatrixID = glGetUniformLocation(program.getGLId(), "uMVP");

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);



    /** A supprimer/passer dans la classe **/
    /** Vertices **/
    /*std::vector<Vertex3DTexture> vertices = {
    //Face sol
        Vertex3DTexture(glm::vec3(-1, -1, -1), glm::vec2(0,0)), //0
        Vertex3DTexture(glm::vec3(1, -1, -1), glm::vec2(1,0)), //1
        Vertex3DTexture(glm::vec3(1, -1, 1), glm::vec2(1,1)), //2
        Vertex3DTexture(glm::vec3(-1, -1, 1), glm::vec2(0,1)), //3

        //Face devant
        Vertex3DTexture(glm::vec3(-1, 1, 1), glm::vec2(0,0)), //4
        Vertex3DTexture(glm::vec3(1, 1, 1), glm::vec2(1,0)), //5
        Vertex3DTexture(glm::vec3(1, -1, 1), glm::vec2(1,1)), //6
        Vertex3DTexture(glm::vec3(-1, -1, 1), glm::vec2(0,1)), //7

        //Face gauche
        Vertex3DTexture(glm::vec3(-1, 1, 1), glm::vec2(0,0)), //8
        Vertex3DTexture(glm::vec3(-1, 1, -1), glm::vec2(1,0)), //9
        Vertex3DTexture(glm::vec3(-1, -1, -1), glm::vec2(1,1)), //10
        Vertex3DTexture(glm::vec3(-1, -1, 1), glm::vec2(0,1)), //11

        //Face derrière
        Vertex3DTexture(glm::vec3(-1, 1, -1), glm::vec2(0,0)), //12
        Vertex3DTexture(glm::vec3(1, 1, -1), glm::vec2(1,0)), //13
        Vertex3DTexture(glm::vec3(1, -1, -1), glm::vec2(1,1)), //14
        Vertex3DTexture(glm::vec3(-1, -1, -1), glm::vec2(0,1)), //15

        //Face droite
        Vertex3DTexture(glm::vec3(1, 1, 1), glm::vec2(0,0)), //16
        Vertex3DTexture(glm::vec3(1, 1, -1), glm::vec2(1,0)), //17
        Vertex3DTexture(glm::vec3(1, -1, -1), glm::vec2(1,1)), //18
        Vertex3DTexture(glm::vec3(1, -1, 1), glm::vec2(0,1)), //19

        //Face haut
        Vertex3DTexture(glm::vec3(-1, 1, -1), glm::vec2(0,0)), //20
        Vertex3DTexture(glm::vec3(1, 1, -1), glm::vec2(1,0)), //21
        Vertex3DTexture(glm::vec3(1, 1, 1), glm::vec2(1,1)), //22
        Vertex3DTexture(glm::vec3(-1, 1, 1), glm::vec2(0,1)) //23
    };*/



    /** Création VBO **/
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    /** A modifier avec objet cube **/
    // Envoyer les données à la CG
    glBufferData(GL_ARRAY_BUFFER, MyCube.getVertexCount()*sizeof(Vertex3DTexture), MyCube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Envoyer les données à la CG
    /*glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex3DTexture), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);*/





    /** Loading textures **/
    std::unique_ptr<Image> EarthMap=loadImage("../GLImac-Template/assets/textures/brique.png");
    if(EarthMap == NULL){
        std::cerr << "Une des textures n'a pas pu etre chargée. \n" << std::endl;
        exit(0);
    }

    /** Textures **/
    GLuint textureEarth;
    //Attribute texture
    glGenTextures(1,&textureEarth);
    glBindTexture(GL_TEXTURE_2D,textureEarth);   //Binding de la texture
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,EarthMap->getWidth(),EarthMap->getHeight(),0,GL_RGBA,GL_FLOAT,EarthMap->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glBindTexture(GL_TEXTURE_2D,0);

    /** Création du VAO **/
    GLuint vao;
    glGenVertexArrays(1, &vao);
    //Binding du vao (un seul à la fois)
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    //Dire à OpenGL qu'on utilise le VAO
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_TEXTURE = 1;
    // Où se trouve les sommets
    // 1st attribute buffer : position
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
    // 2nd attribute buffer : texture
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));



    /** A modifier/passer dans la classe ? **/
     /*std::vector<uint32_t> indices = {
        0,1,3,0,3,2,  4,5,6,4,6,7,  8,9,10,8,10,11,  12,13,14,12,14,15,  16,17,18,16,18,19,  20,21,22,20,22,23
     };*/

     /** Création IBO **/
    /*GLuint ibo;
    glGenBuffers(1, &ibo);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);*/
     //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

     //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
     /** Deux points différents sur deux faces consécutives**/
    //std::vector<uint32_t> indices = MyCube.getIndexBufferObject();
     GLuint ibo;
    glGenBuffers(1, &ibo);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MyCube.getIBOCount()*sizeof(uint32_t), MyCube.getIBOPointer(), GL_STATIC_DRAW);


    glBindVertexArray(0);






    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        // Nettoyage de la fenêtre
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniform1i(uTexture, 0); //sampler, texCoords




        glBindVertexArray(vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureEarth); // la texture earthTexture est bindée sur l'unité GL_TEXTURE0

        // Draw the triangle !
        //glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        //glDrawArrays(GL_TRIANGLES, 0, indices.size()); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        /** A modifier pour objet Cube **/
        //glDrawArrays(GL_TRIANGLES, 0, MyCube.getVertexCount());
        glDrawElements(GL_TRIANGLES, MyCube.getIBOCount(), GL_UNSIGNED_INT, (void *)0);

        glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

return EXIT_SUCCESS;
}
