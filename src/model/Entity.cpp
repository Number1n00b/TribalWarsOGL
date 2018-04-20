#include "../main/main.h"
#include "Entity.h"

int Entity::next_id = 1337;

Entity::Entity(std::string name, float x_pos, float y_pos){
    m_Name = name;
    m_XPos = x_pos;
    m_YPos = y_pos;

    m_uid = next_id;
    next_id++;

    printf("Self registering: %s\n", name.c_str());

    Game::entity_manager->RegisterEntity(this);
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

int Entity::GetUID(){
    return m_uid;
}


bool Entity::operator ==(const Entity &other) const{
    return m_uid == other.m_uid;
}


Entity::~Entity(){
    Game::entity_manager->RemoveEntity(this);
}
