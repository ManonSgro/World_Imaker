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
#include <stack>

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
//#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

// Include imGUI
#include <include/imgui.h>
#include <examples/imgui_impl_sdl.h>
#include <examples/imgui_impl_opengl3.h>

using namespace glm;

using namespace glimac;

float returnX(float pixels, float windowWidth){
    return (pixels*2.0/windowWidth)-1.0;
}
float returnY(float pixels, float windowHeight){
    return (pixels*2.0/windowHeight)-1.0;
}

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    float windowWidth = 800.0f;
    float windowHeight = 800.0f;
    float menuWidth = 200.0f;
    SDLWindowManager windowManager(windowWidth+menuWidth, windowHeight+menuWidth, "World Imaker");
    
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
    double vertices[8][3] = {
    { 1.0f, 1.0f, 1.0f}, //0
    { 1.0f, 1.0f,-1.0f}, //1
    { 1.0f,-1.0f,-1.0f}, //2
    {-1.0f,-1.0f,-1.0f}, //3
    {-1.0f,-1.0f, 1.0f}, //4
    {-1.0f, 1.0f, 1.0f}, //5
    {-1.0f, 1.0f,-1.0f}, //6
    { 1.0f,-1.0f, 1.0f}  //7
    };


    CubeList myCubeList;
    float size = 0.5;
    Cube cube(0.5);
    cube.setScale(2,2,2);
    cube.setTrans(1,-1,1);
    myCubeList.addCube(Cube(size));
    myCubeList.addCube(Cube(size));
    myCubeList.addCube(Cube(size));
    myCubeList.setTrans(0, 0.5,0.5,0.5);
    //myCubeList.setScale(0, 2,2,2);
    myCubeList.setTrans(1, 1,1,1);
    myCubeList.setTrans(2, 2,2,2);
    /*
    myCubeList.addCube(Cube(0.5));
    myCubeList.addCube(Cube(0.5));
    myCubeList.setScale(1, 0.5,0.5,0.5);
    myCubeList.setScale(0, 1.0,1.0,1.0);
    myCubeList.setScale(1, 0.5,0.5,0.5);
    myCubeList.setRot(2, 45.0f, 1.0,0.0,0.0);
    myCubeList.setTrans(2, 0.0, 2.0, 1.0);
    myCubeList.setTrans(0, 0.0, 0.0, 0.0);
    myCubeList.setTrans(1, 0.0, 1.0,-1.0);
    */



        /** ImGUI */

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

// Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Platform/Renderer bindings
    SDL_GLContext gl_context = SDL_GL_CreateContext(windowManager.window);
    SDL_GL_MakeCurrent(windowManager.window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    ImGui_ImplSDL2_InitForOpenGL(windowManager.window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();








    /** Array of Textures **/
    uint nbOfTextures = 3;
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
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vboList[vboList.size()]);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vboList[vboList.size()]);
    // Send data to CG
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount()*sizeof(Vertex3DTexture), cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboList.back());



    /** Loading textures **/
    textures[0].setImage("../GLImac-Template/assets/textures/rouge.png");
    textures[1].setImage("../GLImac-Template/assets/textures/herbe.png");
    textures[2].setImage("../GLImac-Template/assets/textures/brique.png");
    // Link cubes with textures
    myCubeList.setTextureIndex(0, 1);
    myCubeList.setTextureIndex(1, 1);
    myCubeList.setTextureIndex(2, 1);
    cube.setTextureIndex(0);


    /** Textures **/
    for(uint i = 0; i<textures.size(); i++){
        glGenTextures(1,textures[i].getTexturePointer());
        glBindTexture(GL_TEXTURE_2D,textures[i].getTexture());   //Texture binding

        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,textures[i].getImageWidth(),textures[i].getImageHeight(),0,GL_RGBA,GL_FLOAT,textures[i].getImagePixels());

        //Filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }




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
    glGenVertexArrays(1, &vaoList[vaoList.size()]);
    // VAO Binding
    glBindVertexArray(vaoList[vaoList.size()]);
    glBindBuffer(GL_ARRAY_BUFFER, vboList[vaoList.size()]);
    // 1st attribute buffer : position
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
    // 2nd attribute buffer : normal
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
    // 23rd attribute buffer : texture
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));




     /** IBO creation **/
     std::vector<GLuint> iboList(myCubeList.getSize());
     for(int i=0; i<myCubeList.getSize(); i++){
        glGenBuffers(1, &iboList[i]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, myCubeList.getIBOCount(i)*sizeof(uint32_t), myCubeList.getIBOPointer(i), GL_STATIC_DRAW);
     }
     glGenBuffers(1, &iboList[iboList.size()]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[iboList.size()]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.getIBOCountBorder()*sizeof(uint32_t), cube.getIBOPointerBorder(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);




    /** Print cube **/
    myCubeList.printCubes();
    /** Sort cubes **/
    //myCubeList.sortCubes();
    /** Print cubes **/
    myCubeList.printCubes();


    // Application loop:
    bool done = false;
    int elemeSelect = 0;
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

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(windowManager.window);
        ImGui::NewFrame();

         /*** CAMERA ***/
        c.computeMatricesFromInputs(windowWidth,windowHeight,e);
        const glm::mat4 ProjectionMatrix = c.getProjectionMatrix();
        const glm::mat4 ViewMatrix = c.getViewMatrix();

        //std::cout << returnX(e.button.x,windowWidth+menuWidth) << std::endl;
        // Mouse cursor 
        if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
            std::stack<int> pile;
            float posX = returnX(e.button.x,windowWidth+menuWidth);
            float posY =  -returnY(e.button.y,windowHeight+menuWidth);

            
            for(int i(0); i<myCubeList.getSize(); ++i) {
                glm::vec4 clipSpacePos = ProjectionMatrix * (ViewMatrix * vec4(myCubeList.getTrans(i), 1.0));
                std::cout << "clipSpacePos " << clipSpacePos << std::endl;
                glm::vec3 ndcSpacePos(clipSpacePos);
                ndcSpacePos[0] = clipSpacePos[0]/clipSpacePos[3];
                ndcSpacePos[1] = clipSpacePos[1]/clipSpacePos[3];
                ndcSpacePos[2] = clipSpacePos[2]/clipSpacePos[3];

                
                if ((posX < (ndcSpacePos[0]+(size/2)) && posX > (ndcSpacePos[0]-(size/2))) && (posY < (ndcSpacePos[1]+(size/2)) && posY > (ndcSpacePos[1]-(size/2)))) {
                    //std::cout << "oui pour les X et Y pour element " << myCubeList.getCubeIndex(i) << std::endl;
                    elemeSelect = myCubeList.getCubeIndex(i);
                    pile.push(myCubeList.getCubeIndex(i));
                    std::cout << "elements : " << pile.size() << std::endl;
                }
                else {
                    //std::cout << "null obj cursor" << std::endl;
                }
            }

            /*
                int z = 1000;
                while (pile.empty() == false){
                    int current = pile.top();
                    clipSpacePos = ProjectionMatrix * (ViewMatrix * vec4(myCubeList.getTrans(current), 1.0));
                    glm::vec3 ndcSpacePos(clipSpacePos);
                    ndcSpacePos[0] = clipSpacePos[0]/clipSpacePos[3];
                    ndcSpacePos[1] = clipSpacePos[1]/clipSpacePos[3];
                    ndcSpacePos[2] = clipSpacePos[2]/clipSpacePos[3];
                    if (ndcSpacePos[2] < z){
                        z = ndcSpacePos[2];
                        elemeSelect = myCubeList.getCubeIndex(current);
                    }
                }
                */


        }

        std::cout << "elemeSelect " << elemeSelect << std::endl;



        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Render the GUI
        ImGui::Begin("Cube settings", NULL, ImGuiWindowFlags_NoResize |  ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos(ImVec2(windowWidth,0), true);
        ImGui::SetWindowSize(ImVec2(menuWidth,windowHeight+menuWidth));
        static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
        ImGui::ColorEdit3("color", color);
        ImGui::End();


        // Rendu
        glUniform3f(uKd, 0.6, 0.6, 0.6); //Couleur des boules
        glUniform3f(uKs, 0, 0.0, 0.0);
        glUniform1f(uShininess, 32.0);
        //glm::vec4 LightPos = ViewMatrix * glm::vec4(1.0, 1.0, 1.0, 1);
        //glUniform3f(uLightPos_vs, LightPos.x, LightPos.y, LightPos.z);
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
        



        glBindVertexArray(vaoList[vaoList.size()]);

        glBindTexture(GL_TEXTURE_2D, textures[cube.getTextureIndex()].getTexture()); // la texture est bindée sur l'unité GL_TEXTURE0
        glUniform1i(textures[cube.getTextureIndex()].getUniformLocation(), 0);
        // Transform
        ModelMatrix = glm::scale(glm::mat4(1.0f), cube.getScale());
        //Model = glm::translate(Model, myCubeList.getTrans(myCubeList.getCubeIndex(i)));
        ModelMatrix = glm::rotate(ModelMatrix, cube.getRotDeg(), cube.getRot());
        ModelMatrix = glm::translate(ModelMatrix, cube.getTrans());
        // Our ModelViewProjection : multiplication of our 3 matrices
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection

        // Draw cube
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[iboList.size()]);
        glLineWidth(12.0);
        glDrawElements(GL_LINES, cube.getIBOCountBorder(), GL_UNSIGNED_INT, (void *)0);


        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);







        // ////// Draw cube select
        
        // glColor3f(0.5f, 0.0f, 1.0f); // (0.5, 0, 1) is half red and full blue, giving dark purple.
        // glBegin(GL_LINES);
        // glVertex3f(vertices[5][0],vertices[5][1],vertices[5][2]);
        // glVertex3f(vertices[4][0],vertices[4][1],vertices[4][2]);
        // //Top
        // glVertex3f(vertices[5][0],vertices[5][1],vertices[5][2]);
        // glVertex3f(vertices[0][0],vertices[0][1],vertices[0][2]);
        // //Bottom
        // glVertex3f(vertices[4][0],vertices[4][1],vertices[4][2]);
        // glVertex3f(vertices[7][0],vertices[7][1],vertices[7][2]);
        // //Right
        // glVertex3f(vertices[7][0],vertices[7][1],vertices[7][2]);
        // glVertex3f(vertices[0][0],vertices[0][1],vertices[0][2]);
        // //Middle Lines
        // //Top Left
        // glVertex3f(vertices[6][0],vertices[6][1],vertices[6][2]);
        // glVertex3f(vertices[5][0],vertices[5][1],vertices[5][2]);
        // //Top Right
        // glVertex3f(vertices[1][0],vertices[1][1],vertices[1][2]);
        // glVertex3f(vertices[0][0],vertices[0][1],vertices[0][2]);
        // //Bottom Left
        // glVertex3f(vertices[3][0],vertices[3][1],vertices[3][2]);
        // glVertex3f(vertices[4][0],vertices[4][1],vertices[4][2]);
        // //Bottom Right
        // glVertex3f(vertices[2][0],vertices[2][1],vertices[2][2]);
        // glVertex3f(vertices[7][0],vertices[7][1],vertices[7][2]);
        // //Back Lines
        // //Left
        // glVertex3f(vertices[6][0],vertices[6][1],vertices[6][2]);
        // glVertex3f(vertices[3][0],vertices[3][1],vertices[3][2]);
        // //Top
        // glVertex3f(vertices[6][0],vertices[6][1],vertices[6][2]);
        // glVertex3f(vertices[1][0],vertices[1][1],vertices[1][2]);
        // //Bottom
        // glVertex3f(vertices[3][0],vertices[3][1],vertices[3][2]);
        // glVertex3f(vertices[2][0],vertices[2][1],vertices[2][2]);
        // //Right
        // glVertex3f(vertices[2][0],vertices[2][1],vertices[2][2]);
        // glVertex3f(vertices[1][0],vertices[1][1],vertices[1][2]);

        // glEnd();



        // Draw first cube
        // glBindVertexArray(vao);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, colorbuffer);
        // glDrawElements(GL_TRIANGLES, cube.getIBOCount(), GL_UNSIGNED_INT, (void *)0);







        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update the display
        windowManager.swapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

return EXIT_SUCCESS;
}
