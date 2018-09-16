#include "EntityManager.h"
#include "model/Drawable.h"

EntityManager::EntityManager(){
    m_Entities = new LinkedList<Entity>;
}

void EntityManager::RegisterEntity(Entity* e){
    m_Entities->AddElementToStart(e);
}


void EntityManager::RemoveEntity(Entity* e){
    m_Entities->RemoveElementByValue(e);
}

int EntityManager::NumEntities(){
    return m_Entities->Length();
}

Entity* EntityManager::GetEntityByName(std::string name){
    for(int ii = 0; ii < m_Entities->Length(); ii++){
        Entity* curr = m_Entities->GetElement(ii);

        if (curr->GetName() == name) return curr;
    }

    return nullptr;
}


void EntityManager::DrawAllDrawables(){
    // @TODO have a separate LL for drawable entities, and only draw them
    // @TODO build iterators for the LL and the EM
    for(int ii = 0; ii < m_Entities->Length(); ii++){
        Entity* curr = m_Entities->GetElement(ii);
        ((Drawable*)curr)->Draw();
    }
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
