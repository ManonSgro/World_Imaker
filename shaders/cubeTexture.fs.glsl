#version 330 core

// Interpolated values from the vertex shaders
in vec2 vUV;

// Ouput data
out vec3 fColor;

// Values that stay constant for the whole mesh.
uniform sampler2D uTextureSampler;

void main(){

    // Output color = color of the texture at the specified UV
    fColor = texture(uTextureSampler, vUV).rgb;
    //fColor = vec3(1, 0, 0);
}
