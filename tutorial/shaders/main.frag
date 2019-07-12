#version 330 core

in vec3 vertexColor;
in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;

uniform sampler2D ourTexture;

void main() {
	//FragColor = vec4(vertexColor, 1.0f);
	FragColor = texture(ourTexture, TexCoord);
}
