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

    myCubeList.addOrigin(); //origin
        std::cout << "Size ! " << myCubeList.getSize() << std::endl;
    myCubeList.setTrans(0, 0, 0, 0);
    myCubeList.setTextureIndex(0, 0);

    /*myCubeList.addCube(Cube());
    myCubeList.setScale(2, 0.5,0.5,0.5);
    myCubeList.setScale(0, 1.0,1.0,1.0);
    //myCubeList.setScale(1, 0.5,0.5,0.5);
    /*myCubeList.setRot(2, 45.0f, 1.0,0.0,0.0);*/
    /*myCubeList.setTrans(3, 0.0, 2.0, 1.0);
    myCubeList.setTrans(1, 0, 0, 0);
    myCubeList.setTrans(2, 0.0, 1.0,-1.0);*/

    Eigen::MatrixXd points(3,3);
    points << 0,-40,5,
              -10,-40,0,
              10,-40,0;
    for(int i=0; i<points.rows(); i++){
        myCubeList.addCube(Cube());
        std::cout << "Size ! " << myCubeList.getSize() << std::endl;
        myCubeList.setTrans(i+1, points(i,0), points(i,2), points(i,1));
        myCubeList.setTextureIndex(i+1, 0);

    }
    for(int i=0; i<19; i++){
        int x = -9+i;
        int y = -40;
        std::cout << "X et Y : " << x << "-" << y << std::endl;
        int newPoint = myCubeList.interpolatePoints(x,y,points);
        std::cout << "Z : " << newPoint << std::endl;
        myCubeList.addCube(Cube());
        myCubeList.setTrans(myCubeList.getSize()-1, x, newPoint, y);
        myCubeList.setTextureIndex(myCubeList.getSize()-1, 1);
    }
    
    



    /** Array of Textures **/
    uint nbOfTextures = 2;
    std::vector<Texture> textures(nbOfTextures);

     /** Loading shaders **/
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/cubeLight.vs.glsl",
        applicationPath.dirPath() + "shaders/cubeGeneralLight.fs.glsl"
    );
    program.use();

    
    //Obtention de l'id de la variable uniforme
    GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    //Obtiention des variables uniformes pour la lumière
    GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
    GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
    GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
    GLint uLightPos_vs = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
    GLint uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
    GLint uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");
    

    for(int i=0; i<textures.size(); i++){
        char const *pchar = "uTexture" + i;
        textures[i].setUniformLocation(program, (GLchar*)pchar);
    }

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

  

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
    //myCubeList.setTextureIndex(0, 0);
    //myCubeList.setTextureIndex(1, 1);
    //myCubeList.setTextureIndex(2, 1);


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
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;

    std::vector<GLuint> vaoList(myCubeList.getSize());
    for(int i=0; i<myCubeList.getSize(); i++){
        glGenVertexArrays(1, &vaoList[i]);
        // VAO Binding
        glBindVertexArray(vaoList[i]);

        glBindBuffer(GL_ARRAY_BUFFER, vboList[i]);

        // 1st attribute buffer : position
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
        // 2nd attribute buffer : normal
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
        // 23rd attribute buffer : texture
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
    //myCubeList.printCubes();
    /** Sort cubes **/
    //myCubeList.sortCubes();
    /** Print cubes **/
    //myCubeList.printCubes();


    // Application loop:
    bool done = false;
    while(!done) {
        Controls c;
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            c.computeMatricesFromInputs(windowWidth,windowHeight,e);
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

         /*** CAMERA ***/
        c.computeMatricesFromInputs(windowWidth,windowHeight,e);
        const glm::mat4 ProjectionMatrix = c.getProjectionMatrix();
        const glm::mat4 ViewMatrix = c.getViewMatrix();

        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUniform3f(uKd, 0.6, 0.6, 0.6); //Couleur des boules
        glUniform3f(uKs, 0, 0.0, 0.0);
        glUniform1f(uShininess, 32.0);
        glm::vec4 LightPos = ViewMatrix * glm::vec4(1.0, 1.0, 1.0, 1);
        glUniform3f(uLightPos_vs, LightPos.x, LightPos.y, LightPos.z);
        glm::vec4 LightDir = ViewMatrix * glm::vec4(1.0, 1.0, 1.0, 1);
        glUniform3f(uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        glUniform3f(uLightIntensity, 2.0, 2.0, 2.0);



        glm::mat4 ModelMatrix = glm::mat4();
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix * ModelMatrix));

        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix * ModelMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));




        /** Draw cube list **/
        int currentTexture = myCubeList.getTextureIndex(0);
        // Active first texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[myCubeList.getTextureIndex(0)].getTexture()); // la texture est bindée sur l'unité GL_TEXTURE0
        glUniform1i(textures[myCubeList.getTextureIndex(0)].getUniformLocation(), 0);
        // Active first MVP
        ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
        ModelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f,0.0f,0.0f));
        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection
        

        for(int i=0; i<myCubeList.getSize(); i++){
            if(currentTexture != myCubeList.getTextureIndex(i)){
                currentTexture = myCubeList.getTextureIndex(i);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textures[myCubeList.getTextureIndex(i)].getTexture()); // la texture est bindée sur l'unité GL_TEXTURE0
                glUniform1i(textures[myCubeList.getTextureIndex(i)].getUniformLocation(), 0);
            }

            glBindVertexArray(vaoList[myCubeList.getCubeIndex(i)]);


            // Transform
            ModelMatrix = glm::scale(glm::mat4(1.0f), myCubeList.getScale(myCubeList.getCubeIndex(i)));
            //Model = glm::translate(Model, myCubeList.getTrans(myCubeList.getCubeIndex(i)));
            ModelMatrix = glm::rotate(ModelMatrix, myCubeList.getRotDeg(myCubeList.getCubeIndex(i)), myCubeList.getRot(myCubeList.getCubeIndex(i)));
            ModelMatrix = glm::translate(ModelMatrix, myCubeList.getTrans(myCubeList.getCubeIndex(i)));
            // Our ModelViewProjection : multiplication of our 3 matrices
            glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection

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
