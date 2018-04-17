#include "Entity.h"

Entity::Entity(x_pos, y_pos){
    m_XPos = x_pos;
    m_YPos = y_pos;
}


bool Entity::operator ==(const Entity &other) const{
    return ((m_XPos == other->m_XPos) && (m_YPos == other->m_Ypos));
}


Entity::~Entity(){
    //Empty
}
