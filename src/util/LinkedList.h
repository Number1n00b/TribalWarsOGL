#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template<class T>
class LinkedList
{
	public:
        LinkedList<T>();

        T RemoveElement(index ii);
        T GetElement(index ii);

        void AddElement(index ii);

	private:
        //@TODO later we can make this of type <Entities>
        //and also have one for type <drawables>
        LinkedList<Entity>* entities;
};

#endif //LINKED_LIST_H
