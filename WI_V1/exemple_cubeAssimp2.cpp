
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Geometry.hpp>
#include <glimac/Controls.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Texture.hpp>
#include <glimac/3D/shader.h>
#include <glimac/3D/model.h>
#include <cstddef>
#include <vector>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

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

    /**********************************/
    /********* INITIALISATION *********/
    /**********************************/

    /** Apel de la classe **/
    std::vector<Cube> cubeList;
    cubeList.push_back(Cube(1));
    cubeList.push_back(Cube(0.5));
    cubeList.push_back(Cube(0.5));
    cubeList[1].translateVertices(0.0,2.0,-2.0);
    cubeList[0].translateVertices(0.0,0.0,-2.0);
    cubeList[2].translateVertices(0.0,0.0,0.0);


    /** Array of Textures **/
    //uint nbOfTextures = 2;
    //std::vector<Texture> textures(nbOfTextures);

    //Chargement des shaders
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
/*
    for(int i=0; i<textures.size(); i++){
        char const *pchar = "uTexture" + i;
        textures[i].setUniformLocation(program, (GLchar*)pchar);
    }
*/
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


    /** Création VBO **/
    std::vector<GLuint> vboList(cubeList.size());
    for(int i=0; i<cubeList.size(); i++){
        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vboList[i]);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vboList[i]);

        // Send data to CG
        glBufferData(GL_ARRAY_BUFFER, cubeList[i].getVertexCount()*sizeof(Vertex3DTexture), cubeList[i].getDataPointer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, vboList.back());
    }


    /** Loading textures **/
    /*
    textures[0].setImage("../GLImac-Template/assets/textures/brique.png");
    textures[1].setImage("../GLImac-Template/assets/textures/herbe.png");
    // Link cubes with textures
    cubeList[0].setTextureIndex(0);
    cubeList[1].setTextureIndex(1);
    cubeList[2].setTextureIndex(1);

*/
    /** Textures **/
    /*
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
*/
    /** VAO creation **/
    //VAO attributes index
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;

    std::vector<GLuint> vaoList(cubeList.size());
    for(int i=0; i<cubeList.size(); i++){
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
     std::vector<GLuint> iboList(cubeList.size());
     for(int i=0; i<cubeList.size(); i++){
        glGenBuffers(1, &iboList[i]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeList[i].getIBOCount()*sizeof(uint32_t), cubeList[i].getIBOPointer(), GL_STATIC_DRAW);
     }

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    /**********************************/
    /******* BOUCLE D'AFFICHAGE *******/
    /**********************************/


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


        /*** CAMERA ***/
        Controls c;
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
        /*
        for(int i=0; i<cubeList.size(); i++){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[cubeList[i].getTextureIndex()].getTexture()); // la texture est bindée sur l'unité GL_TEXTURE0
            glUniform1i(textures[cubeList[i].getTextureIndex()].getUniformLocation(), 0);

            glBindVertexArray(vaoList[i]);

            // Draw cube
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[i]);
            glDrawElements(GL_TRIANGLES, cubeList[i].getIBOCount(), GL_UNSIGNED_INT, (void *)0);
        }

*/

        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
