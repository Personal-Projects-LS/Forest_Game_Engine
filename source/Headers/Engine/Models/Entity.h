#pragma once

#include <memory>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Engine/Models/Mesh.h"
#include "Headers/Engine/Texture/Texture.h"
#include "Headers/Engine/Shader/Shader.h"
#include "Headers/Engine/Camera/Camera.h"
#include "Headers/Engine/Collisions/Plane.h"
#include "Headers/Engine/Graphics/Materials/Material.h"
#include <Headers/Engine/Graphics/Lighting/PointLight.h>


class Entity {
public:
    Entity() = default;

    Entity(
            const std::shared_ptr<Mesh> &mesh,
            const std::vector<Texture>& textures,
            const glm::vec3& position,
            const glm::vec3& rotation,
            const glm::vec3& scale
    ) noexcept;

    Entity(
            const std::shared_ptr<Mesh> &mesh,
            const Material &material,
            const Shader &shader,
            const glm::vec3 &position,
            const glm::vec3 &rotation,
            const glm::vec3& scale
    ) noexcept;

    void render(const Camera& camera, const Shader& shader, glm::vec3 lightPos, glm::vec3 lightColor) const noexcept;

    void render(const Camera &camera, const std::vector<PointLight> &pointLights) const noexcept;

    [[nodiscard]] glm::vec3 getScale() const noexcept;
    [[nodiscard]] glm::vec3 getPos() const noexcept;
    [[nodiscard]] glm::vec3 getRotation() const noexcept;

    void setPos(glm::vec3 newPos) noexcept;
    void setRotation(glm::vec3 newRotation) noexcept;
    void rotate(glm::vec3 rotation) noexcept;
    void translate(glm::vec3 translation) noexcept;
    void addScale(glm::vec3 scale) noexcept;

    void setFlipped() noexcept;

    glm::mat4 createModelMatrix() noexcept;

    std::vector<Plane> planes;
    bool hit = false;
    bool pickedUp = false;
    double verticalOffset = 0;

private:
    std::shared_ptr<Mesh> mesh;
    std::vector<Texture> textures;
    Shader shader;
    Material material;
    glm::vec3 rotation{}, position{}, scale{};
    glm::mat4 modelMatrix{};

    float flipped = -1; //@todo check if this should be here

    void limitRotation() noexcept;
    void moveEntityPlanes(const std::vector<glm::vec3> &vertices) noexcept;
};


