#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inColor;

uniform mat4 model;

out vec3 vertexColor;

void main() {
	gl_Position = model * vec4(aPos, 1.0f);
	vertexColor = inColor;
}
