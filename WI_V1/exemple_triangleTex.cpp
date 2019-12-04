#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <cstddef>

using namespace glimac;

struct Vertex2DUV
{
    glm::vec2 position;
    glm::vec2 texture;

    Vertex2DUV(){}
    Vertex2DUV(glm::vec2 position, glm::vec2 texture):position(position), texture(texture){}
};

glm::mat3 translate(float tx, float ty)
{
    glm::mat3 M = glm::mat3(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(tx, ty, 1));
    return M;
}
glm::mat3 scale(float sx, float sy)
{
    glm::mat3 M = glm::mat3(glm::vec3(sx, 0, 0), glm::vec3(0, sy, 0), glm::vec3(0, 0, 1));
    return M;
}
glm::mat3 rotate(float a)
{
    float ar;
    ar = glm::radians(a);
    glm::mat3 M = glm::mat3(glm::vec3(cos(ar), sin(ar), 0), glm::vec3(-sin(ar), cos(ar), 0), glm::vec3(0, 0, 1));
    return M;
}

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

    //Chargement des textures
    std::unique_ptr<Image> img = loadImage("../GLImac-Template/assets/textures/brique.png");
    if (img == NULL)
    {
        std::cout << "PROBLEM chargement texture" << std::endl;
    }
    else
    {
        std::cout << "OK chargement texture" << std::endl;
    }


    //Chargement des shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
        applicationPath.dirPath() + "shaders/tex2D.fs.glsl"
    );
    program.use();

    //Obtention de l'id de la variable uniforme
    GLint uModelMatrix = glGetUniformLocation(program.getGLId(), "uModelMatrix");
    GLint uColor = glGetUniformLocation(program.getGLId(), "uColor");

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
     GLuint textures;
     glGenTextures(1, &textures);
     glBindTexture(GL_TEXTURE_2D, textures);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_FLOAT, img->getPixels());
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     /*
    glGenTextures(1,&textureEarth);
    glBindTexture(GL_TEXTURE_2D,textureEarth);   //Binding de la texture
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,EarthMap->getWidth(),EarthMap->getHeight(),0,GL_RGBA,GL_FLOAT,EarthMap->getPixels());*/

    //Création d'un VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    //Bindind du vbo sur la cible
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Création d'un tableau de float pour stocker les points du VBO
    //On utilise la structure nouvellement créée
    Vertex2DUV vertices[] = {
        Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 1)),
        Vertex2DUV(glm::vec2(1, -1), glm::vec2(1, 1)),
        Vertex2DUV(glm::vec2(0, 1), glm::vec2(0.5, 0))
    };
    //Puis on envois les données à la CG
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);

    //Débindind du vbo de la cible pour éviter de le remodifier
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //Débindind de la texture
    glBindTexture(GL_TEXTURE_2D, 0);


    //Création du VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);

    //Binding du vao (un seul à la fois)
    glBindVertexArray(vao);

    //Dire à OpenGL qu'on utilise le VAO
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    //Indiquer à OpenGL où trouver les sommets
    //Bindind du vbo sur la cible
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //Spécification du format de l'attribut de sommet position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, texture));
    //Débindind du vbo de la cible pour éviter de le remodifier
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Débindind du vao de la cible pour éviter de le remodifier
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

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        //On nettoit la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);

        //On rebind le vao
        glBindVertexArray(vao);

        //On envoie un matrice
        /*glm::mat3 MRotate = rotate(windowManager.getTime()*10);
        glUniformMatrix3fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(MRotate));*/

        //On dessine le triangle
        glm::vec3 Color0 = glm::vec3(1, 1, 1);
        glm::vec3 Color1 = glm::vec3(0, 0, 1);
        glm::vec3 Color2 = glm::vec3(1, 0, 0);
        glm::vec3 Color3 = glm::vec3(0, 1, 0);

        glm::mat3 MRotateGlobal = rotate(windowManager.getTime()*50);
        glm::mat3 MRotate = rotate(windowManager.getTime()*100);
        glm::mat3 MRotateInv = rotate(-windowManager.getTime()*100);
        glm::mat3 MScale = scale(0.5, 0.5);


        glm::mat3 MTranslate0 = translate(1, 1);
        glUniform3fv(uColor, 1, glm::value_ptr(Color0));
        glUniformMatrix3fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(MRotateGlobal * MScale * MTranslate0 * MRotate));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glm::mat3 MTranslate1 = translate(1, -1);
        glUniform3fv(uColor, 1, glm::value_ptr(Color1));
        glUniformMatrix3fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(MRotateGlobal * MScale * MTranslate1 * MRotateInv));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glm::mat3 MTranslate2 = translate(-1, 1);
        glUniform3fv(uColor, 1, glm::value_ptr(Color2));
        glUniformMatrix3fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(MRotateGlobal * MScale * MTranslate2 * MRotateInv));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glm::mat3 MTranslate3 = translate(-1, -1);
        glUniform3fv(uColor, 1, glm::value_ptr(Color3));
        glUniformMatrix3fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(MRotateGlobal * MScale * MTranslate3 * MRotate));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Débindind du vao de la cible pour éviter de le remodifier
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    //On libère le GPU des ressources VBO et VAO
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &textures);


    return EXIT_SUCCESS;
}
