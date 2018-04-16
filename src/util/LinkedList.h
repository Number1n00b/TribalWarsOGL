#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <class T>
struct LinkedListNode{
	LinkedListNode<T>* next;
	LinkedListNode<T>* prev;

	T* data;
};


template<class T>
class LinkedList
{
	public:
        LinkedList();

		void AddElementToStart(const T& element);
		void AddElementToEnd(const T& element);

        T* GetElement(int index);
		void DeleteElement(int index);
		T* RemoveElement(int index);

		int Length();

		~LinkedList();
	private:
		LinkedListNode<T>* m_Head;
		LinkedListNode<T>* m_Tail;

		LinkedListNode<T>* GetNode(int index);

		int m_NodeCount;
};


#endif //LINKED_LIST_H
