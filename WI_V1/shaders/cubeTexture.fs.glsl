#version 330 core

// Interpolated values from the vertex shaders
in vec2 vUV;


// Values that stay constant for the whole mesh.
uniform sampler2D uTextureSampler;
uniform sampler2D uTextureGrass;


// Ouput data
out vec3 fFragColor;

void main(){

    // Output color = color of the texture at the specified UV
    vec4 color1 = texture(uTextureSampler, vUV);
    //fColor = vec3(1, 0, 0);
    vec4 color2 = texture(uTextureGrass, vUV);

    fFragColor = color1.rgb + color2.rgb;
}
