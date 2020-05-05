#include "Headers/Engine/Texture/Texture.h"

#pragma once

class Material {
private:
    Texture albedo;
    Texture ao;
    Texture metallic;
    Texture normal;
    Texture roughness;
public:
    //takes the directory of a folder containing textures with correct names
    Material(const char* directory, int type);
    Material();

    [[nodiscard]] const Texture &getAlbedo() const;

    [[nodiscard]] const Texture &getAo() const;

    [[nodiscard]] const Texture &getMetallic() const;

    [[nodiscard]] const Texture &getNormal() const;

    [[nodiscard]] const Texture &getRoughness() const;

};

