#pragma once

#include <memory>
#include <vector>
#include <cstring> //memcpy & memset

#include "Headers/Engine/Texture/IQuadTexture.h"
#include "Headers/Engine/ResourceContainers/TextureResourceContainer.h"
#include "Headers/Engine/Utils/MathUtils.h"
#include "Character.h"
#include "FontFileReader.h"
#include "ImageFileReader.h"
#include "Headers/Engine/Shader/Shader.h"

class Text : public IQuadTexture{
public:
    Text();

    Text(const Text &textObj) = delete;
    Text(Text &&oldTextObj) = default;

    Text(FontFileReader &fontInfo, ImageFileReader &imageData, const std::string &text);

    void bind(const Shader &shader) const noexcept override;
    void unbind() const noexcept override;

    Text& operator=(const Text &textObj) = delete;
    Text& operator=(Text &&oldTextObj) = default;

    [[nodiscard]] unsigned int get_ID() const;

private:
    std::vector<Character> text;

    std::unique_ptr<TextureResourceContainer> IDContainer;
    static constexpr int textureUnit = 0; //temporary, will change later
};
