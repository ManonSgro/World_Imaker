
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Geometry.hpp>
#include <glimac/Controls.hpp>
#include <cstddef>
#include <vector>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 800, "GLImac");

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

    Sphere MySphere(1, 32, 16);

    //Chargement des shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/cubeLight.vs.glsl",
        applicationPath.dirPath() + "shaders/cubeLight.fs.glsl"
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
    GLint uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
    GLint uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");

    glEnable(GL_DEPTH_TEST); //permet d'activer le test de profondeur du GPU. Sans cet appel de fonction, certains triangles non visible viendraient recouvrir des triangles situés devant.

    //Création d'un VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    //Bindind du vbo sur la cible
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Puis on envois les données à la CG
    glBufferData(GL_ARRAY_BUFFER, MySphere.getVertexCount()*sizeof(ShapeVertex), MySphere.getDataPointer(), GL_STATIC_DRAW);

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

    TrackballCamera Camera;

/*
    uint nbLune = 32;
    TrackballCamera Camera;

    std::vector<glm::vec3> AxesRotation;
    std::vector<glm::vec3> AxesTranslation;


    for (int i = 0; i < nbLune; ++i)
    {
        AxesRotation.push_back(glm::sphericalRand(1.0f)); //Rempli Axes rotation comme une pile ou comme un tableau, on pourra l'utiliser AxesRotation[i]
        AxesTranslation.push_back(glm::sphericalRand(2.0f));
    }

*/
    /**********************************/
    /******* BOUCLE D'AFFICHAGE *******/
    /**********************************/


    // Application loop:
    bool done = false;
    while(!done) {

        glm::mat4 ViewMatrix = Camera.getViewMatrix();

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        /*** CAMERA ***/
        Controls c;
        float windowWidth = 800.0f;
        float windowHeight = 800.0f;
        c.computeMatricesFromInputs(windowWidth,windowHeight);
        glm::mat4 ProjectionMatrix = c.getProjectionMatrix();
        ViewMatrix = c.getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        GLuint MatrixID = glGetUniformLocation(program.getGLId(), "uMVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.0f), 800.0f/600.0f, 0.1f, 100.0f); //param perspective(float fovy, float aspect, float znear, float far)
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        // Nettoyage de la fenêtre
        glClearColor(0.0,0.0,0.0,0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
        /*
        glm::mat4 Mrotate = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        */
        glUniform3f(uKd, 0.1, 0.2, 0.3); //Couleur des boules
        glUniform3f(uKs, 2, 0.0, 0.0);
        glUniform1f(uShininess, 32.0);
        glm::vec4 LightDir = Camera.getViewMatrix() * glm::vec4(10.0, 10.0, 1.0, 0.2);
        glUniform3f(uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        glUniform3f(uLightIntensity, 5.0, 5.0, 5.0);

        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * ViewMatrix)); //Model View Projection
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
        NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glDrawArrays(GL_TRIANGLES, 0, MySphere.getVertexCount());


        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
