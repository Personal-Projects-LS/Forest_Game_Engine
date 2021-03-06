#include <Headers/Engine/Models/stb_image.h> //must be included in cpp file

#include <utility>

#include "Headers/Engine/Models/Texture.h"

Texture::Texture() {
    textureUnit = 0;
};

Texture::Texture(const char *filename, int unit, std::string nameInShader) {
    textureFilename = std::string(filename);
    shaderName = std::move(nameInShader);
    unsigned int ID;

    int type = 0;
    if (std::regex_match(filename, std::regex("(.+)(\\.png)")) || std::regex_match(filename, std::regex("(.+)(\\.bmp)"))) {
        type = PNG;
    }
    else if (std::regex_match(filename, std::regex("(.+)(\\.jpg)"))) {
        type = JPG;
    }
    else {
        std::cerr << "File type not supported!. Please supply a JPG or PNG!" << std::endl;
    }
    textureUnit = unit;
    glGenTextures(1, &ID);
    int width, height, nrchannels;
    unsigned char *data = nullptr;
    if (type == PNG) {
        data = stbi_load(filename, &width, &height, &nrchannels, STBI_rgb_alpha);
    } else {
        data = stbi_load(filename, &width, &height, &nrchannels, STBI_rgb);
    }

    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if(data){
        if(type == JPG) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load " << filename << " texture!" << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    IDContainer = std::make_shared<TextureResourceContainer>(ID);
}

Texture::Texture(Texture &&oldTexture) noexcept {
    IDContainer = oldTexture.IDContainer;
    oldTexture.IDContainer = nullptr;

    textureUnit = oldTexture.textureUnit;
    oldTexture.textureUnit = 0;

    shaderName = oldTexture.shaderName;
}

Texture::Texture(const Texture &original) {
    if (this != &original) {
        textureFilename = original.textureFilename;

        textureUnit = original.textureUnit;

        shaderName = original.shaderName;

        assert(IDContainer == nullptr);
        IDContainer = original.IDContainer;
    }
}

Texture& Texture::operator=(Texture &&oldTexture) noexcept {
    IDContainer = oldTexture.IDContainer;
    oldTexture.IDContainer = nullptr;

    textureUnit = oldTexture.textureUnit;

    shaderName = oldTexture.shaderName;
    oldTexture.textureUnit = 0;

    return *this;
}

Texture& Texture::operator=(const Texture &original) {
    if(this == &original) {
        return *this;
    }

    textureFilename = original.textureFilename;

    textureUnit = original.textureUnit;

    shaderName = original.shaderName;

    assert(IDContainer == nullptr);
    IDContainer = original.IDContainer;

    return *this;
}

Texture::~Texture() = default;

unsigned int Texture::get_ID(){
    return IDContainer->getID();
}

void Texture::bind(Shader &shader) {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, IDContainer->getID());
    int textureLoc = glGetUniformLocation(shader.ID, shaderName.c_str());
    glUniform1i(textureLoc, textureUnit);
}

void Texture::unbind() {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
}
