#pragma once

#include "Headers/Engine/ResourceContainers/stb_PointerContainer.h"

#include <memory>
#include <algorithm>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class TerrainMesh {
public:
    TerrainMesh() = default;

    TerrainMesh(const TerrainMesh &terrainMeshObj) = delete;
    TerrainMesh(TerrainMesh &&oldTerrainMeshObj) = default;

    explicit TerrainMesh(const char* filename);

    TerrainMesh &operator=(const TerrainMesh &terrainMeshObj) = delete;
    TerrainMesh &operator=(TerrainMesh &&oldTerrainMeshObj) = default;

    void bindVAO() const;

    static void unbindVAO();

    [[nodiscard]] unsigned int getNumOfVertices() const;

    static constexpr float SIZE = 1600;
    static constexpr float MAX_HEIGHT = 80;

    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight(float x, float z) const;
    [[nodiscard]] glm::vec3 calculateNormal(float x, float z) const;

    ~TerrainMesh();

private:
    std::shared_ptr<stb_PointerContainer> dataContainer = nullptr;

    int height{};
    void loadTerrain(std::vector<glm::vec3>& verticies, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords, std::vector<unsigned int>& indices, const char* filename);
    unsigned int VAO{}, VBO{}, EBO{}, texCoordBuffer{}, normalBuffer{}, numOfVertices{}; //be careful with making numOfVertices unsigned. unsigned and signed number can NOT mix. //@todo decide whether it is ok to have numOfVertices be unsigned
};