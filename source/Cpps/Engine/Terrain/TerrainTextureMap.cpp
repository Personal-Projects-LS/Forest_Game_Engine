#include "Headers/Engine/Terrain/TerrainTextureMap.h"

TerrainTextureMap::TerrainTextureMap(const char *map, const char *texture1, const char *texture2, const char *texture3,
                                     const char *texture4) noexcept {
    textures.reserve(5);
    textures.emplace_back(map, 0, "texture0");
    textures.emplace_back(texture1, 1, "texture1");
    textures.emplace_back(texture2, 2, "texture2");
    textures.emplace_back(texture3, 3, "texture3");
    textures.emplace_back(texture4, 4, "texture4");
}

void TerrainTextureMap::bindTextures(const Shader &shader) const noexcept {
    for(const Texture &texture : textures) {
        texture.bind(shader);
    }
}

void TerrainTextureMap::unBindTextures() const noexcept {
    for(const Texture &texture : textures) {
        texture.unbind();
    }
}
