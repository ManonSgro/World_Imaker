#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Geometry.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <cstddef>
#include <vector>

using namespace glimac;

struct EarthProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uAddTexture;

    EarthProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3DFreeFly.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3DFreeFly.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        uAddTexture = glGetUniformLocation(m_Program.getGLId(), "uAddTexture");
    }
};

struct MoonProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    MoonProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3DFreeFly.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3DFreeFly.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

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

    std::unique_ptr<Image> pImage = loadImage("../GLImac-Template/assets/textures/EarthMap.jpg");
    if (pImage == NULL) std::cout << "PROBLEM chargement texture Terre" << std::endl;
    GLuint texTerre;
    glGenTextures(1,&texTerre);
    glBindTexture(GL_TEXTURE_2D,texTerre);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pImage->getWidth() ,pImage->getHeight(),0,GL_RGBA,GL_FLOAT,pImage->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D,0);

       //Chargement des textures
    pImage = loadImage("../GLImac-Template/assets/textures/MoonMap.jpg");
    if (pImage == NULL) std::cout << "PROBLEM chargement texture Lune" << std::endl;

    GLuint texLune;
    glGenTextures(1,&texLune);
    glBindTexture(GL_TEXTURE_2D,texLune);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pImage->getWidth() ,pImage->getHeight(),0,GL_RGBA,GL_FLOAT,pImage->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D,0);

       //Chargement des textures
    pImage = loadImage("../GLImac-Template/assets/textures/CloudMap.jpg");
    if (pImage == NULL) std::cout << "PROBLEM chargement texture Lune" << std::endl;

    GLuint texCloud;
    glGenTextures(1,&texCloud);
    glBindTexture(GL_TEXTURE_2D,texCloud);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pImage->getWidth() ,pImage->getHeight(),0,GL_RGBA,GL_FLOAT,pImage->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D,0);


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    Sphere sphere(1, 64, 32);

    //Chargement des shaders
    FilePath applicationPath(argv[0]);
    EarthProgram earthProgram(applicationPath);
    MoonProgram moonProgram(applicationPath);

    //TrackBallCamera myCamera;
    FreeFlyCamera myCamera;

    glEnable(GL_DEPTH_TEST);

    //Création d'un VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    //Bindind du vbo sur la cible
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Puis on envois les données à la CG
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);

    //Débindind du vbo de la cible pour éviter de le remodifier
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Création du VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);

    //Binding du vao (un seul à la fois)
    glBindVertexArray(vao);

    //Dire à OpenGL qu'on utilise le VAO
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    //Indiquer à OpenGL où trouver les sommets
    //Bindind du vbo sur la cible
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //Spécification du format de l'attribut de sommet position
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords));
    //Débindind du vbo de la cible pour éviter de le remodifier
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Débindind du vao de la cible pour éviter de le remodifier
    glBindVertexArray(0);



    std::vector<glm::vec3> AxesRotation;
    std::vector<glm::vec3> Translations;
    for (int i = 0; i < 32; ++i)
    {
        AxesRotation.push_back(glm::sphericalRand(1.0f));
        Translations.push_back(glm::sphericalRand(2.0f));
    }



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

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);


    if(windowManager.isKeyPressed(SDLK_s)) myCamera.moveFront(-0.1);
    if(windowManager.isKeyPressed(SDLK_z)) myCamera.moveFront(0.1);
    if(windowManager.isKeyPressed(SDLK_q)) myCamera.moveLeft(0.1);
    if(windowManager.isKeyPressed(SDLK_d)) myCamera.moveLeft(-0.1);
    if(windowManager.isKeyPressed(SDLK_i)) myCamera.rotateLeft(5.0);
    if(windowManager.isKeyPressed(SDLK_k)) myCamera.rotateUp(5.0);

    glm::ivec2 mousePos = glm::ivec2(0.0);
    if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
        mousePos = windowManager.getMousePosition();
        float mousePosX = mousePos.x/800.0f - 0.5;
        float mousePosY = mousePos.y/600.0f - 0.5;

        myCamera.rotateLeft(-2*mousePosX);
        myCamera.rotateUp(-2*mousePosY);

    }

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);

    earthProgram.m_Program.use();

    glUniform1i(earthProgram.uTexture, 0);
    glUniform1i(earthProgram.uAddTexture, 1);

    glm::mat4 globalMVMatrix = myCamera.getViewMatrix();

    glm::mat4 earthMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE,
        glm::value_ptr(earthMVMatrix));
    glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE,
        glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
    glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE,
        glm::value_ptr(ProjMatrix * earthMVMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texTerre);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texCloud);

    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    moonProgram.m_Program.use();
    glUniform1i(earthProgram.uTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texLune);

    for (int i = 0; i < AxesRotation.size(); ++i)
    {
        glm::mat4 MVMatrix2 = myCamera.getViewMatrix();
        glm::mat4 NormalMatrix2 = glm::transpose(glm::inverse(MVMatrix2));
        MVMatrix2 = glm::rotate(MVMatrix2, windowManager.getTime(), AxesRotation.at(i)); // Translation * Rotation
        MVMatrix2 = glm::translate(MVMatrix2, Translations.at(i)); // Translation * Rotation * Translation
        MVMatrix2 = glm::scale(MVMatrix2, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale
        glUniformMatrix4fv(moonProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix2));
        glUniformMatrix4fv(moonProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix2));
        glUniformMatrix4fv(moonProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix2));
        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
    }
     glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
    // Update the display
    windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
