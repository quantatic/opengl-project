#include "texture.h"

#include <GL/glew.h>

#include <stdio.h>
#include <string.h>


GLuint loadTextureBMP(const char *texturePath) {
    FILE *fp = fopen(texturePath, "rb"); 

    if(fp == NULL) {
        printf("[+] Unable to open texture file %s for reading\n", texturePath);
    }

    unsigned char header[54];

    if(fread(header, 1, 54, fp) != 54) {
        printf("[+] Not able to read entire header from %s\n", texturePath);    
    }

    if(header[0] != 'B' || header[1] != 'M') {
        printf("[+] File magic number not correct in file %s\n", texturePath);
    }

    int dataPos, imageSize, width, height;

    memcpy(&dataPos, &header[0x0A], sizeof(int));
    memcpy(&imageSize, &header[0x22], sizeof(int));
    memcpy(&width, &header[0x12], sizeof(int));
    memcpy(&height, &header[0x16], sizeof(int));

    //fix misformatted bmp by guessing information
    
    if(imageSize == 0) {
        imageSize = width * height * 3;
    }

    if(dataPos == 0) {
        dataPos = 54;
    }

    unsigned char data[imageSize];

    fseek(fp, dataPos, SEEK_SET);
    fread(data, 1, imageSize, fp);
    fclose(fp);

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return textureID;    
}
