#version 330 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform sampler2D uTexture;

out vec3 fFragColor;

void main() {

    vec4 color = texture(uTexture, vTexCoords);
    fFragColor = color.rgb;
}
