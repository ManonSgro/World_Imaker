#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 aVertexPosition_modelspace;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 vUV;
out vec3 vPosition_vs; //position du sommet transformée dans le view space
out vec3 vNormal_vs; //normale du sommet transformée dans le view space


mat3 translate(float tx, float ty){
    mat3 M = mat3(vec3(1,0,0), vec3(0,1,0), vec3(tx, ty, 1));
    return M;
}

// Values that stay constant for the whole mesh.
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

void main(){

    vec4 vertexPosition = vec4(aVertexPosition_modelspace, 1);
	vec4 vertexNormal = vec4(aVertexNormal, 0);

	//Valeurs de sortie
	vPosition_vs = vec3(uMVMatrix * vertexPosition);
    vNormal_vs = vec3(uNormalMatrix * vertexNormal);

    // Output position of the vertex, in clip space : MVP * position
    gl_Position = uMVPMatrix * vec4(aVertexPosition_modelspace, 1);

    // UV of the vertex. No special space for this one.
    vUV = aVertexUV;
}



