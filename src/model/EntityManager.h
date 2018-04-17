#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "../util/containers/LinkedList.h"

class EntityManager
{
	public:
        EntityManager();

        void RegisterEntity(Entity* e);

		// Designed to only be called by the entity that is asking to be removed
		// itself, or anything with a poitner to it.
		void RemoveEntity(Entity* e);

		void PrintAllEntities();

		~EntityManager();
	private:
        //@TODO later we can make different lists too, eg <Drawable>'s
        LinkedList<Entity>* m_Entities;
};

#endif //ENTITY_MANAGER_H
