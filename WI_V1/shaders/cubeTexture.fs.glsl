#version 330 core

// Interpolated values from the vertex shaders
in vec2 vUV;


// Values that stay constant for the whole mesh.
uniform sampler2D uTexture0;
uniform sampler2D uTexture1;


// Ouput data
out vec3 fFragColor;

void main(){

    // Output color = color of the texture at the specified UV
    vec4 color1 = texture(uTexture0, vUV);
    //fColor = vec3(1, 0, 0);
    vec4 color2 = texture(uTexture1, vUV);

    fFragColor = color1.rgb;
}
