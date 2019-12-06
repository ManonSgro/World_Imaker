#version 330 core

in vec3 vFragColor;

out vec3 fFragColor;

void main() {
   float grey = (vFragColor.x+vFragColor.y+vFragColor.y)/3;
  fFragColor = vec3(grey, grey, grey);
};
