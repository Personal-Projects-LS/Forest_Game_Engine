#pragma once

#include <array>

#include "Headers/Engine/Models/Entity.h"
#include "Headers/Engine/Collisions/CollisionHandler.h"

#include "Headers/Game/Player/Player.h"

class Animal {
public:
    Animal(Entity entity, Player* player, int health, int dmg, float move_speed, float jump_power);

    template<size_t N>
    void update(std::vector<Entity *> &entities, std::array<Terrain, N> &terrains, Entity *boundingBox, bool bound);

    template<size_t N>
    void followPlayer(std::vector<Entity*> &entities, std::array<Terrain, N> &terrains, Entity* boundingBox, bool bound);

    Entity getEntity();
    Entity *getEntityPointer();
    void render(Camera &camera, Shader &shader, glm::vec3 &lightPos, glm::vec3 &lightColor);
    void hitPlayer();
    void takeDamage(int damage);
    bool isDead();

private:
    bool m_damagedPlayer = false;
    bool m_dead = false;
    int m_health;
    int m_damage;
    float m_move_speed;
    float m_jump_power;
    Entity m_entity;
    CollisionHandler m_collisionHandler;
    Player *m_player;
};

//template definitions:

template<size_t N>
void Animal::update(std::vector<Entity *> &entities, std::array<Terrain, N> &terrains, Entity* boundingBox, bool bound) {
    if(m_health > 0) {
        if (m_entity.hit) {
            takeDamage(1);
            m_entity.hit = false;
            if(m_health <= 0) {
                m_dead = true;
                for(int i = 0; i < entities.size(); ++i) {
                    if(entities[i] == &m_entity) {
                        entities.erase(entities.begin() + i);
                    }
                }
            }
        }
        followPlayer(entities, terrains, boundingBox, bound);
    }
}

template<size_t N>
void Animal::followPlayer(std::vector<Entity*> &entities, std::array<Terrain, N> &terrains, Entity* boundingBox, bool bound) {
    glm::vec3 move = m_player->getPlayerEntity().getPos() - m_entity.getPos();
    double turn = glm::degrees(atan(move.x / move.z));
    if(turn > 0) {
        turn -= 180;
    }
    turn += 90;
    glm::vec3 newRotation(m_entity.getRotation().x, turn, m_entity.getRotation().z);
    m_entity.setRotation(newRotation);
    if(!m_damagedPlayer) {
        if (std::sqrt(move.x * move.x + move.y * move.y + move.z * move.z) < 20 && !m_collisionHandler.inAir) {
            m_collisionHandler.currentGravity.y = m_jump_power;
            m_collisionHandler.inAir = true;
        }
        move.y = 0;
        move = glm::normalize(move);
        move *= m_move_speed;
        m_collisionHandler.moveEntity(move, entities, terrains, boundingBox, bound);
        //if(m_collisionHandler.hitPlayer) {
        //    m_damagedPlayer = true;
        //    hitPlayer();
        //}
    } else if(std::sqrt(move.x * move.x + move.y * move.y + move.z * move.z) > 30) {
        m_damagedPlayer = false;
    }
}
