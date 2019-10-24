//
// Created by aekstrand7207 on 10/24/2019.
//

#include "Headers/Engine/Skybox/CubeMapTexture.h"

CubeMapTexture::CubeMapTexture() = default;

CubeMapTexture::CubeMapTexture(std::vector<const char *> files) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
    unsigned char* data;
    int width, height, channels;
    for(int i = 0; i < files.size(); ++i) {
        data = stbi_load(files[i], &width, &height, &channels, GL_RGB);
        if(data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Failed to load cubemap!" << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

CubeMapTexture::~CubeMapTexture() = default;

void CubeMapTexture::bind(Shader &shader) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void CubeMapTexture::unBind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}