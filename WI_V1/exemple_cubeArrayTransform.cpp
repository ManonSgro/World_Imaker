#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Geometry.hpp>
#include <glimac/Texture.hpp>
#include <glimac/CubeList.hpp>
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

    /** Create cube list **/
    CubeList myCubeList;
    myCubeList.addCube(Cube());
    myCubeList.addCube(Cube());
    myCubeList.addCube(Cube());
    myCubeList.setScale(2, 0.5,0.5,0.5);
    myCubeList.setScale(0, 1.0,1.0,1.0);
    myCubeList.setScale(1, 0.5,0.5,0.5);
    myCubeList.setRot(2, 45.0f, 1.0,0.0,0.0);
    myCubeList.setTrans(2, 0.0, 2.0, 1.0);
    myCubeList.setTrans(0, 0.0, 0.0, 0.0);
    myCubeList.setTrans(1, 0.0, 1.0,-1.0);
    


    /** Array of Textures **/
    uint nbOfTextures = 2;
    std::vector<Texture> textures(nbOfTextures);

     /** Loading shaders **/
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/cubeTexture.vs.glsl",
        applicationPath.dirPath() + "shaders/cubeTexture.fs.glsl"
    );
    program.use();

    //Obtention de l'id de la variable uniforme
    GLint uMVP = glGetUniformLocation(program.getGLId(), "uMVP");
    //GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    //GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    //GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    for(int i=0; i<textures.size(); i++){
        char const *pchar = "uTexture" + i;
        textures[i].setUniformLocation(program, (GLchar*)pchar);
    }

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




    /** Création VBO **/
    std::vector<GLuint> vboList(myCubeList.getSize());
    for(int i=0; i<myCubeList.getSize(); i++){
        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vboList[i]);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vboList[i]);

        // Send data to CG
        glBufferData(GL_ARRAY_BUFFER, myCubeList.getVertexCount(i)*sizeof(Vertex3DTexture), myCubeList.getDataPointer(i), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, vboList.back());
    }





    /** Loading textures **/
    textures[0].setImage("../GLImac-Template/assets/textures/brique.png");
    textures[1].setImage("../GLImac-Template/assets/textures/herbe.png");
    // Link cubes with textures
    myCubeList.setTextureIndex(0, 0);
    myCubeList.setTextureIndex(1, 1);
    myCubeList.setTextureIndex(2, 1);


    /** Textures **/
    for(uint i = 0; i<textures.size(); i++){
        glGenTextures(1,textures[i].getTexturePointer());
        glBindTexture(GL_TEXTURE_2D,textures[i].getTexture());   //Texture binding

        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,textures[i].getImageWidth(),textures[i].getImageHeight(),0,GL_RGBA,GL_FLOAT,textures[i].getImagePixels());

        //Filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    // Stop modifying bindTexture
    glBindTexture(GL_TEXTURE_2D,0);


    /** VAO creation **/
    //VAO attributes index
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_TEXTURE = 1;

    std::vector<GLuint> vaoList(myCubeList.getSize());
    for(int i=0; i<myCubeList.getSize(); i++){
        glGenVertexArrays(1, &vaoList[i]);
        // VAO Binding
        glBindVertexArray(vaoList[i]);

        glBindBuffer(GL_ARRAY_BUFFER, vboList[i]);

        // 1st attribute buffer : position
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
        // 2nd attribute buffer : texture
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

    }


     /** IBO creation **/
     std::vector<GLuint> iboList(myCubeList.getSize());
     for(int i=0; i<myCubeList.getSize(); i++){
        glGenBuffers(1, &iboList[i]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, myCubeList.getIBOCount(i)*sizeof(uint32_t), myCubeList.getIBOPointer(i), GL_STATIC_DRAW);
     }

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



    /** Print cube **/
    myCubeList.printCubes();
    /** Sort cubes **/
    myCubeList.sortCubes();
    /** Print cubes **/
    myCubeList.printCubes();


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

        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        /*glm::mat4 Mrotate = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * ViewMatrix)); //Model View Projection
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix * Mrotate));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));*/


        /** Draw cube list **/
        int currentTexture = myCubeList.getTextureIndex(0);
        // Active first texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[myCubeList.getTextureIndex(0)].getTexture()); // la texture est bindée sur l'unité GL_TEXTURE0
        glUniform1i(textures[myCubeList.getTextureIndex(0)].getUniformLocation(), 0);
        // Active first MVP
        Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
        Model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f,0.0f,0.0f));
        Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
        glm::mat4 mvp = Projection * View * Model;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        for(int i=0; i<myCubeList.getSize(); i++){
            if(currentTexture != myCubeList.getTextureIndex(i)){
                currentTexture = myCubeList.getTextureIndex(i);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textures[myCubeList.getTextureIndex(i)].getTexture()); // la texture est bindée sur l'unité GL_TEXTURE0
                glUniform1i(textures[myCubeList.getTextureIndex(i)].getUniformLocation(), 0);
            }

            glBindVertexArray(vaoList[myCubeList.getCubeIndex(i)]);


            // Transform
            Model = glm::scale(glm::mat4(1.0f), myCubeList.getScale(myCubeList.getCubeIndex(i)));
            //Model = glm::translate(Model, myCubeList.getTrans(myCubeList.getCubeIndex(i)));
            Model = glm::rotate(Model, myCubeList.getRotDeg(myCubeList.getCubeIndex(i)), myCubeList.getRot(myCubeList.getCubeIndex(i)));
            Model = glm::translate(Model, myCubeList.getTrans(myCubeList.getCubeIndex(i)));
            // Our ModelViewProjection : multiplication of our 3 matrices
            glm::mat4 mvp = Projection * View * Model;
            // Send our transformation to the currently bound shader, in the "MVP" uniform
            // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

            // Draw cube
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[myCubeList.getCubeIndex(i)]);
            glDrawElements(GL_TRIANGLES, myCubeList.getIBOCount(i), GL_UNSIGNED_INT, (void *)0);
        }


        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Update the display
        windowManager.swapBuffers();
    }

return EXIT_SUCCESS;
}
