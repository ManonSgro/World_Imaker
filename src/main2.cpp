#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Texture.hpp>
#include <glimac/CubeList.hpp>
#include <glimac/Controls.hpp>
#include <glimac/objloader.hpp>
#include <glimac/text.hpp>
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
#include <misc/cpp/imgui_stdlib.h>

using namespace glm;

using namespace glimac;


int main(int argc, char** argv) {
//     // Initialize SDL and open a window
//     float windowWidth = 800.0f;
//     float windowHeight = 800.0f;
//     float menuWidth = 200.0f;
//     SDLWindowManager windowManager(windowWidth+menuWidth, windowHeight+menuWidth, "World Imaker");
    
//     glewExperimental = GL_TRUE;

//     // Initialize glew for OpenGL3+ support
//     GLenum glewInitError = glewInit();
//     if(GLEW_OK != glewInitError) {
//         std::cerr << glewGetErrorString(glewInitError) << std::endl;
//         return EXIT_FAILURE;
//     }

//     std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
//     std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

//     /** READ FILE **/
//     //int sum = 0;
//     /*
//     std::vector<int> file;
//     int x;
//     std::ifstream inFile;
    
//     inFile.open("../sauv/autoSave.txt");
//     if (!inFile) {
//         std::cout << "Unable to open file";
//         exit(1); // terminate with error
//     }
    
//     while (inFile >> x) {
//         file.push_back(x);
//     }
    
//     inFile.close();
//     std::cout << "Loading... " << file.size()/5 << "...cubes" << std::endl; 

//     CubeList myCubeList;
//     for(int i=0; i<file.size(); i+=5){
//         myCubeList.addCube(Cube());
//         myCubeList.setTrans(file[i], file[i+1],file[i+2],file[i+3]);
//         myCubeList.setTextureIndex(file[i], file[i+4]);
//     }
//     */
//     std::vector<GLuint> vboList(myCubeList.getSize()+1);
//     std::vector<GLuint> vaoList(myCubeList.getSize()+1);
//     std::vector<GLuint> iboList(myCubeList.getSize()+1);
//     CubeList myCubeList;
//     myCubeList.addCube(Cube(), iboList, vaoList, vboList);
//     myCubeList.addCube(Cube(), iboList, vaoList, vboList);
//     myCubeList.addCube(Cube(), iboList, vaoList, vboList);
//     myCubeList.setTrans(0, 0,0,0);
//     myCubeList.setTrans(1, 1,0,0);
//     myCubeList.setTrans(2, -1,0,0);

//     // Link cubes with textures
//     myCubeList.setTextureIndex(0, 1);
//     myCubeList.setTextureIndex(1, 1);
//     myCubeList.setTextureIndex(2, 1);

//     /** Initialize cursor **/
//     Cube cursor;
//     cursor.setTrans(myCubeList.getTrans(0).x,myCubeList.getTrans(0).y,myCubeList.getTrans(0).z);
//     cursor.setTextureIndex(0);



//         /** ImGUI */

//     // Decide GL+GLSL versions
// #if __APPLE__
//     // GL 3.2 Core + GLSL 150
//     const char* glsl_version = "#version 150";
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
// #else
//     // GL 3.0 + GLSL 130
//     const char* glsl_version = "#version 130";
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
// #endif

// // Initialize OpenGL loader
// #if defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//     bool err = glewInit() != GLEW_OK;
// #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//     bool err = gladLoadGL() == 0;
// #else
//     bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
// #endif
//     if (err)
//     {
//         fprintf(stderr, "Failed to initialize OpenGL loader!\n");
//         return 1;
//     }

//     // Setup Dear ImGui context
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO(); (void)io;

//     // Setup Platform/Renderer bindings
//     SDL_GLContext gl_context = SDL_GL_CreateContext(windowManager.window);
//     SDL_GL_MakeCurrent(windowManager.window, gl_context);
//     SDL_GL_SetSwapInterval(1); // Enable vsync
//     ImGui_ImplSDL2_InitForOpenGL(windowManager.window, gl_context);
//     ImGui_ImplOpenGL3_Init(glsl_version);


//     // Setup Dear ImGui style
//     ImGui::StyleColorsDark();


//     /** Array of Textures **/
//     uint nbOfTextures = 10;
//     std::vector<Texture> textures(nbOfTextures);

//      /** Loading shaders **/
//     FilePath applicationPath(argv[0]);
//     Program program = loadProgram(
//         applicationPath.dirPath() + "shaders/vertex.vs.glsl",
//         applicationPath.dirPath() + "shaders/fragment.fs.glsl"
//     );
//     program.use();

    
//     //Obtention de l'id de la variable uniforme
//     GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
//     GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
//     GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

//     //Obtiention des variables uniformes pour la lumière
//     GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
//     GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
//     GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
//     GLint uLightPos_vs = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
//     GLint uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
//     GLint uLightIntensityP = glGetUniformLocation(program.getGLId(), "uLightIntensityP");
//     GLint uLightIntensityD = glGetUniformLocation(program.getGLId(), "uLightIntensityD");
    

//     for(int i=0; i<textures.size(); i++){
//         char const *pchar = "uTexture" + i;
//         textures[i].setUniformLocation(program, (GLchar*)pchar);
//     }

   

  

//     /** Création VBO **/

//     // Generate 1 buffer, put the resulting identifier in vertexbuffer
//     glGenBuffers(1, &vboList[0]);
//     // The following commands will talk about our 'vertexbuffer' buffer
//     glBindBuffer(GL_ARRAY_BUFFER, vboList[0]);
//     // Send data to CG
//     glBufferData(GL_ARRAY_BUFFER, cursor.getVertexCount()*sizeof(Vertex3DTexture), cursor.getDataPointer(), GL_STATIC_DRAW);
//     glBindBuffer(GL_ARRAY_BUFFER, vboList.front());

//     for(int i=0; i<myCubeList.getSize(); i++){
//         // Generate 1 buffer, put the resulting identifier in vertexbuffer
//         glGenBuffers(1, &vboList[i+1]);
//         // The following commands will talk about our 'vertexbuffer' buffer
//         glBindBuffer(GL_ARRAY_BUFFER, vboList[i+1]);

//         // Send data to CG
//         glBufferData(GL_ARRAY_BUFFER, myCubeList.getVertexCount(i)*sizeof(Vertex3DTexture), myCubeList.getDataPointer(i), GL_STATIC_DRAW);
//         glBindBuffer(GL_ARRAY_BUFFER, vboList.back());
//     }



//     /** Loading textures **/
//     textures[0].setImage("../GLImac-Template/assets/textures/rouge.png");
//     textures[1].setImage("../GLImac-Template/assets/textures/bois.png");
//     textures[2].setImage("../GLImac-Template/assets/textures/brique.png");
//     textures[3].setImage("../GLImac-Template/assets/textures/cailloux.png");
//     textures[4].setImage("../GLImac-Template/assets/textures/eau.png");
//     textures[5].setImage("../GLImac-Template/assets/textures/goudron.png");
//     textures[6].setImage("../GLImac-Template/assets/textures/herbe.png");
//     textures[7].setImage("../GLImac-Template/assets/textures/marbre.png");
//     textures[8].setImage("../GLImac-Template/assets/textures/mosaique.png");
//     textures[9].setImage("../GLImac-Template/assets/textures/sol_metalique.png");
    
    


//     /** Textures **/
//     for(uint i = 0; i<textures.size(); i++){
//         glGenTextures(1,textures[i].getTexturePointer());
//         glBindTexture(GL_TEXTURE_2D,textures[i].getTexture());   //Texture binding

//         glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,textures[i].getImageWidth(),textures[i].getImageHeight(),0,GL_RGBA,GL_FLOAT,textures[i].getImagePixels());

//         //Filters
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     }




