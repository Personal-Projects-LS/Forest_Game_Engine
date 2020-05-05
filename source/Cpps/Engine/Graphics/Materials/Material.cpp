
#include "Headers/Engine/Graphics/Materials/Material.h"

Material::Material(const char* directory, int type) {
    std::string extension = (type == Texture::PNG) ? "bmp" : "jpg";
    this -> albedo = Texture(((std::string(directory) + std::string("/albedo."))+ extension).c_str(), 0, "albedo");
    this -> ao = Texture(((std::string(directory) + std::string("/ao."))+ extension).c_str() , 1, "ao");
    this -> metallic = Texture(((std::string(directory) + std::string("/metallic."))+ extension).c_str() , 2, "metallic");
    this -> normal = Texture(((std::string(directory) + std::string("/normal."))+ extension).c_str() , 3, "normal");
    this -> roughness = Texture(((std::string(directory) + std::string("/roughness."))+ extension).c_str() , 4, "roughness");
}

Material::Material() = default;

const Texture &Material::getAlbedo() const {
    return albedo;
}

const Texture &Material::getAo() const {
    return ao;
}

const Texture &Material::getMetallic() const {
    return metallic;
}

const Texture &Material::getNormal() const {
    return normal;
}

const Texture &Material::getRoughness() const {
    return roughness;
}
