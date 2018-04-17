#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "../util/containers/LinkedList.h"

class EntityManager
{
	public:
        EntityManager();

        void RegisterEntity(Entity* e);
		void RemoveEntity(Entity* e);

		void PrintAllEntities();

		~EntityManager();
	private:
        //@TODO later we can make different lists too, eg <Drawable>'s
        LinkedList<Entity>* m_Entities;
};

#endif //ENTITY_MANAGER_H