//     /** VAO creation **/
//     //VAO attributes index
//     const GLuint VERTEX_ATTR_POSITION = 0;
//     const GLuint VERTEX_ATTR_NORMAL = 1;
//     const GLuint VERTEX_ATTR_TEXTURE = 2;


//     glGenVertexArrays(1, &vaoList[0]);
//     // VAO Binding
//     glBindVertexArray(vaoList[0]);
//     glBindBuffer(GL_ARRAY_BUFFER, vboList[0]);
//     // 1st attribute buffer : position
//     glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
//     glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
//     // 2nd attribute buffer : normal
//     glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
//     glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
//     // 23rd attribute buffer : texture
//     glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
//     glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

//     for(int i=0; i<myCubeList.getSize(); i++){
//         glGenVertexArrays(1, &vaoList[i+1]);
//         // VAO Binding
//         glBindVertexArray(vaoList[i+1]);

//         glBindBuffer(GL_ARRAY_BUFFER, vboList[i+1]);

//         // 1st attribute buffer : position
//         glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
//         glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
//         // 2nd attribute buffer : normal
//         glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
//         glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
//         // 23rd attribute buffer : texture
//         glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
//         glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

//     }




//      /** IBO creation **/

//     glGenBuffers(1, &iboList[0]);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[0]);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, cursor.getIBOCountBorder()*sizeof(uint32_t), cursor.getIBOPointerBorder(), GL_STATIC_DRAW);

//      for(int i=0; i<myCubeList.getSize(); i++){
//         glGenBuffers(1, &iboList[i+1]);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[i+1]);
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER, myCubeList.getIBOCount(i)*sizeof(uint32_t), myCubeList.getIBOPointer(i), GL_STATIC_DRAW);
//      }


//     glBindVertexArray(0);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//     GLuint VertexArrayID;
// 	glGenVertexArrays(1, &VertexArrayID);
// 	glBindVertexArray(VertexArrayID);

// 	// Create and compile our GLSL program from the shaders
// 	//GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

// 	// Get a handle for our "MVP" uniform
// 	GLuint MatrixID = glGetUniformLocation(program.getGLId(), "MVP");
// 	GLuint ViewMatrixID = glGetUniformLocation(program.getGLId(), "V");
// 	GLuint ModelMatrixID = glGetUniformLocation(program.getGLId(), "M");

