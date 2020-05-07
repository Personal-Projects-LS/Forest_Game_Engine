#include <Headers/Game/Loop/Progression.h>
#include <Headers/Game/Loop/Time.h>
#include "Headers/Game/Environment/BoundingBox.h"

BoundingBox::BoundingBox(Entity *box) : m_entity(box) {
    resetSize();
}

void BoundingBox::resetSize() {
    float scaleOffset = SIZE - m_entity->getScale().x;
    m_entity->addScale(scaleOffset, scaleOffset, scaleOffset);
}

void BoundingBox::shrink() {
    if(m_entity->getScale().x > 50) {
        float speed = 0.0f;
        switch(Progression::getProgress()) {
            case 0:
                speed  = SPEED_LVL1 * Time::getDeltaTime();
                break;
            case 1:
                speed  = SPEED_LVL2 * Time::getDeltaTime();
                break;
            case 2:
                speed  = SPEED_LVL3 * Time::getDeltaTime();
                break;
            case 3:
                speed  = SPEED_FINAL * Time::getDeltaTime();
                break;
        }
        m_entity->addScale(speed, speed, speed);
    }
}

void BoundingBox::turnOff(std::vector<Entity *> &entities) {
    for(unsigned int i = 0; i < entities.size(); ++i) {
        if(entities[i] == m_entity) {
            entities.erase(entities.begin() + i);
        }
    }
}

void BoundingBox::turnOn(std::vector<Entity *> &entities) {
    resetSize();
    entities.push_back(m_entity);
}

Entity* BoundingBox::getEntity() {
    return m_entity;
}