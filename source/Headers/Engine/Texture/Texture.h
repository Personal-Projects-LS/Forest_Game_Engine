#pragma once

#include <memory>
#include <regex>
#include <glad/glad.h>
#include <iostream>
#include <string>

#include "Headers/Engine/Texture/IQuadTexture.h"
#include "Headers/Engine/Shader/Shader.h"
#include "Headers/Engine/ResourceContainers/TextureResourceContainer.h"

class Texture : public IQuadTexture {
public:
    Texture();
    explicit Texture(const char *filename, int unit, std::string nameInShader);

    void bind(const Shader& shader) const noexcept override;
    void unbind() const noexcept override;

    static constexpr int PNG = 0;
    static constexpr int JPG = 1;

    [[nodiscard]] unsigned int get_ID() const;

private:
    std::shared_ptr<TextureResourceContainer> IDContainer = nullptr;
    int textureUnit{};
    std::string shaderName;
};