// 	// Load the texture
// 	GLuint Texture = loadDDS("../GLImac-Template/assets/models/uvmap.DDS");

// 	// Get a handle for our "myTextureSampler" uniform
// 	GLuint TextureID  = glGetUniformLocation(program.getGLId(), "myTextureSampler");

// 	// Read our .obj file
// 	std::vector<glm::vec3> vertices;
// 	std::vector<glm::vec2> uvs;
// 	std::vector<glm::vec3> normals;
// 	bool res = loadOBJ("../GLImac-Template/assets/models/suzanne.obj", vertices, uvs, normals);

// 	// Load it into a VBO

// 	GLuint vertexbuffer;
// 	glGenBuffers(1, &vertexbuffer);
// 	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// 	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

// 	GLuint uvbuffer;
// 	glGenBuffers(1, &uvbuffer);
// 	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
// 	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

// 	GLuint normalbuffer;
// 	glGenBuffers(1, &normalbuffer);
// 	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
// 	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

// 	// Get a handle for our "LightPosition" uniform
// 	//glUseProgram(programID);
//     GLuint LightID = glGetUniformLocation(program.getGLId(), "LightPosition_worldspace");


//     /** Print cube **/
//     myCubeList.printCubes();
//     /** Sort cubes **/
//     //myCubeList.sortCubes();
//     /** Print cubes **/
//     myCubeList.printCubes();


//     // Application loop:
//     bool done = false;
//     int currentActive = -1;

//     int item_LightP = 0;
//     int item_LightD = 0;
//     int item_Light3D = 1;

//     int xLightD = 1;
//     int yLightD = 1;
//     int zLightD = 1;

//     int xLightP = 1;
//     int yLightP = 1;
//     int zLightP = 1;

//     bool thereIsACubeAbove = false;
//     bool thereIsACubeUnder = false;
//     std::string filePath;
//     std::string loadFilePath;
//     Controls c;
//     c.calculateVectors();
//     c.computeMatricesFromInputs();
//     while(!done) {
//         bool addCube = false;
//         bool deleteCube = false;

//         // Event loop:
//         SDL_Event e;
//         while(windowManager.pollEvent(e)) {
//             // Send to ImGui
//             ImGui_ImplSDL2_ProcessEvent(&e);

//             // Avoid ImGui confilcts
//             /*
//             if (!ImGui::GetIO().WantCaptureKeyboard) {

// 				if (Input::KeyIsDown(CTRL)) {
// 					if (e.key.keysym.sym == 'z') {
// 						m_histories.getActiveHistory().moveBackward();
// 					}
// 					else if (e.key.keysym.sym == 'y') {
// 						m_histories.getActiveHistory().moveForward();
// 					}
// 					else if (e.key.keysym.sym == 's') {
// 						m_saveViewWindow.Open();
// 					}
// 				}
// 				else {
// 					if (e.key.keysym.scancode == SDL_SCANCODE_F5) {
// 						Locate::materialsManager().Shaders()[Locate::materialsManager().SelectedMaterial().shaderID].reloadShader();
// 						Locate::materialsManager().updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
// 						Locate::materialsManager().updateMatrixUniform("u_viewMat", m_camera.getViewMatrix());
// 					}
// 					if (e.key.keysym.sym == 'z') {
// 						m_cursor.setPosition(glm::ivec3(0, 1, 0) + m_cursor.getPosition());
// 					}
// 					else if (e.key.keysym.sym == 's') {
// 						m_cursor.setPosition(glm::ivec3(0, -1, 0) + m_cursor.getPosition());
// 					}
// 					else if (e.key.keysym.sym == 'q') {
// 						m_cursor.setPosition(glm::ivec3(1, 0, 0) + m_cursor.getPosition());
// 					}
// 					else if (e.key.keysym.sym == 'd') {
// 						m_cursor.setPosition(glm::ivec3(-1, 0, 0) + m_cursor.getPosition());
// 					}
// 					else if (e.key.keysym.sym == 'w') {
// 						m_cursor.setPosition(glm::ivec3(0, 0, 1) + m_cursor.getPosition());
// 					}
// 					else if (e.key.keysym.sym == 'x') {
// 						m_cursor.setPosition(glm::ivec3(0, 0, -1) + m_cursor.getPosition());
// 					}
// 				}
// 			}
// 			break;
//             */

//             if(e.type == SDL_QUIT) {
//                 done = true; // Leave the loop after this iteration
//             }

