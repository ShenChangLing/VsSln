#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec4 outColor;
out vec2 outTexCoord;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 p;

void main()
{
	gl_Position = p*view*transform*vec4(aPos,1.0);
	outColor = aColor;
	outTexCoord = aTexCoord;
}