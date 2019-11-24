
#version 330 core

in vec3 vFragColor;

out vec3 fFragColor;

uniform vec3 uColor;
uniform sampler2D uTexture;
void main()
{
	fFragColor = uColor;
}