//             c.calculateVectors();
//             if(e.type == SDL_KEYDOWN) {
//                 if (e.key.keysym.sym == SDLK_a){
//                     cursor.setTrans(cursor.getTrans().x - 1, cursor.getTrans().y, cursor.getTrans().z);
//                 }
//                 if (e.key.keysym.sym == SDLK_q){
//                     cursor.setTrans(cursor.getTrans().x + 1, cursor.getTrans().y, cursor.getTrans().z);
//                 }
//                 if (e.key.keysym.sym == SDLK_z){
//                     cursor.setTrans(cursor.getTrans().x, cursor.getTrans().y  - 1, cursor.getTrans().z);
//                 }
//                 if (e.key.keysym.sym == SDLK_s){
//                     cursor.setTrans(cursor.getTrans().x, cursor.getTrans().y + 1, cursor.getTrans().z);
//                 }
//                 if (e.key.keysym.sym == SDLK_e){
//                     cursor.setTrans(cursor.getTrans().x, cursor.getTrans().y, cursor.getTrans().z - 1);
//                 }
//                 if (e.key.keysym.sym == SDLK_d){
//                     cursor.setTrans(cursor.getTrans().x, cursor.getTrans().y, cursor.getTrans().z + 1);
//                 }


//                 if (e.key.keysym.sym == SDLK_KP_8){
//                     glm::vec3 newPos = c.getPosition() + (c.getUp() * c.getSpeed());
//                     c.setPosition(newPos);
//                 }
//                 if (e.key.keysym.sym == SDLK_KP_2){
//                     glm::vec3 newPos = c.getPosition() - (c.getUp() * c.getSpeed());
//                     c.setPosition(newPos);
//                 }
//                 if (e.key.keysym.sym == SDLK_KP_6){
//                     glm::vec3 newPos = c.getPosition() + (c.getRight() * c.getSpeed());
//                     c.setPosition(newPos);
//                 }
//                 if (e.key.keysym.sym == SDLK_KP_4){
//                     glm::vec3 newPos = c.getPosition() - (c.getRight() * c.getSpeed());
//                     c.setPosition(newPos);
//                 }
//                 if (e.key.keysym.sym == SDLK_KP_PLUS){
//                     glm::vec3 newPos = c.getPosition() + (c.getDirection() * c.getSpeed());
//                     c.setPosition(newPos);
//                 }
//                 if (e.key.keysym.sym == SDLK_KP_MINUS){
//                     glm::vec3 newPos = c.getPosition() - (c.getDirection() * c.getSpeed());
//                     c.setPosition(newPos);
//                 }
//                 if (e.key.keysym.sym == SDLK_KP_9){
//                     c.calculateVectors();
//                     c.setHorizontalAngle(c.getHorizontalAngle() + c.getSpeed());
//                     c.computeMatricesFromInputs();
//                 }
//                 if (e.key.keysym.sym == SDLK_KP_7){
//                     c.setHorizontalAngle(c.getHorizontalAngle() - c.getSpeed());
//                 }
//                 if (e.key.keysym.sym == SDLK_KP_3){
//                     c.setVerticalAngle(c.getVerticalAngle() + c.getSpeed());
//                 }
//                 if (e.key.keysym.sym == SDLK_KP_1){
//                     c.setVerticalAngle(c.getVerticalAngle() - c.getSpeed());
//                 }
//                 if (e.key.keysym.sym == SDLK_KP_5){
//                     c.setPosition(glm::vec3(0,0,5));
//                     c.setHorizontalAngle(3.14f);
//                     c.setVerticalAngle(0.0f);
//                 }
//             }
//             c.computeMatricesFromInputs();

//         }
                    
//             // feed inputs to dear imgui, start new frame
//             ImGui_ImplOpenGL3_NewFrame();
//             ImGui_ImplSDL2_NewFrame(windowManager.window);
//             ImGui::NewFrame();

//             /*** CAMERA ***/
//             //c.calculateVectors();
//             //c.computeMatricesFromInputs(windowWidth,windowHeight);
//             const glm::mat4 ProjectionMatrix = c.getProjectionMatrix();
//             const glm::mat4 ViewMatrix = c.getViewMatrix();

//             // Clear window
//             glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//             // Render the GUI
//             ImGui::Begin("CURSOR settings", NULL, ImGuiWindowFlags_NoResize |  ImGuiWindowFlags_NoMove);
//             ImGui::SetWindowPos(ImVec2(windowWidth,0), true);
//             ImGui::SetWindowSize(ImVec2(menuWidth,windowHeight+menuWidth));
//             ImGui::Text("Coordinates");
//             ImGui::Text("X :");
//             int xCursor = cursor.getTrans().x;
//             ImGui::InputInt("x", &xCursor);
//             ImGui::Text("Y :");
//             int yCursor = cursor.getTrans().y;
//             ImGui::InputInt("y", &yCursor);
//             ImGui::Text("Z :");
//             int zCursor = cursor.getTrans().z;
//             ImGui::InputInt("z", &zCursor);



//             const char* itemsLight[] = { "On", "Off"};
//             ImGui::Text("Lumiere directionnelle :");
//             ImGui::Combo("D", &item_LightD, itemsLight, IM_ARRAYSIZE(itemsLight));

//             ImGui::Text("Coordinates D");
//             ImGui::InputInt("xD", &xLightD);
//             ImGui::Text("Y :");
//             ImGui::InputInt("yD", &yLightD);
//             ImGui::Text("Z :");
//             ImGui::InputInt("zD", &zLightD);


