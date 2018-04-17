#include "EntityManger.h"

EntityManager::EntityManager(){
    m_Entities = new LinkedList<Entity>;
}

void EntityManager::registerEntity(Entity* e){
    m_Entities->AddElement(e);
}


void EntityManager::removeEntity(Entity* e){
    m_Entities->RemoveElementByValue(e);
}


EntityManager::~EntityManager(){
    delete m_Entities;
}
