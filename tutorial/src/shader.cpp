#include "shader.hpp"

#include <stdlib.h>
#include <stdio.h>

GLuint loadShaderProgram(const char *vertexPath, const char *fragmentPath) {
	FILE *vertexFile = fopen(vertexPath, "r");

	if(vertexFile == NULL) {
		printf("[+] Unable to open vertex shader file: %s\n", vertexPath);
	}

    long fileLen;
    size_t codeLen;

    fseek(vertexFile, 0, SEEK_END);
    fileLen = ftell(vertexFile);
    fseek(vertexFile, 0, SEEK_SET);

    char *vertexCode = (char *)malloc(sizeof(char) * (fileLen + 1));

    codeLen = fread(vertexCode, sizeof(char), fileLen, vertexFile);
    fclose(vertexFile);

    if(ferror(vertexFile)) {
		printf("[+] Unable to read from vertex shader file: %s\n", vertexPath);
    }

    vertexCode[codeLen] = '\0';
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, (const char **)&vertexCode, NULL);
    free(vertexCode);

    glCompileShader(vertexShader);

    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("[+] Vertex shader compilation error\n%s\n", infoLog);
    }


    ///////////////////////////////////////////////////////////////////////
    
	FILE *fragmentFile = fopen(fragmentPath, "r");

	if(fragmentFile == NULL) {
		printf("[+] Unable to open fragment shader file: %s\n", fragmentPath);
	}

    fseek(fragmentFile, 0, SEEK_END);
    fileLen = ftell(fragmentFile);
    fseek(fragmentFile, 0, SEEK_SET);

    char *fragmentCode = (char *)malloc(sizeof(char) * (fileLen + 1));
    
    codeLen = fread(fragmentCode, sizeof(char), fileLen, fragmentFile);
    fclose(fragmentFile);

    if(ferror(fragmentFile)) {
		printf("[+] Unable to read from fragment shader file: %s\n", fragmentPath);
    }

    fragmentCode[codeLen] = '\0';

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const char **)&fragmentCode, NULL);
    free(fragmentCode);

    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("[+] Fragment shader compilation error\n%s\n", infoLog);
    }

    ///////////////////////////////////////////////////////////////////////
    
    GLuint ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        printf("[+] Shader program linking error\n%s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return ID;
}