//             ImGui::Text("Lumiere ponctuelle :");
//             ImGui::Combo("P", &item_LightP, itemsLight, IM_ARRAYSIZE(itemsLight));

//             ImGui::Text("Coordinates P");
//             ImGui::InputInt("xP", &xLightP);
//             ImGui::Text("Y :");
//             ImGui::InputInt("yP", &yLightP);
//             ImGui::Text("Z :");
//             ImGui::InputInt("zP", &zLightP);


//             const char* items3d[] = { "On", "Off"};
//             ImGui::Text("Affichage 3D :");
//             ImGui::Combo("3D", &item_Light3D, items3d, IM_ARRAYSIZE(items3d));


//             ImGui::End();


//             ImGui::Begin("FILE settings", NULL);
            
//             ImGui::Text("Save file :");
//             ImGui::InputText("Save Path", &filePath);

//             if(ImGui::Button("Save")){
//                 std::ofstream autoSauv;
//                 autoSauv.open (filePath);
//                 for(int i=0; i<myCubeList.getSize(); i++){
//                     autoSauv << std::to_string(myCubeList.getCubeIndex(i))+" "
//                     +std::to_string((int)myCubeList.getTrans(i).x)+" "
//                     +std::to_string((int)myCubeList.getTrans(i).y)+" "
//                     +std::to_string((int)myCubeList.getTrans(i).z)+" "
//                     +std::to_string(myCubeList.getTextureIndex(i))+" "+"\n";
//                 }
//                 autoSauv.close();
//             }


//             ImGui::Text("Load file :");
//             ImGui::InputText("Load Path", &loadFilePath);
//             if(ImGui::Button("Load")){
//                 std::vector<int> file;
//                 int x;
//                 std::ifstream loadFile;
//                 loadFile.open(loadFilePath);
//                 if (!loadFile) {
//                     std::cout << "Unable to open file";
//                     exit(1); // terminate with error
//                 }
//                 while (loadFile >> x) {
//                     file.push_back(x);
//                     std::cout << " Loading file : " << x << std::endl;
//                 }
//                 loadFile.close();
                
//                 // Save current file
//                 std::ofstream autoSauv;
//                 autoSauv.open ("../sauv/autoSauv.txt");
//                 for(int i=0; i<myCubeList.getSize(); i++){
//                     autoSauv << std::to_string(myCubeList.getCubeIndex(i))+" "
//                     +std::to_string((int)myCubeList.getTrans(i).x)+" "
//                     +std::to_string((int)myCubeList.getTrans(i).y)+" "
//                     +std::to_string((int)myCubeList.getTrans(i).z)+" "
//                     +std::to_string(myCubeList.getTextureIndex(i))+" "+"\n";
//                 }
//                 autoSauv.close();

//                 // Reset cube list
//                 std::cout << "Deleting ..." << myCubeList.getSize() << "...cubes" << std::endl;
//                 while(myCubeList.getSize()){
//                     int i = 0;
//                     myCubeList.deleteCube(i, iboList, vaoList, vboList);
//                     currentActive = -1;

//                     // VBO
//                     if(i<=vboList.size()+1){
//                         glDeleteBuffers(1, &iboList[i+1]);
//                         iboList.erase(iboList.begin()+i+1);
//                         glDeleteVertexArrays(1, &vaoList[i+1]);
//                         vaoList.erase(vaoList.begin()+i+1);
//                         glDeleteBuffers(1, &vboList[i+1]);
//                         vboList.erase(vboList.begin()+i+1);
//                     }
//                 }
                

//                 // Load file
//                 std::cout << "Loading... " << file.size()/5 << "...cubes" << std::endl; 
//                 for(int i=0; i<file.size(); i+=5){
//                     myCubeList.addCube(Cube(), iboList, vaoList, vboList);
//                     myCubeList.setTrans(file[i], file[i+1],file[i+2],file[i+3]);
//                     myCubeList.setTextureIndex(file[i], file[i+4]);
//                     if(myCubeList.getTrans(i).x==xCursor && myCubeList.getTrans(i).y==yCursor && myCubeList.getTrans(i).z==zCursor){
//                         currentActive = myCubeList.getSize()-1;
//                     }

//                     // VBO
//                     vboList.resize(vboList.size()+1);
//                     glGenBuffers(1, &vboList[vboList.size()-1]);
//                     glBindBuffer(GL_ARRAY_BUFFER, vboList[vboList.size()-1]);
//                     glBufferData(GL_ARRAY_BUFFER, myCubeList.getVertexCount(myCubeList.getSize()-1)*sizeof(Vertex3DTexture), myCubeList.getDataPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);
//                     glBindBuffer(GL_ARRAY_BUFFER, vboList.back());

//                     //VAO
//                     vaoList.resize(vaoList.size()+1);
//                     glGenVertexArrays(1, &vaoList[vaoList.size()-1]);
//                     glBindVertexArray(vaoList[vaoList.size()-1]);
//                     glBindBuffer(GL_ARRAY_BUFFER, vboList[vaoList.size()-1]);
//                     glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
//                     glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
//                     glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
//                     glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
//                     glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
//                     glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

