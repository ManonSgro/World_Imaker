
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
#include <glimac/objloader.hpp>
#include <glimac/text.hpp>
#include <cstddef>
#include <vector>

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
    cubeList.push_back(Cube());
    cubeList.push_back(Cube());
    cubeList.push_back(Cube());
    cubeList[1].translateVertices(0.0,2.0,-2.0);
    cubeList[0].translateVertices(0.0,0.0,-2.0);
    cubeList[2].translateVertices(0.0,0.0,0.0);


    /** Array of Textures **/
    uint nbOfTextures = 2;
    std::vector<Texture> textures(nbOfTextures);

    //Chargement des shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/cubeOBJ.vs.glsl",
        applicationPath.dirPath() + "shaders/cubeOBJ.fs.glsl"
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
    //GLint TextureID  = glGetUniformLocation(program.getGLId(), "textureSampler");
   // GLuint LightID = glGetUniformLocation(program.getGLId(), "LightPosition_worldspace");

    for(int i=0; i<textures.size(); i++){
        char const *pchar = "uTexture" + i;
        textures[i].setUniformLocation(program, (GLchar*)pchar);
    }

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
    textures[0].setImage("../GLImac-Template/assets/textures/brique.png");
    textures[1].setImage("../GLImac-Template/assets/textures/herbe.png");
    // Link cubes with textures
    cubeList[0].setTextureIndex(0);
    cubeList[1].setTextureIndex(1);
    cubeList[2].setTextureIndex(1);


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


	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	//GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(program.getGLId(), "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(program.getGLId(), "V");
	GLuint ModelMatrixID = glGetUniformLocation(program.getGLId(), "M");

	// Load the texture
	GLuint Texture = loadDDS("../GLImac-Template/assets/models/uvmap.DDS");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(program.getGLId(), "myTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("../GLImac-Template/assets/models/suzanne.obj", vertices, uvs, normals);

	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	//glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(program.getGLId(), "LightPosition_worldspace");


    /**********************************/
    /******* BOUCLE D'AFFICHAGE *******/
    /**********************************/


    // Application loop:
    bool done = false;
    while(!done) {

        // Event loop:
        Controls c;
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
        glUseProgram(program.getGLId());

        glUniform3f(uKd, 0.6, 0.6, 0.6); //Couleur des boules
        glUniform3f(uKs, 0.0, 0.0, 0.0);
        glUniform1f(uShininess, 32.0);
        glm::vec4 LightPos = ViewMatrix * glm::vec4(1.0, 1.0, 0.0, 1);
        glUniform3f(uLightPos_vs, LightPos.x, LightPos.y, LightPos.z);
        glm::vec4 LightDir = ViewMatrix * glm::vec4(1.0, 1.0, 1.0, 1);
        glUniform3f(uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        glUniform3f(uLightIntensity, 2.0, 2.0, 2.0);

        glm::mat4 ModelMatrix = glm::mat4();
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix * ModelMatrix));

        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix * ViewMatrix * ModelMatrix)); //Model View Projection
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix * ModelMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));



		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(4,4,4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangles !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
glDisableVertexAttribArray(2);



        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
