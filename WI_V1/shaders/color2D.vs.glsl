#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;

mat3 translate(float tx, float ty){
    mat3 M = mat3(vec3(1,0,0), vec3(0,1,0), vec3(tx, ty, 1));
    return M;
};

mat3 scale(float sx, float sy){
    mat3 M = mat3(vec3(sx,0,0), vec3(0,sy,0), vec3(0, 0, 1));
    return M;
};

mat3 rotate(float a){
    mat3 M = mat3(vec3(cos(radians(a)), sin(radians(a)), 0), vec3(-sin(radians(a)),cos(radians(a)),0), vec3(0, 0, 1));
    return M;
};

void main() {
  vFragColor = aVertexColor;
  //gl_Position = vec4(aVertexPosition, 0, 1);
  //gl_Position = vec4(aVertexPosition+vec2(0.5,0.5), 0, 1); //translate
  //gl_Position = vec4(aVertexPosition*2, 0, 1); //scale
  //gl_Position = vec4(aVertexPosition*vec2(2,0.5), 0, 1); //scale

  //gl_Position = vec4((translate(0.5,0.5)*scale(2,0.5)*rotate(45.0)*vec3(aVertexPosition, 1)).xy, 0, 1);
  //déformation car repère pas à l'échelle

  gl_Position = vec4((rotate(0.0)*scale(1,1)*translate(0.5,0)*vec3(aVertexPosition, 1)).xy, 0, 1);

    //gl_Position = vec4((rotate(0.0)*scale(1.5,1.5)*translate(0.0,0.0)*vec3(aVertexPosition, 1)).xy, 0, 1);
};