//                     //IBO
//                     iboList.resize(iboList.size()+1);
//                     glGenBuffers(1, &iboList[iboList.size()-1]);
//                     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[iboList.size()-1]);
//                     glBufferData(GL_ELEMENT_ARRAY_BUFFER, myCubeList.getIBOCount(myCubeList.getSize()-1)*sizeof(uint32_t), myCubeList.getIBOPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);
//                 }
                
//             }
//             ImGui::End();


//             ImGui::Begin("CUBE settings", NULL);
//             int selectedCube = currentActive;
//             ImGui::Text("Selected cube :");

//             ImGui::InputInt("text", &selectedCube);
//             const char* itemsTextures[] = { "Bois", "Brique", "Cailloux", "Eau", "Goudron", "Herbe", "Marbre", "Mosaique", "Sol metalique"};

//             int item_currentTexture = myCubeList.getTextureIndex(selectedCube)-1;
//             ImGui::Text("Texture:");
//             ImGui::Combo("Texture", &item_currentTexture, itemsTextures, IM_ARRAYSIZE(itemsTextures));
//             if(selectedCube == -1){
//                 addCube = ImGui::Button("Add cube");
//             }else{
//                 deleteCube = ImGui::Button("Delete cube");
//             }
//             ImGui::Text("Modify cube :");
//             if(ImGui::Button("Extrude")){
//                 if(selectedCube!=-1 && !thereIsACubeAbove){
//                     yCursor++;
//                     myCubeList.addCube(Cube(), iboList, vaoList, vboList);
//                     myCubeList.setTrans(myCubeList.getSize()-1, xCursor, yCursor, zCursor);
//                     myCubeList.setTextureIndex(myCubeList.getSize()-1, item_currentTexture+1);
//                     currentActive = myCubeList.getSize()-1;

//                     // VBO
//                     vboList.resize(vboList.size()+1);
//                     glGenBuffers(1, &vboList[vboList.size()-1]);
//                     glBindBuffer(GL_ARRAY_BUFFER, vboList[vboList.size()-1]);
//                     glBufferData(GL_ARRAY_BUFFER, myCubeList.getVertexCount(myCubeList.getSize()-1)*sizeof(Vertex3DTexture), myCubeList.getDataPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);
//                     glBindBuffer(GL_ARRAY_BUFFER, vboList.back());

//                     //VAO
//                     vaoList.resize(vaoList.size()+1);
//                     glGenVertexArrays(1, &vaoList[vaoList.size()-1]);
//                     glBindVertexArray(vaoList[vaoList.size()-1]);
//                     glBindBuffer(GL_ARRAY_BUFFER, vboList[vaoList.size()-1]);
//                     glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
//                     glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
//                     glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
//                     glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
//                     glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
//                     glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

//                     //IBO
//                     iboList.resize(iboList.size()+1);
//                     glGenBuffers(1, &iboList[iboList.size()-1]);
//                     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[iboList.size()-1]);
//                     glBufferData(GL_ELEMENT_ARRAY_BUFFER, myCubeList.getIBOCount(myCubeList.getSize()-1)*sizeof(uint32_t), myCubeList.getIBOPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);

//                 }else{
//                     std::cout << "[ERROR] Cannot extrude a non-cube or cube with no space above!" << std::endl;
//                 }
//             };
//             if(ImGui::Button("Dig")){
//                 if(selectedCube!=-1 && thereIsACubeUnder && !thereIsACubeAbove){
//                     myCubeList.deleteCube(selectedCube, iboList, vaoList, vboList);
//                     // VBO
//                     if(selectedCube<=vboList.size()+1){
//                         glDeleteBuffers(1, &iboList[selectedCube+1]);
//                         iboList.erase(iboList.begin()+selectedCube+1);
//                         glDeleteVertexArrays(1, &vaoList[selectedCube+1]);
//                         vaoList.erase(vaoList.begin()+selectedCube+1);
//                         glDeleteBuffers(1, &vboList[selectedCube+1]);
//                         vboList.erase(vboList.begin()+selectedCube+1);
//                     }
//                     yCursor--;
//                 }else{
//                     std::cout << "[ERROR] Cannot dig a non-cube or cube that is not above a column!" << std::endl;
//                 }
//             };
//             ImGui::End();
//             myCubeList.setTextureIndex(selectedCube, item_currentTexture+1);

//             if(addCube == true){
//                 myCubeList.addCube(Cube(), iboList, vaoList, vboList);
//                 myCubeList.setTrans(myCubeList.getSize()-1, xCursor, yCursor, zCursor);
//                 myCubeList.setTextureIndex(myCubeList.getSize()-1, 1);
//                 currentActive = myCubeList.getSize()-1;

//                 // VBO
//                 vboList.resize(vboList.size()+1);
//                 glGenBuffers(1, &vboList[vboList.size()-1]);
//                 glBindBuffer(GL_ARRAY_BUFFER, vboList[vboList.size()-1]);
//                 glBufferData(GL_ARRAY_BUFFER, myCubeList.getVertexCount(myCubeList.getSize()-1)*sizeof(Vertex3DTexture), myCubeList.getDataPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);
//                 glBindBuffer(GL_ARRAY_BUFFER, vboList.back());

