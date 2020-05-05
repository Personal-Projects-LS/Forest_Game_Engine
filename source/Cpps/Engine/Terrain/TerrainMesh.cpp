#include <Headers/Engine/Models/stb_image.h>

#include "Headers/Engine/Terrain/TerrainMesh.h"

TerrainMesh::TerrainMesh(const char* filename) {
    std::vector<glm::vec3> vertices, normals;
    std::vector<glm::vec2> texCoords;
    std::vector<unsigned int> indices;
    loadTerrain(vertices, normals, texCoords, indices, filename);
    numOfVertices = indices.size();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &texCoordBuffer);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &normalBuffer);
    bindVAO();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    unbindVAO();
}

TerrainMesh::~TerrainMesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &texCoordBuffer);
    glDeleteBuffers(1, &normalBuffer);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void TerrainMesh::bindVAO() const {
    glBindVertexArray(VAO);
}

void TerrainMesh::unbindVAO() {
    glBindVertexArray(0);
}

[[nodiscard]] unsigned int TerrainMesh::getNumOfVertices() const {
    return numOfVertices;
}

void TerrainMesh::loadTerrain(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &texCoords, std::vector<unsigned int> &indices, const char* filename) {
    int width, nrchannels;
    dataContainer = std::make_shared<stb_PointerContainer>(stbi_load(filename, &width, &height, &nrchannels, 1));
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < height; ++j){
            vertices.emplace_back(static_cast<float>(j)/static_cast<float>(height - 1) * SIZE, getHeight(static_cast<float>(j), static_cast<float>(i)), static_cast<float>(i)/static_cast<float>(height - 1) * SIZE);
            normals.push_back(calculateNormal(static_cast<float>(j), static_cast<float>(i)));
            texCoords.emplace_back(static_cast<float>(j)/static_cast<float>(height - 1), static_cast<float>(i)/static_cast<float>(height - 1));
        }
    }
    for(int gz = 0; gz < height - 1; ++gz){
        for(int gx = 0; gx < (height - 1); ++gx){
            int topLeft = gz*height + gx;
            int topRight = topLeft + 1;
            int bottomLeft = (gz+1)*height + gx;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
}

[[nodiscard]] float TerrainMesh::getHeight(float x, float z) const {
    return (((static_cast<float>(
                dataContainer->getData()[static_cast<int>(
                    std::clamp(z, 0.0f, getWidth())
                    * static_cast<float>(height)
                    + std::clamp(x, 0.0f, getWidth()))
                ])/127.5f)-1.0f)*MAX_HEIGHT
    );
}

[[nodiscard]] glm::vec3 TerrainMesh::calculateNormal(float x, float z) const {
    const float heightL = getHeight(x - 1, z);
    const float heightR = getHeight(x + 1, z);
    const float heightU = getHeight(x, z + 1);
    const float heightD = getHeight(x, z - 1);
    glm::vec3 normal(heightL - heightR, 2, heightD - heightU);
    normal = glm::normalize(normal);
    return normal;
}

[[nodiscard]] float TerrainMesh::getWidth() const {
    return static_cast<float>(height - 1);
}