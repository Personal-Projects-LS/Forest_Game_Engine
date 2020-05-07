#pragma once

#include <Headers/Engine/Models/Entity.h>

class BoundingBox {
public:
    BoundingBox(Entity* box);
    void shrink();
    void resetSize();
    void turnOn(std::vector<Entity*>& entities);
    void turnOff(std::vector<Entity*>& entities);
    Entity* getEntity();
    static constexpr int SIZE = 500;
    static constexpr float SPEED_LVL1 = -20.0f;
    static constexpr float SPEED_LVL2 = -16.65f;
    static constexpr float SPEED_LVL3 = -13.32f;
    static constexpr float SPEED_FINAL = -6.67f;
private:
    Entity* m_entity;
};