//                 //VAO
//                 vaoList.resize(vaoList.size()+1);
//                 glGenVertexArrays(1, &vaoList[vaoList.size()-1]);
//                 glBindVertexArray(vaoList[vaoList.size()-1]);
//                 glBindBuffer(GL_ARRAY_BUFFER, vboList[vaoList.size()-1]);
//                 glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
//                 glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
//                 glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
//                 glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
//                 glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
//                 glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

//                 //IBO
//                 iboList.resize(iboList.size()+1);
//                 glGenBuffers(1, &iboList[iboList.size()-1]);
//                 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[iboList.size()-1]);
//                 glBufferData(GL_ELEMENT_ARRAY_BUFFER, myCubeList.getIBOCount(myCubeList.getSize()-1)*sizeof(uint32_t), myCubeList.getIBOPointer(myCubeList.getSize()-1), GL_STATIC_DRAW);

//             }else if(deleteCube == true){
//                 myCubeList.deleteCube(selectedCube, iboList, vaoList, vboList);
//                 currentActive = -1;

//                 // VBO
//                 if(selectedCube<=vboList.size()+1){
//                     glDeleteBuffers(1, &iboList[selectedCube+1]);
//                     iboList.erase(iboList.begin()+selectedCube+1);
//                     glDeleteVertexArrays(1, &vaoList[selectedCube+1]);
//                     vaoList.erase(vaoList.begin()+selectedCube+1);
//                     glDeleteBuffers(1, &vboList[selectedCube+1]);
//                     vboList.erase(vboList.begin()+selectedCube+1);
//                 }
//             }

//             // Rendu
//             glUniform3f(uKd, 0.6, 0.6, 0.6); //Couleur des boules
//             glUniform3f(uKs, 0, 0.0, 0.0);
//             glUniform1f(uShininess, 32.0);
//             glm::vec4 LightPos = ViewMatrix * glm::vec4((float) xLightP, (float) yLightP, (float) zLightP, 1);
//             glUniform3f(uLightPos_vs, LightPos.x, LightPos.y, LightPos.z);
//             glm::vec4 LightDir = ViewMatrix * glm::vec4((float) xLightD, (float) yLightD, (float) zLightD, 1);

//             glUniform3f(uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
//             if (item_LightD == 0){
//                 glUniform3f(uLightIntensityD, 2.0, 2.0, 2.0);   
//             }
//             else {
//                 glUniform3f(uLightIntensityD, 0.0, 0.0, 0.0);
//             }
//             if (item_LightP == 0){
//                 glUniform3f(uLightIntensityP, 2.0, 2.0, 2.0);   
//             }
//             else {
//                 glUniform3f(uLightIntensityP, 0.0, 0.0, 0.0);
//             }


//             /// Cursor move
//             cursor.setTrans(xCursor, yCursor, zCursor);


//             glm::mat4 ModelMatrix = glm::mat4(1.0f);
//             glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix * ModelMatrix));

//             glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection
//             glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix * ModelMatrix));
//             glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            


//             // Enable depth test
//             glEnable(GL_DEPTH_TEST);
//             // Accept fragment if it closer to the camera than the former one
//             glDepthFunc(GL_LESS);

//             /** Draw cube list **/
//             int currentTexture = myCubeList.getTextureIndex(0);
//             // Active first texture
//             glActiveTexture(GL_TEXTURE0);
//             glBindTexture(GL_TEXTURE_2D, textures[myCubeList.getTextureIndex(0)].getTexture()); // la texture est bindée sur l'unité GL_TEXTURE0
//             glUniform1i(textures[myCubeList.getTextureIndex(0)].getUniformLocation(), 0);
//             // Active first MVP
//             ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
//             ModelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f,0.0f,0.0f));
//             ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
//             glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection
//             glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix * ModelMatrix)); //Model View Projection
//             glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix)); //Model View Projection

            
//             currentActive = -1;
//             thereIsACubeAbove = false;
//             thereIsACubeUnder = false;
//             for(int i=0; i<myCubeList.getSize(); i++){
//                 if ((myCubeList.getTrans(i).x == cursor.getTrans().x) && (myCubeList.getTrans(i).y == cursor.getTrans().y) && (myCubeList.getTrans(i).z == cursor.getTrans().z)){
//                     currentActive = myCubeList.getCubeIndex(i);
//                 }
//                 if ((myCubeList.getTrans(i).x == cursor.getTrans().x) && (myCubeList.getTrans(i).y == cursor.getTrans().y+1) && (myCubeList.getTrans(i).z == cursor.getTrans().z)){
//                     thereIsACubeAbove = true;
//                 }
//                 if ((myCubeList.getTrans(i).x == cursor.getTrans().x) && (myCubeList.getTrans(i).y == cursor.getTrans().y-1) && (myCubeList.getTrans(i).z == cursor.getTrans().z)){
//                     thereIsACubeUnder = true;
//                 }
//                 if(currentTexture != myCubeList.getTextureIndex(i)){
//                     currentTexture = myCubeList.getTextureIndex(i);
//                     glActiveTexture(GL_TEXTURE0);
//                     glBindTexture(GL_TEXTURE_2D, textures[myCubeList.getTextureIndex(i)].getTexture()); // la texture est bindée sur l'unité GL_TEXTURE0
//                     glUniform1i(textures[myCubeList.getTextureIndex(i)].getUniformLocation(), 0);
//                 }

