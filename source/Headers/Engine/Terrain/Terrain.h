#pragma once

#include <Headers/Engine/Camera.h>
#include "Headers/Engine/Terrain/TerrainTextureMap.h"
#include "Headers/Engine/Terrain/TerrainMesh.h"
#include "Headers/Engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Terrain {

public:
    Terrain(TerrainTextureMap& textureMap, TerrainMesh& terrainMesh, int gridX, int gridY);
    ~Terrain();
    void render(Camera& camera, Shader& shader, glm::vec3& lightPos, glm::vec3& lightColor);
private:
    TerrainTextureMap terrainTextureMap;
    TerrainMesh terrainMesh;
    int x, z;
    glm::vec3 position;
    glm::mat4 modelMatrix;
    glm::mat4 createModelMatrix();
};

