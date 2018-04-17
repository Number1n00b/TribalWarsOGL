#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

class EntityManager
{
	public:
        EntityManager();

        void registerEntity(Entity* e);


	private:
        //@TODO later we can make different lists too, eg <Drawable>'s
        LinkedList<Entity>* entities;
};

#endif //ENTITY_MANAGER_H
