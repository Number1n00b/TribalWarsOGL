#ifndef ENTITY_H
#define ENTITY_H


class Entity{
    public:
        Entity(x_pos, y_pos);

        bool operator ==(const Entity &other) const;

        ~Entity();
    private:
        int m_XPos;
        int m_YPos;
}


#endif //ENTITY_H
