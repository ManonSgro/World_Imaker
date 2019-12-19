#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Geometry.hpp>
#include <glimac/Controls.hpp>
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

glm::mat3 translate(float tx, float ty){
    glm::mat3 M = glm::mat3(glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(tx, ty, 1));
    return M;
}
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
    Cube MyCube2;
    Cube MyCube3;
    MyCube3.translateVertices(0.0,2.0,-2.0);
    MyCube.translateVertices(0.0,0.0,-2.0);
    MyCube2.translateVertices(0.0,0.0,0.0);

     /** Loading shaders **/
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/cubeLight.vs.glsl",
        applicationPath.dirPath() + "shaders/cubeLight.fs.glsl"
    );
    program.use();

    //Obtention de l'id de la variable uniforme
    GLint uMVP = glGetUniformLocation(program.getGLId(), "uMVP");
    GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint uTexture = glGetUniformLocation(program.getGLId(), "uTextureSampler");
    GLint uTextureGrass = glGetUniformLocation(program.getGLId(), "uTextureGrass");

    /*** Initialisation lumieres ***/
     //Obtiention des variables uniformes pour la lumière
    GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
    GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
    GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
    GLint uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
    GLint uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


    /** Création VBO **/
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);


    // Envoyer les données à la CG
    glBufferData(GL_ARRAY_BUFFER, MyCube.getVertexCount()*sizeof(Vertex3DTexture), MyCube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    /** VBO Cube 2 **/
    // This will identify our vertex buffer
    GLuint vertexbuffer2;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer2);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);

    glBufferData(GL_ARRAY_BUFFER, MyCube2.getVertexCount()*sizeof(Vertex3DTexture), MyCube2.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);

    /** VBO Cube 3 **/
    // This will identify our vertex buffer
    GLuint vertexbuffer3;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer3);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);

    glBufferData(GL_ARRAY_BUFFER, MyCube3.getVertexCount()*sizeof(Vertex3DTexture), MyCube3.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);





    /** Loading textures **/
    std::unique_ptr<Image> EarthMap=loadImage("../GLImac-Template/assets/textures/brique.png");
    std::unique_ptr<Image> GrassMap=loadImage("../GLImac-Template/assets/textures/herbe.png");
    if(EarthMap == NULL || GrassMap == NULL){
        std::cerr << "Une des textures n'a pas pu etre chargée. \n" << std::endl;
        exit(0);
    }

    /** Textures **/
    GLuint textureEarth, textureGrass;
    //Attribute texture
    glGenTextures(1,&textureEarth);
    glBindTexture(GL_TEXTURE_2D,textureEarth);   //Binding de la texture
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,EarthMap->getWidth(),EarthMap->getHeight(),0,GL_RGBA,GL_FLOAT,EarthMap->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    glGenTextures(1,&textureGrass);
    glBindTexture(GL_TEXTURE_2D,textureGrass);   //Binding de la texture
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,GrassMap->getWidth(),GrassMap->getHeight(),0,GL_RGBA,GL_FLOAT,GrassMap->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

    /** VAO Cube 2 **/
    GLuint vao2;
    glGenVertexArrays(1, &vao2);
    //Binding du vao (un seul à la fois)
    glBindVertexArray(vao2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);

    // Où se trouve les sommets
    // 1st attribute buffer : position
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
    // 2nd attribute buffer : texture
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

    /** VAO Cube 3 **/
    GLuint vao3;
    glGenVertexArrays(1, &vao3);
    //Binding du vao (un seul à la fois)
    glBindVertexArray(vao3);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);

    // Où se trouve les sommets
    // 1st attribute buffer : position
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
    // 2nd attribute buffer : texture
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));


     /** Création IBO **/
    //std::vector<uint32_t> indices = MyCube.getIndexBufferObject();
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MyCube.getIBOCount()*sizeof(uint32_t), MyCube.getIBOPointer(), GL_STATIC_DRAW);

    /** IBO Cube 2 **/
    GLuint ibo2;
    glGenBuffers(1, &ibo2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MyCube2.getIBOCount()*sizeof(uint32_t), MyCube2.getIBOPointer(), GL_STATIC_DRAW);

    /** IBO Cube 3 **/
    GLuint ibo3;
    glGenBuffers(1, &ibo3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MyCube3.getIBOCount()*sizeof(uint32_t), MyCube3.getIBOPointer(), GL_STATIC_DRAW);


    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);






    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        Controls c;
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            c.computeMatricesFromInputs(windowWidth,windowHeight);
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        // Nettoyage de la fenêtre
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glUniform1i(uTexture, 0); //sampler, texCoords
        //glUniform1i(uTextureGrass, 1);
        glBindVertexArray(vao);

        /*** CAMERA ***/
        c.computeMatricesFromInputs(windowWidth,windowHeight);
        glm::mat4 ProjectionMatrix = c.getProjectionMatrix();
        glm::mat4 ViewMatrix = c.getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        GLuint MatrixID = glGetUniformLocation(program.getGLId(), "uMVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


        /*** Lumieres ***/
        glUniform3f(uKd, 0.1, 0.2, 0.3); //Couleur des boules
        glUniform3f(uKs, 0.5, 0.0, 0.0);
        glUniform1f(uShininess, 32.0);
        glm::vec4 LightDir = c.getViewMatrix() * glm::vec4(1.0, 1.0, 1.0, 0.0);
        glUniform3f(uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        glUniform3f(uLightIntensity, 2.0, 2.0, 2.0);

        /*** Textures ***/
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureEarth); // la texture earthTexture est bindée sur l'unité GL_TEXTURE0
        glUniform1i(uTexture, 0);
        // Draw first cube
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, MyCube.getIBOCount(), GL_UNSIGNED_INT, (void *)0);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureGrass); // la texture grassTexture est bindée sur l'unité GL_TEXTURE1
        glUniform1i(uTextureGrass, 0);
        // Draw second cube
        glBindVertexArray(vao2);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
        glDrawElements(GL_TRIANGLES, MyCube2.getIBOCount(), GL_UNSIGNED_INT, (void *)0);

        // Draw third cube
        glBindVertexArray(vao3);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
        glDrawElements(GL_TRIANGLES, MyCube3.getIBOCount(), GL_UNSIGNED_INT, (void *)0);



        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Update the display
        windowManager.swapBuffers();
    }

return EXIT_SUCCESS;
}
