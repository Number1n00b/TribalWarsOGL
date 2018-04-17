#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "EntityManager.h"

class EntityManager;

class Entity{
    public:
        Entity(EntityManager* manager, std::string name, float x_pos, float y_pos);

        std::string GetName();
        float GetXPos();
        float GetYPos();

        bool operator ==(const Entity &other) const;

        ~Entity();
    private:
        //EntityType type; (?)

        EntityManager* m_Manager;

        std::string m_Name;

        float m_XPos;
        float m_YPos;
};


#endif //ENTITY_H