//                 glBindVertexArray(vaoList[myCubeList.getCubeIndex(i)+1]);

//                 // Transform
//                 ModelMatrix = glm::scale(glm::mat4(1.0f), myCubeList.getScale(myCubeList.getCubeIndex(i)));
//                 //Model = glm::translate(Model, myCubeList.getTrans(myCubeList.getCubeIndex(i)));
//                 ModelMatrix = glm::rotate(ModelMatrix, myCubeList.getRotDeg(myCubeList.getCubeIndex(i)), myCubeList.getRot(myCubeList.getCubeIndex(i)));
//                 ModelMatrix = glm::translate(ModelMatrix, myCubeList.getTrans(myCubeList.getCubeIndex(i)));
//                 // Our ModelViewProjection : multiplication of our 3 matrices
//                 glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection
//                 glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr( ViewMatrix * ModelMatrix)); //Model View Projection
//                 glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(ViewMatrix * ModelMatrix)))); //Model View Projection

//                 // Draw cube
//                 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[myCubeList.getCubeIndex(i)+1]);
//                 glDrawElements(GL_TRIANGLES, myCubeList.getIBOCount(i), GL_UNSIGNED_INT, (void *)0);
//             }

            
//             glDisable(GL_DEPTH_TEST);



//             glBindVertexArray(vaoList[0]);

//             glBindTexture(GL_TEXTURE_2D, textures[cursor.getTextureIndex()].getTexture()); // la texture est bindée sur l'unité GL_TEXTURE0
//             glUniform1i(textures[cursor.getTextureIndex()].getUniformLocation(), 0);
//             // Transform
//             ModelMatrix = glm::scale(glm::mat4(1.0f), cursor.getScale());
//             //Model = glm::translate(Model, myCubeList.getTrans(myCubeList.getCubeIndex(i)));
//             ModelMatrix = glm::rotate(ModelMatrix, cursor.getRotDeg(), cursor.getRot());
//             ModelMatrix = glm::translate(ModelMatrix, cursor.getTrans());
//             // Our ModelViewProjection : multiplication of our 3 matrices
//             glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection

//             // Draw cube
//             glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[0]);
//             glLineWidth(5.0);
//             glDrawElements(GL_LINES, cursor.getIBOCountBorder(), GL_UNSIGNED_INT, (void *)0);


//             glBindVertexArray(0);
//             glActiveTexture(GL_TEXTURE0);
//             glBindTexture(GL_TEXTURE_2D, 0);





//             //////////////////////////////////// load 3d
//             if (item_Light3D == 0){
//                 // NormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(ViewMatrix * ModelMatrix)))); //Model View Projection
//                 // Bind our texture in Texture Unit 0
//                 glActiveTexture(GL_TEXTURE0);
//                 glBindTexture(GL_TEXTURE_2D, Texture);
//                 // Set our "myTextureSampler" sampler to use Texture Unit 0
//                 glUniform1i(TextureID, 0);

//                 // 1rst attribute buffer : vertices
//                 glEnableVertexAttribArray(0);
//                 glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//                 glVertexAttribPointer(
//                     0,                  // attribute
//                     3,                  // size
//                     GL_FLOAT,           // type
//                     GL_FALSE,           // normalized?
//                     0,                  // stride
//                     (void*)0            // array buffer offset
//                 );

//                 // 2nd attribute buffer : UVs
//                 glEnableVertexAttribArray(2);
//                 glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
//                 glVertexAttribPointer(
//                     2,                                // attribute
//                     2,                                // size
//                     GL_FLOAT,                         // type
//                     GL_FALSE,                         // normalized?
//                     0,                                // stride
//                     (void*)0                          // array buffer offset
//                 );

//                 // 3rd attribute buffer : normals
//                 glEnableVertexAttribArray(1);
//                 glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
//                 glVertexAttribPointer(
//                     1,                                // attribute
//                     3,                                // size
//                     GL_FLOAT,                         // type
//                     GL_FALSE,                         // normalized?
//                     0,                                // stride
//                     (void*)0                          // array buffer offset
//                 );

//                 // Draw the triangles !
//                 glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

//                 glDisableVertexAttribArray(0);
//                 glDisableVertexAttribArray(1);
//                 glDisableVertexAttribArray(2);
//             }








//             ImGui::Render();
//             ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//             // Update the display
//             windowManager.swapBuffers();
//         }


//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplSDL2_Shutdown();
//     ImGui::DestroyContext();

return EXIT_SUCCESS;
}
