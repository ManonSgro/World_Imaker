#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragColor;
uniform sampler2D uTexture;
uniform sampler2D uAddTexture;
void main()
{
	fFragColor = vec3(texture(uTexture, vTexCoords).xyz + texture(uAddTexture, vTexCoords).xyz);
}
