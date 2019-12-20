/**
 * \file main.cpp
 * \brief Programme principal - Editeur de scène 3D
 * \author Amélia MANSION - Manon SGRO'
 * \version 0.1
 * \date 20 décembre 2019
 *
 * Programme d'édition de scène 3D.
 *
 */

// Includes
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <glm/glm.hpp>

// Include GLImac
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Texture.hpp>
#include <glimac/CubeList.hpp>
#include <glimac/Controls.hpp>

// Include imGUI
#include <include/imgui.h>
#include <examples/imgui_impl_sdl.h>
#include <examples/imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

using namespace glm;

using namespace glimac;


int main(int argc, char** argv) {

    // Initialize SDL and open a window
    float windowWidth = 800.0f;
    float windowHeight = 800.0f;
    float menuWidth = 200.0f;
    SDLWindowManager windowManager(windowWidth+menuWidth, windowHeight+menuWidth, "World Imaker");
    //glewExperimental = GL_TRUE;

    // Initialize GLEW for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // Print some infos about OpenGl and GLEW
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /** INITIALIZE SCENE **/
    std::vector<GLuint> vboList(1);
    std::vector<GLuint> vaoList(1);
    std::vector<GLuint> iboList(1);
    // VAO attributes index
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;
    
    // Add 3 cubes
    CubeList myCubeList;
    myCubeList.addCube(Cube(), iboList, vaoList, vboList, VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXTURE);
    myCubeList.addCube(Cube(), iboList, vaoList, vboList, VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXTURE);
    myCubeList.addCube(Cube(), iboList, vaoList, vboList, VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXTURE);

    // Translate cubes
    myCubeList.setTrans(0, 0,0,0);
    myCubeList.setTrans(1, 1,0,0);
    myCubeList.setTrans(2, -1,0,0);

    // Link cubes with textures
    myCubeList.setTextureIndex(0, 1);
    myCubeList.setTextureIndex(1, 1);
    myCubeList.setTextureIndex(2, 1);

    // Initialize cursor (a very special cube)
    Cube cursor;
    cursor.setTrans(myCubeList.getTrans(0).x,myCubeList.getTrans(0).y,myCubeList.getTrans(0).z);
    cursor.setTextureIndex(0);

    /** INITIALIZE IMGUI */

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

     /** LOADING SHADERS **/
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/vertex.vs.glsl",
        applicationPath.dirPath() + "shaders/fragment.fs.glsl"
    );
    program.use();

    // Get uniform variable ID
    GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    
    //Get uniform variables for light
    GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
    GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
    GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
    GLint uLightPos_vs = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
    GLint uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
    GLint uLightIntensityP = glGetUniformLocation(program.getGLId(), "uLightIntensityP");
    GLint uLightIntensityD = glGetUniformLocation(program.getGLId(), "uLightIntensityD");
    
    /** INITIALIZE TEXTURES **/
    uint nbOfTextures = 10;
    std::vector<Texture> textures(nbOfTextures);

    for(int i=0; i<textures.size(); i++){
        char const *pchar = "uTexture" + i;
        textures[i].setUniformLocation(program, (GLchar*)pchar);
    }

    // Loading textures
    textures[0].setImage("../GLImac-Template/assets/textures/rouge.png");
    textures[1].setImage("../GLImac-Template/assets/textures/bois.png");
    textures[2].setImage("../GLImac-Template/assets/textures/brique.png");
    textures[3].setImage("../GLImac-Template/assets/textures/cailloux.png");
    textures[4].setImage("../GLImac-Template/assets/textures/eau.png");
    textures[5].setImage("../GLImac-Template/assets/textures/goudron.png");
    textures[6].setImage("../GLImac-Template/assets/textures/herbe.png");
    textures[7].setImage("../GLImac-Template/assets/textures/marbre.png");
    textures[8].setImage("../GLImac-Template/assets/textures/mosaique.png");
    textures[9].setImage("../GLImac-Template/assets/textures/sol_metalique.png");

    // Textures
    for(uint i = 0; i<textures.size(); i++){
        glGenTextures(1,textures[i].getTexturePointer());
        glBindTexture(GL_TEXTURE_2D,textures[i].getTexture());   // Texture binding
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,textures[i].getImageWidth(),textures[i].getImageHeight(),0,GL_RGBA,GL_FLOAT,textures[i].getImagePixels());

        //Filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    /** INITIALIZE VBOs **/
    // For the cursor
    // Generate one buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vboList[0]);
    // Bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, vboList[0]);
    // Send data to CG
    glBufferData(GL_ARRAY_BUFFER, cursor.getVertexCount()*sizeof(Vertex3DTexture), cursor.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboList.front());

    // Repeat for all cubes of the scene (i+1 because the cursor is 0)
    myCubeList.generateVBO(vboList);

    /** INITIALIZE VAOs **/

    // Generate a VAO
    glGenVertexArrays(1, &vaoList[0]);
    // VAO Binding
    glBindVertexArray(vaoList[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vboList[0]);
    // 1st attribute buffer : position
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
    // 2nd attribute buffer : normal
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
    // 3rd attribute buffer : texture
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

    //Repeat for all cubes of the scene (i+1 because the cursor is 0)
    myCubeList.generateVAO(vaoList, vboList, VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXTURE);

    /** INITIALIZE IBOs **/
    // Generate buffer
    glGenBuffers(1, &iboList[0]);
    // Bind IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[0]);
    // Send data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cursor.getIBOCountBorder()*sizeof(uint32_t), cursor.getIBOPointerBorder(), GL_STATIC_DRAW);

    //Repeat for all cubes of the scene (i+1 because the cursor is 0)
    myCubeList.generateIBO(iboList);

    // Stop binding
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /** SORT CUBES BY TEXTURE **/
    myCubeList.printCubes();
    myCubeList.sortCubes();
    myCubeList.printCubes();

    /** INITIALIZE LOOP **/
    bool done = false; // is looping

    int currentActive = -1; // current selected cube

    int item_LightP = 0; // Spotlight on/off
    int item_LightD = 0; // Directive light on/off

    // Directive light position
    int xLightD = 1;
    int yLightD = 1;
    int zLightD = 1;

    // Spotlight position
    int xLightP = 1;
    int yLightP = 1;
    int zLightP = 1;

    // Extrude/Dig state
    bool thereIsACubeAbove = false;
    bool thereIsACubeUnder = false;

    // Load/Save file
    std::string filePath;
    std::string loadFilePath;

    // Camera initialisation
    Controls c;
    c.calculateVectors();
    c.computeMatricesFromInputs();

    /** APPLICATION LOOP **/
    while(!done){
        bool addCube = false;
        bool deleteCube = false;

        // Event loop
        SDL_Event e;
        while(windowManager.pollEvent(e)){
            // Send event to ImGui
            ImGui_ImplSDL2_ProcessEvent(&e);           

            if(e.type == SDL_QUIT){
                done = true;
            }

            c.calculateVectors();   // Calculate the new vectors of the camera
            if(e.type == SDL_KEYDOWN){
                // Move the cursor
                if (e.key.keysym.sym == SDLK_a){
                    cursor.setTrans(cursor.getTrans().x - 1, cursor.getTrans().y, cursor.getTrans().z);
                }
                if (e.key.keysym.sym == SDLK_q){
                    cursor.setTrans(cursor.getTrans().x + 1, cursor.getTrans().y, cursor.getTrans().z);
                }
                if (e.key.keysym.sym == SDLK_z){
                    cursor.setTrans(cursor.getTrans().x, cursor.getTrans().y  - 1, cursor.getTrans().z);
                }
                if (e.key.keysym.sym == SDLK_s){
                    cursor.setTrans(cursor.getTrans().x, cursor.getTrans().y + 1, cursor.getTrans().z);
                }
                if (e.key.keysym.sym == SDLK_e){
                    cursor.setTrans(cursor.getTrans().x, cursor.getTrans().y, cursor.getTrans().z - 1);
                }
                if (e.key.keysym.sym == SDLK_d){
                    cursor.setTrans(cursor.getTrans().x, cursor.getTrans().y, cursor.getTrans().z + 1);
                }

                // Move the camera
                if (e.key.keysym.sym == SDLK_KP_8){
                    glm::vec3 newPos = c.getPosition() + (c.getUp() * c.getSpeed());
                    c.setPosition(newPos);
                }
                if (e.key.keysym.sym == SDLK_KP_2){
                    glm::vec3 newPos = c.getPosition() - (c.getUp() * c.getSpeed());
                    c.setPosition(newPos);
                }
                if (e.key.keysym.sym == SDLK_KP_6){
                    glm::vec3 newPos = c.getPosition() + (c.getRight() * c.getSpeed());
                    c.setPosition(newPos);
                }
                if (e.key.keysym.sym == SDLK_KP_4){
                    glm::vec3 newPos = c.getPosition() - (c.getRight() * c.getSpeed());
                    c.setPosition(newPos);
                }
                if (e.key.keysym.sym == SDLK_KP_PLUS){
                    glm::vec3 newPos = c.getPosition() + (c.getDirection() * c.getSpeed());
                    c.setPosition(newPos);
                }
                if (e.key.keysym.sym == SDLK_KP_MINUS){
                    glm::vec3 newPos = c.getPosition() - (c.getDirection() * c.getSpeed());
                    c.setPosition(newPos);
                }
                if (e.key.keysym.sym == SDLK_KP_9){
                    c.calculateVectors();
                    c.setHorizontalAngle(c.getHorizontalAngle() + c.getSpeed());
                    c.computeMatricesFromInputs();
                }
                if (e.key.keysym.sym == SDLK_KP_7){
                    c.setHorizontalAngle(c.getHorizontalAngle() - c.getSpeed());
                }
                if (e.key.keysym.sym == SDLK_KP_3){
                    c.setVerticalAngle(c.getVerticalAngle() + c.getSpeed());
                }
                if (e.key.keysym.sym == SDLK_KP_1){
                    c.setVerticalAngle(c.getVerticalAngle() - c.getSpeed());
                }
                if (e.key.keysym.sym == SDLK_KP_5){
                    c.setPosition(glm::vec3(0,0,5));
                    c.setHorizontalAngle(3.14f);
                    c.setVerticalAngle(0.0f);
                }
            }
            c.computeMatricesFromInputs();   // Calculate the new matrix for the camera
        }
                    
        // Feed inputs to Dear ImGui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(windowManager.window);
        ImGui::NewFrame();

        // Set up MVP from Camera
        const glm::mat4 ProjectionMatrix = c.getProjectionMatrix();
        const glm::mat4 ViewMatrix = c.getViewMatrix();

        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Render the GUI
        // Cursor menu
        ImGui::Begin("CURSOR settings", NULL, ImGuiWindowFlags_NoResize |  ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos(ImVec2(windowWidth,0), true);
        ImGui::SetWindowSize(ImVec2(menuWidth,windowHeight+menuWidth));

        ImGui::Text("Coordinates");
        ImGui::Text("X :");
        int xCursor = cursor.getTrans().x;
        ImGui::InputInt("x", &xCursor);
        ImGui::Text("Y :");
        int yCursor = cursor.getTrans().y;
        ImGui::InputInt("y", &yCursor);
        ImGui::Text("Z :");
        int zCursor = cursor.getTrans().z;
        ImGui::InputInt("z", &zCursor);
        
        // Directive light
        const char* itemsLight[] = { "On", "Off"};
        ImGui::Text("Lumiere directionnelle :");
        ImGui::Combo("D", &item_LightD, itemsLight, IM_ARRAYSIZE(itemsLight));
        ImGui::Text("Coordinates D");
        ImGui::InputInt("xD", &xLightD);
        ImGui::Text("Y :");
        ImGui::InputInt("yD", &yLightD);
        ImGui::Text("Z :");
        ImGui::InputInt("zD", &zLightD);

        // Spotlight
        ImGui::Text("Lumiere ponctuelle :");
        ImGui::Combo("P", &item_LightP, itemsLight, IM_ARRAYSIZE(itemsLight));
        ImGui::Text("Coordinates P");
        ImGui::InputInt("xP", &xLightP);
        ImGui::Text("Y :");
        ImGui::InputInt("yP", &yLightP);
        ImGui::Text("Z :");
        ImGui::InputInt("zP", &zLightP);

        ImGui::End();

        // File menu
        ImGui::Begin("FILE settings", NULL);
        
        // Save
        ImGui::Text("Save file :");
        ImGui::InputText("Save Path", &filePath);
        if(ImGui::Button("Save")){
            std::ofstream autoSauv;
            autoSauv.open (filePath);
            for(int i=0; i<myCubeList.getSize(); i++){
                autoSauv << std::to_string(myCubeList.getCubeIndex(i))+" "
                +std::to_string((int)myCubeList.getTrans(i).x)+" "
                +std::to_string((int)myCubeList.getTrans(i).y)+" "
                +std::to_string((int)myCubeList.getTrans(i).z)+" "
                +std::to_string(myCubeList.getTextureIndex(i))+" "+"\n";
            }
            autoSauv.close();
        }

        // Load
        ImGui::Text("Load file :");
        ImGui::InputText("Load Path", &loadFilePath);
        if(ImGui::Button("Load")){

            // Read file to load
            std::vector<int> file;
            int x;
            std::ifstream loadFile;
            loadFile.open(loadFilePath);
            if (!loadFile) {
                std::cout << "Unable to open file";
                exit(1); // terminate with error
            }
            while (loadFile >> x) {
                file.push_back(x);
            }
            loadFile.close();
            
            // Save current file
            std::ofstream autoSauv;
            autoSauv.open ("../sauv/autoSave.txt");
            for(int i=0; i<myCubeList.getSize(); i++){
                autoSauv << std::to_string(myCubeList.getCubeIndex(i))+" "
                +std::to_string((int)myCubeList.getTrans(i).x)+" "
                +std::to_string((int)myCubeList.getTrans(i).y)+" "
                +std::to_string((int)myCubeList.getTrans(i).z)+" "
                +std::to_string(myCubeList.getTextureIndex(i))+" "+"\n";
            }
            autoSauv.close();

            // Reset cube list
            std::cout << "Deleting ..." << myCubeList.getSize() << "...cubes" << std::endl;
            while(myCubeList.getSize()){
                int i = 0;
                myCubeList.deleteCube(i, iboList, vaoList, vboList);
                currentActive = -1;
            }
            
            // Load file
            std::cout << "Loading... " << file.size()/5 << "...cubes" << std::endl; 
            for(int i=0; i<file.size(); i+=5){
                myCubeList.addCube(Cube(), iboList, vaoList, vboList, VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXTURE);
                myCubeList.setTrans(file[i], file[i+1],file[i+2],file[i+3]);
                myCubeList.setTextureIndex(file[i], file[i+4]);
                if(myCubeList.getTrans(i).x==xCursor && myCubeList.getTrans(i).y==yCursor && myCubeList.getTrans(i).z==zCursor){
                    currentActive = myCubeList.getSize()-1;
                }
/*
                // VBO
                vboList.resize(vboList.size()+1);
                glGenBuffers(1, &vboList[vboList.size()-1]);
                glBindBuffer(GL_ARRAY_BUFFER, vboList[vboList.size()-1]);
                glBufferData(GL_ARRAY_BUFFER, myCubeList.getVertexCount(myCubeList.getSize()-1)*sizeof(Vertex3DTexture), myCubeList.getDataPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, vboList.back());

                //VAO
                vaoList.resize(vaoList.size()+1);
                glGenVertexArrays(1, &vaoList[vaoList.size()-1]);
                glBindVertexArray(vaoList[vaoList.size()-1]);
                glBindBuffer(GL_ARRAY_BUFFER, vboList[vaoList.size()-1]);
                glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
                glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
                glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
                glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
                glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
                glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

                //IBO
                iboList.resize(iboList.size()+1);
                glGenBuffers(1, &iboList[iboList.size()-1]);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[iboList.size()-1]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, myCubeList.getIBOCount(myCubeList.getSize()-1)*sizeof(uint32_t), myCubeList.getIBOPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);
            */
            }
        }

        ImGui::End();

        // Cube menu
        ImGui::Begin("CUBE settings", NULL);

        // Selected cube
        int selectedCube = currentActive;
        ImGui::Text("Selected cube :");
        ImGui::InputInt("index", &selectedCube);

        // Texture
        const char* itemsTextures[] = { "Bois", "Brique", "Cailloux", "Eau", "Goudron", "Herbe", "Marbre", "Mosaique", "Sol metalique"};
        int item_currentTexture = myCubeList.getTextureIndex(selectedCube)-1;
        ImGui::Text("Texture:");
        ImGui::Combo("Texture", &item_currentTexture, itemsTextures, IM_ARRAYSIZE(itemsTextures));
        
        // Add/Delete cube
        if(selectedCube == -1){
            addCube = ImGui::Button("Add cube");
        }else{
            deleteCube = ImGui::Button("Delete cube");
        }

        // Extrude/Dig cube
        ImGui::Text("Modify cube :");
        if(ImGui::Button("Extrude")){
            if(selectedCube!=-1 && !thereIsACubeAbove){
                yCursor++;
                myCubeList.addCube(Cube(), iboList, vaoList, vboList, VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXTURE);
                myCubeList.setTrans(myCubeList.getSize()-1, xCursor, yCursor, zCursor);
                myCubeList.setTextureIndex(myCubeList.getSize()-1, item_currentTexture+1);
                currentActive = myCubeList.getSize()-1;

/*
                // VBO
                vboList.resize(vboList.size()+1);
                glGenBuffers(1, &vboList[vboList.size()-1]);
                glBindBuffer(GL_ARRAY_BUFFER, vboList[vboList.size()-1]);
                glBufferData(GL_ARRAY_BUFFER, myCubeList.getVertexCount(myCubeList.getSize()-1)*sizeof(Vertex3DTexture), myCubeList.getDataPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, vboList.back());

                //VAO
                vaoList.resize(vaoList.size()+1);
                glGenVertexArrays(1, &vaoList[vaoList.size()-1]);
                glBindVertexArray(vaoList[vaoList.size()-1]);
                glBindBuffer(GL_ARRAY_BUFFER, vboList[vaoList.size()-1]);
                glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
                glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
                glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
                glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
                glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
                glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

                //IBO
                iboList.resize(iboList.size()+1);
                glGenBuffers(1, &iboList[iboList.size()-1]);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[iboList.size()-1]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, myCubeList.getIBOCount(myCubeList.getSize()-1)*sizeof(uint32_t), myCubeList.getIBOPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);*/

            }else{
                std::cout << "[ERROR] Cannot extrude a non-cube or cube with no space above!" << std::endl;
            }
        };
        if(ImGui::Button("Dig")){
            if(selectedCube!=-1 && thereIsACubeUnder && !thereIsACubeAbove){
                myCubeList.deleteCube(selectedCube, iboList, vaoList, vboList);
                yCursor--;
            }else{
                std::cout << "[ERROR] Cannot dig a non-cube or cube that is not above a column!" << std::endl;
            }
        };

        ImGui::End();

        // Reset texture index (from ImGui)
        myCubeList.setTextureIndex(selectedCube, item_currentTexture+1);

        // Add/Delete cube (from ImGui)
        if(addCube == true){
            myCubeList.addCube(Cube(), iboList, vaoList, vboList, VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXTURE);
            myCubeList.setTrans(myCubeList.getSize()-1, xCursor, yCursor, zCursor);
            myCubeList.setTextureIndex(myCubeList.getSize()-1, 1);
            currentActive = myCubeList.getSize()-1;

            // VBO
            /*vboList.resize(vboList.size()+1);
            glGenBuffers(1, &vboList[vboList.size()-1]);
            glBindBuffer(GL_ARRAY_BUFFER, vboList[vboList.size()-1]);
            glBufferData(GL_ARRAY_BUFFER, myCubeList.getVertexCount(myCubeList.getSize()-1)*sizeof(Vertex3DTexture), myCubeList.getDataPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, vboList.back());

            //VAO
            vaoList.resize(vaoList.size()+1);
            glGenVertexArrays(1, &vaoList[vaoList.size()-1]);
            glBindVertexArray(vaoList[vaoList.size()-1]);
            glBindBuffer(GL_ARRAY_BUFFER, vboList[vaoList.size()-1]);
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
            glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
            glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

            //IBO
            iboList.resize(iboList.size()+1);
            glGenBuffers(1, &iboList[iboList.size()-1]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[iboList.size()-1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, myCubeList.getIBOCount(myCubeList.getSize()-1)*sizeof(uint32_t), myCubeList.getIBOPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);
*/
        }else if(deleteCube == true){
            myCubeList.deleteCube(selectedCube, iboList, vaoList, vboList);
            currentActive = -1;
        }

        // Rendu lumière
        glUniform3f(uKd, 0.6, 0.6, 0.6);
        glUniform3f(uKs, 0, 0.0, 0.0);
        glUniform1f(uShininess, 32.0);
        glm::vec4 LightPos = ViewMatrix * glm::vec4((float) xLightP, (float) yLightP, (float) zLightP, 1);
        glUniform3f(uLightPos_vs, LightPos.x, LightPos.y, LightPos.z);
        glm::vec4 LightDir = ViewMatrix * glm::vec4((float) xLightD, (float) yLightD, (float) zLightD, 1);
        glUniform3f(uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        
        // On/Off lights
        if (item_LightD == 0){
            glUniform3f(uLightIntensityD, 2.0, 2.0, 2.0);   
        }
        else {
            glUniform3f(uLightIntensityD, 0.0, 0.0, 0.0);
        }
        if (item_LightP == 0){
            glUniform3f(uLightIntensityP, 2.0, 2.0, 2.0);   
        }
        else {
            glUniform3f(uLightIntensityP, 0.0, 0.0, 0.0);
        }

        // Cursor move
        cursor.setTrans(xCursor, yCursor, zCursor);

        // Reset MVP
        glm::mat4 ModelMatrix = glm::mat4(1.0f);
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix * ModelMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix * ModelMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        
        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        // Draw cube list

        // Active first texture
        int currentTexture = myCubeList.getTextureIndex(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[myCubeList.getTextureIndex(0)].getTexture()); // bind texture on GL_TEXTURE0
        glUniform1i(textures[myCubeList.getTextureIndex(0)].getUniformLocation(), 0);
        
        // Active first MVP
        ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
        ModelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f,0.0f,0.0f));
        ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix * ModelMatrix)); //Model View Projection
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix)); //Model View Projection

        // Reset variables
        currentActive = -1;
        thereIsACubeAbove = false;
        thereIsACubeUnder = false;

        // Loop on cubes
        for(int i=0; i<myCubeList.getSize(); i++){

            // Get current cube
            if ((myCubeList.getTrans(i).x == cursor.getTrans().x) && (myCubeList.getTrans(i).y == cursor.getTrans().y) && (myCubeList.getTrans(i).z == cursor.getTrans().z)){
                currentActive = myCubeList.getCubeIndex(i);
            }
            // Is there a cube above current ?
            if ((myCubeList.getTrans(i).x == cursor.getTrans().x) && (myCubeList.getTrans(i).y == cursor.getTrans().y+1) && (myCubeList.getTrans(i).z == cursor.getTrans().z)){
                thereIsACubeAbove = true;
            }
            // Is there a cube under current ?
            if ((myCubeList.getTrans(i).x == cursor.getTrans().x) && (myCubeList.getTrans(i).y == cursor.getTrans().y-1) && (myCubeList.getTrans(i).z == cursor.getTrans().z)){
                thereIsACubeUnder = true;
            }

            // Active another texture if needed
            if(currentTexture != myCubeList.getTextureIndex(i)){
                currentTexture = myCubeList.getTextureIndex(i);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textures[myCubeList.getTextureIndex(i)].getTexture());
                glUniform1i(textures[myCubeList.getTextureIndex(i)].getUniformLocation(), 0);
            }

            // Bind VAO
            glBindVertexArray(vaoList[myCubeList.getCubeIndex(i)+1]);

            // Transform
            ModelMatrix = glm::scale(glm::mat4(1.0f), myCubeList.getScale(myCubeList.getCubeIndex(i)));
            ModelMatrix = glm::rotate(ModelMatrix, myCubeList.getRotDeg(myCubeList.getCubeIndex(i)), myCubeList.getRot(myCubeList.getCubeIndex(i)));
            ModelMatrix = glm::translate(ModelMatrix, myCubeList.getTrans(myCubeList.getCubeIndex(i)));
            // Reset ModelViewProjection matrices
            glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection
            glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr( ViewMatrix * ModelMatrix)); //Model View Projection
            glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(ViewMatrix * ModelMatrix)))); //Model View Projection

            // Draw cube
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[myCubeList.getCubeIndex(i)+1]);
            glDrawElements(GL_TRIANGLES, myCubeList.getIBOCount(i), GL_UNSIGNED_INT, (void *)0);
        }
        
        // Disable depth for cursor
        glDisable(GL_DEPTH_TEST);

        // Repeat for drawing the cursor alone
        glBindVertexArray(vaoList[0]);

        glBindTexture(GL_TEXTURE_2D, textures[cursor.getTextureIndex()].getTexture()); // la texture est bindée sur l'unité GL_TEXTURE0
        glUniform1i(textures[cursor.getTextureIndex()].getUniformLocation(), 0);

        ModelMatrix = glm::scale(glm::mat4(1.0f), cursor.getScale());
        ModelMatrix = glm::rotate(ModelMatrix, cursor.getRotDeg(), cursor.getRot());
        ModelMatrix = glm::translate(ModelMatrix, cursor.getTrans());
        
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection

        // Draw cursor
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[0]);
        glLineWidth(5.0);
        glDrawElements(GL_LINES, cursor.getIBOCountBorder(), GL_UNSIGNED_INT, (void *)0);

        // Unbind
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update the display
        windowManager.swapBuffers();
    }

    // Destroy ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return EXIT_SUCCESS;
}
