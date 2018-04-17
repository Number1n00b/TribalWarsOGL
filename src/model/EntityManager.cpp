#include "EntityManager.h"

EntityManager::EntityManager(){
    m_Entities = new LinkedList<Entity>;
}

void EntityManager::RegisterEntity(Entity* e){
    m_Entities->AddElementToStart(e);
}


void EntityManager::RemoveEntity(Entity* e){
    m_Entities->RemoveElementByValue(e);
}


void EntityManager::PrintAllEntities(){
    Entity* curr;
    printf("[");
    for(int ii = 0; ii < m_Entities->Length(); ii++){
        curr = m_Entities->GetElement(ii);
        printf("%s|%.0f|%.0f", curr->GetName().c_str(), curr->GetXPos(), curr->GetYPos());
        if(ii != m_Entities->Length() - 1){
            printf(", ");
        }
    }
    printf("]\n");
}


EntityManager::~EntityManager(){
    delete m_Entities;
}
