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
        LinkedList(){
            m_Head = nullptr;
            m_Tail = nullptr;

            m_NodeCount = 0;
        }

        void AddElementToStart(const T& element){
            LinkedListNode<T>* new_node = new LinkedListNode<T>;
            new_node->prev = nullptr;

            if(m_NodeCount == 0){
                m_Head = new_node;
                m_Tail = new_node;

                new_node->next = nullptr;
            }else{
                m_Head->prev = new_node;
                new_node->next = m_Head;
                m_Head = new_node;
            }

            m_NodeCount++;
        }

        void AddElementToEnd(const T& element){
            if(m_NodeCount == 0){
                AddElementToStart(element);
            }else{
                LinkedListNode<T>* new_node = new LinkedListNode<T>;
                new_node->next = nullptr;

                m_Tail->next = new_node;
                new_node->prev = m_Tail;

                m_Tail = new_node;
            }

            m_NodeCount++;
        }


        T* GetElement(int index){
            //Retrieve the node from the list.
            LinkedListNode<T>* curr = GetNode(index);

            //If the retrieved node is null: the index is out of range.
            if(curr == nullptr){
                return;
            }

            return curr->data;
        }

        void DeleteElement(int index){
            //Retrieve the node from the list.
            LinkedListNode<T>* curr = GetNode(index);

            //If the retrieved node is null: the index is out of range.
            if(curr == nullptr){
                return;
            }

            //Remove the element from the list.
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            //Cleanup memory.
            delete curr->data;
            delete curr;

            m_NodeCount--;
        }

        RemoveElement(int index){
            //Retrieve the node from the list.
            LinkedListNode<T>* curr = GetNode(index);

            //If the retrieved node is null: the index is out of range.
            if(curr == nullptr){
                return nullptr;
            }

            //Remove the element from the list.
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            T* data = curr->data;

            //Cleanup memory.
            delete curr;

            m_NodeCount--;

            return data;
        }

        int Length(){
            return m_NodeCount;
        }

        ~LinkedList(){
            LinkedListNode<T>* curr = m_Head;
            LinkedListNode<T>* next = nullptr;

            while(curr != nullptr){
                next = curr->next;

                delete curr->data;
                delete curr;

                curr = next;
            }
        }

        private:
        LinkedListNode<T>* m_Head;
        LinkedListNode<T>* m_Tail;

        LinkedListNode<T>* GetNode(int index){
            //Check bounds.
            if(index < 0 || index >= m_NodeCount){
                return nullptr;
            }

            //Traverse to the desired item in the list.
            LinkedListNode<T>* curr = m_Head;
            int curr_index = 0;
            while(curr_index != index){
                curr = curr->next;
            }

            return curr;
        }


        int m_NodeCount;
};


#endif //LINKED_LIST_H
