#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h> // For printf when printing list.

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

        void AddElementToStart(T* element){
            LinkedListNode<T>* new_node = new LinkedListNode<T>;
            new_node->prev = nullptr;
            new_node->data = element;

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

        void AddElementToEnd(T* element){
            if(m_NodeCount == 0){
                AddElementToStart(element);
            }else{
                LinkedListNode<T>* new_node = new LinkedListNode<T>;
                new_node->next = nullptr;
                new_node->data = element;

                m_Tail->next = new_node;
                new_node->prev = m_Tail;

                m_Tail = new_node;
                m_NodeCount++;
            }
        }


        T* GetElement(int index){
            //Retrieve the node from the list.
            LinkedListNode<T>* curr = GetNode(index);

            //If the retrieved node is null: the index is out of range.
            if(curr == nullptr){
                return nullptr;
            }

            return curr->data;
        }


        T* RemoveElement(int index){
            //Retrieve the node from the list.
            LinkedListNode<T>* curr = GetNode(index);

            //If the retrieved node is null: the index is out of range.
            if(curr == nullptr){
                return nullptr;
            }

            //Remove the element from the list.
            // If it's the only element.
            if(m_NodeCount == 1){
                m_Head = nullptr;
                m_Tail = nullptr;
            }

            // If it's the first element.
            else if(index == 0){
                m_Head = curr->next;
                m_Head->prev = nullptr;
            }

            // If it's the last element.
            else if(index == m_NodeCount - 1){
                m_Tail = curr->prev;
                m_Tail->next = nullptr;
            }

            // If it's any element in between.
            else{
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            T* data = curr->data;

            //Cleanup memory.
            delete curr;

            m_NodeCount--;

            return data;
        }


        // Uses the == opperator to determine equality.
        T* RemoveElementByValue(T* ElementToRemove){
            LinkedListNode<T>* curr;

            for(int ii = 0; ii < m_NodeCount; ii++){
                curr = GetNode(ii);

                if( *ElementToRemove == *(curr->data) ){
                    return RemoveElement(ii);
                }
            }

            return nullptr;
        }


        void DeleteElement(int index){
            T* data = RemoveElement(index);

            delete data;
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

        void Print( void (*PrintItem)(T* item) ){
            LinkedListNode<T>* curr = m_Head;

            printf("[");
            while(curr != nullptr){
                PrintItem(curr->data);

                if(curr->next != nullptr){
                    printf(", ");
                }

                curr=curr->next;
            }
            printf("]\n");
        }

        private:
            LinkedListNode<T>* m_Head;
            LinkedListNode<T>* m_Tail;
            int m_NodeCount;

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
                    curr_index++;
                }

                return curr;
            }


};


#endif //LINKED_LIST_H
