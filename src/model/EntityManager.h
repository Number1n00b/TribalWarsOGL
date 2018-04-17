#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"

class EntityManager
{
	public:
        EntityManager();

        void registerEntity(Entity* e);
		void removeEntity(Entity* e);

		~EntityManager();
	private:
        //@TODO later we can make different lists too, eg <Drawable>'s
        LinkedList<Entity>* m_Entities;
};

#endif //ENTITY_MANAGER_H
