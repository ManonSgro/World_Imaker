#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 aVertexPosition_modelspace;
layout(location = 1) in vec2 aVertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 vUV;

// Values that stay constant for the whole mesh.
uniform mat4 uMVP;

void main(){
    // Output position of the vertex, in clip space : MVP * position
    gl_Position = uMVP * vec4(aVertexPosition_modelspace, 1);

    // UV of the vertex. No special space for this one.
    vUV = aVertexUV;
}
