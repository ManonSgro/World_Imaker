#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <cstddef>

using namespace glimac;
using namespace glm;

struct Vertex2DUV{
    glm::vec2 position;
    glm::vec2 texture;

    Vertex2DUV(){
        position=glm::vec2(0.0);
        texture=glm::vec2(0.0);
    };

    Vertex2DUV(glm::vec2 p,glm::vec2 t){
        position=p;
        texture=t;
    };
};

glm::mat3 translate(float tx, float ty){
    glm::mat3 M = glm::mat3(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(tx, ty, 1));
    return M;
}
glm::mat3 scale(float sx, float sy){
    glm::mat3 M = glm::mat3(glm::vec3(sx, 0, 0), glm::vec3(0, sy, 0), glm::vec3(0, 0, 1));
    return M;
}

glm::mat3 rotate(float a){
    glm::mat3 M = glm::mat3(glm::vec3(cos(a), sin(a), 0), glm::vec3(-sin(a), cos(a), 0), glm::vec3(0, 0, 1));
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


    //Chargement des shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/tex2Dtexture.vs.glsl",
        applicationPath.dirPath() + "shaders/tex2Dtexture.fs.glsl"
    );
    program.use();

    //Obtention de l'id de la variable uniforme
    GLint uTimeLocation = glGetUniformLocation(program.getGLId(), "uModelMatrix");
     GLint uColorLocation = glGetUniformLocation(program.getGLId(), "uColor");
    GLint uTexture = glGetUniformLocation(program.getGLId(), "uTexture");

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    // glGenTextures(1, &textures);
    // glBindTexture(GL_TEXTURE_2D, textures);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image::getWidth(), Image::getHeight(), 0, GL_RGBA, GL_FLOAT, 1);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Création d'un VBO
    GLuint vbo;
     glGenBuffers(1, &vbo);

     //Création d'une texture
      std::unique_ptr<Image> texture_brique=loadImage("/Users/PierreCharles/Documents/IMAC/IMAC2/Synthèse d'image/TD_MacOS/GLImac-Template/assets/textures/brique.png");
      std::unique_ptr<Image> texture_herbe=loadImage("/Users/PierreCharles/Documents/IMAC/IMAC2/Synthèse d'image/TD_MacOS/GLImac-Template/assets/textures/herbe.png");
      std::unique_ptr<Image> texture_toit=loadImage("/Users/PierreCharles/Documents/IMAC/IMAC2/Synthèse d'image/TD_MacOS/GLImac-Template/assets/textures/toit.jpg");
      std::unique_ptr<Image> texture_ciel=loadImage("/Users/PierreCharles/Documents/IMAC/IMAC2/Synthèse d'image/TD_MacOS/GLImac-Template/assets/textures/ciel.jpg");

     if(texture_brique == NULL || texture_herbe == NULL || texture_toit == NULL || texture_ciel == NULL){
            std::cerr << "Une des textures n'a pas pu etre chargée. \n" << std::endl;
            exit(0);
     }

     GLuint texture;
     glGenTextures(1,&texture);


     //  Binding d'un VBO sur la cible GL_ARRAY_BUFFER:
     glBindBuffer(GL_ARRAY_BUFFER, vbo);

     //Binding de la texture
     glBindTexture(GL_TEXTURE_2D,texture);


     // glBindTexture(GL_TEXTURE_2D,texture2);
     // glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->getWidth(),img2->getHeight(),0,GL_RGBA,GL_FLOAT,img2->getPixels());
     // //filtrage
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     //debindage de la texture
     glBindTexture(GL_TEXTURE_2D,0);
     // tableau avec coordonnées et envoi des données au buffer
    Vertex2DUV vertices[] = { Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 1)), // en bas a gauche MAISON
                              Vertex2DUV(glm::vec2(-1, 0.5), glm::vec2(0, 0)), // en haut a gauche MAISON
                              Vertex2DUV(glm::vec2(1, 0.5), glm::vec2(1, 0)),// en haut a droite MAISON
                              Vertex2DUV(glm::vec2(1, -1), glm::vec2(1, 1)), //en bas a droite MAISON
                              Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 1)), // en bas a gauche HERBE
                              Vertex2DUV(glm::vec2(-1, 0), glm::vec2(0, 0)), // en haut a gauche HERBE
                              Vertex2DUV(glm::vec2(1, 0), glm::vec2(1, 0)),// en haut a droite HERBE
                              Vertex2DUV(glm::vec2(1, -1), glm::vec2(1, 1)), //en bas a droite HERBE
                              Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 1)), // premier sommet TOIT
                              Vertex2DUV(glm::vec2(1, -1), glm::vec2(1, 1)), // deuxième sommet TOIT
                              Vertex2DUV(glm::vec2(0, 1), glm::vec2(0.5, 0)),// troisième sommet TOIT
                              Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 1)), // en bas a gauche CIEL
                              Vertex2DUV(glm::vec2(-1, 1), glm::vec2(0, 0)), // en haut a gauche CIEL
                              Vertex2DUV(glm::vec2(1, 1), glm::vec2(1, 0)),// en haut a droite CIEL
                              Vertex2DUV(glm::vec2(1, -1), glm::vec2(1, 1)), //en bas a droite CIEL
    };

    glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);

     // Débind du VBO et de sa cible
     glBindBuffer(GL_ARRAY_BUFFER, 0);

     // création du VAO
     GLuint vao;
     glGenVertexArrays(1, &vao);

     // Binding du VAO
     glBindVertexArray(vao);

     // Spécification des attributs
     const GLuint VERTEX_ATTR_POSITION = 0;
     const GLuint VERTEX_ATTR_TEXTURE = 1;

     glBindBuffer(GL_ARRAY_BUFFER, vbo);


     glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
     glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, position));

     glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
     glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV),  (const GLvoid*)offsetof(Vertex2DUV, texture));

     glBindBuffer(GL_ARRAY_BUFFER, 0);

     // Débind du VAO
     glBindVertexArray(0);
    float uTime = 0,b=0,bb=2;


    float rotate_utime = 0;
    float rotate_speed = 0.01;

    vec3 red(1,0,0);
    vec3 blue(0,0,1);
    vec3 green(0,1,0);
    vec3 yellow(1,1,0);


    // u loop:
    bool done = false;
    while(!done) {

        // u loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
         glm::mat3 M_scale_reset = scale(1, 1); //mise a l'echelle
         glm::mat3 M_scale = scale(0.25, 0.25); //Scale
         glm::mat3 M_translate = translate(0, 0.361f); //Translate
         glm::mat3 M_translate2 = translate(0, -0.2); //Translate
         glm::mat3 M_translate3 = translate(-0.5, 0.5); //Translate
         glm::mat3 M_translate4 = translate(0.5, -0.5); //Translate
         glm::mat3 M_rotate = rotate(0.25); //Rotate
         glm::mat3 M_rotate2 = rotate(-rotate_utime); //Rotate

         // Nettoyage de la fenêtre
         glClear(GL_COLOR_BUFFER_BIT);
         glBindTexture(GL_TEXTURE_2D, texture);
         glUniform1i(uTexture, 0);


         //CIEL
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,texture_ciel->getWidth(),texture_ciel->getHeight(),0,GL_RGBA,GL_FLOAT,texture_ciel->getPixels());
            glBindVertexArray(vao);
            glUniformMatrix3fv(uTimeLocation, 1, GL_FALSE, glm::value_ptr(M_scale_reset));
            glUniform3f(uColorLocation,green.r,green.g,green.b);
            glDrawArrays(GL_QUADS, 11, 4); //11 car indice de départ, et 4 car 4 coordonnées
            glBindVertexArray(0);

         //MAISON
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,texture_brique->getWidth(),texture_brique->getHeight(),0,GL_RGBA,GL_FLOAT,texture_brique->getPixels());
            glBindVertexArray(vao);
            glUniformMatrix3fv(uTimeLocation, 1, GL_FALSE, glm::value_ptr(M_scale));
            glUniform3f(uColorLocation,red.r,red.g,red.b);
            rotate_utime+=rotate_speed;
            glDrawArrays(GL_QUADS, 0, 4); //0 car indice de départ, et 4 car 4 coordonnées
            glBindVertexArray(0);


        //HERBE
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,texture_herbe->getWidth(),texture_herbe->getHeight(),0,GL_RGBA,GL_FLOAT,texture_herbe->getPixels());
            glBindVertexArray(vao);
            glUniformMatrix3fv(uTimeLocation, 1, GL_FALSE, glm::value_ptr(M_scale_reset * M_translate2));
            glUniform3f(uColorLocation,green.r,green.g,green.b);
            glDrawArrays(GL_QUADS, 4, 4); //4 car indice de départ, et 4 car 4 coordonnées
            glBindVertexArray(0);

        //TOIT
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,texture_toit->getWidth(),texture_toit->getHeight(),0,GL_RGBA,GL_FLOAT,texture_toit->getPixels());
            glBindVertexArray(vao);
            glUniformMatrix3fv(uTimeLocation, 1, GL_FALSE, glm::value_ptr(M_translate * M_scale));
            glUniform3f(uColorLocation,green.r,green.g,green.b);
            glDrawArrays(GL_TRIANGLES, 8, 3); //8 car indice de départ, et 3 car 3 coordonnées
            glBindVertexArray(0);


         glBindTexture(GL_TEXTURE_2D, 0);


        // Update the display
        windowManager.swapBuffers();
    }
    glDeleteTextures(1,&texture);
    return EXIT_SUCCESS;
}
