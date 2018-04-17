#include "Entity.h"

Entity::Entity(EntityManager* manager, std::string name, float x_pos, float y_pos){
    m_Manager = manager;

    m_Name = name;
    m_XPos = x_pos;
    m_YPos = y_pos;

    m_Manager->RegisterEntity(this);
}

std::string Entity::GetName(){
    return m_Name;
}

float Entity::GetXPos(){
    return m_XPos;
}

float Entity::GetYPos(){
    return m_YPos;
}


bool Entity::operator ==(const Entity &other) const{
    return m_Name == other.m_Name;
}


Entity::~Entity(){
    //Empty
}
