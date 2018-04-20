#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity{
    public:
        Entity(std::string name, float x_pos, float y_pos);

        std::string GetName();
        float GetXPos();
        float GetYPos();

        int GetUID();

        bool operator ==(const Entity &other) const;

        ~Entity();
    private:
        //EntityType type; (?)
        std::string m_Name;

        static int next_id;
        int m_uid;

        float m_XPos;
        float m_YPos;
};


#endif //ENTITY_H
