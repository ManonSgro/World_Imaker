#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;



mat3 translate(float tx, float ty)
{
	mat3 M = mat3(vec3(1, 0, 0), vec3(0, 1, 0), vec3(tx, ty, 1));
	return M;
}

mat3 scale(float sx, float sy)
{
	mat3 M = mat3(vec3(sx, 0, 0), vec3(0, sy, 0), vec3(0, 0, 1));
	return M;
}

mat3 rotate(float a)
{
	float ar;
	ar = radians(a);
	mat3 M = mat3(vec3(cos(ar), sin(ar), 0), vec3(-sin(ar), cos(ar), 0), vec3(0, 0, 1));
	return M;
}


uniform mat3 uModelMatrix;
void main()
{
	vFragColor = aVertexColor;
	gl_Position = vec4((uModelMatrix * vec3(aVertexPosition, 1)).xy, 0, 1);
}
