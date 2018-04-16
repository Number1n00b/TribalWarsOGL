#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

class EntityManager
{
	public:
        EntityManager<T>();

        void registerEntity(Entity* e);

	private:
        //@TODO later we can make this of type <Entities>
        //and also have one for type <drawables>
        LinkedList<Entity>* entities;
};

#endif //ENTITY_MANAGER_H
