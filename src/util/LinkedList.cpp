#include <stdlib.h>
#include "LinkedList.h"

template<class T>
LinkedList<T>::LinkedList(){
    m_Head = nullptr;
    m_Tail = nullptr;

    m_NodeCount = 0;
}

template<class T>
/**
* This function will remove the element from the list, but not handle the
* memory of the item itself. (Use DeleteElement for that).
*/
T* LinkedList<T>::RemoveElement(int index){
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

template<class T>
void LinkedList<T>::DeleteElement(int index){
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


template<class T>
T* LinkedList<T>::GetElement(int index){
    //Retrieve the node from the list.
    LinkedListNode<T>* curr = GetNode(index);

    //If the retrieved node is null: the index is out of range.
    if(curr == nullptr){
        return;
    }

    return curr->data;
}


template<class T>
void LinkedList<T>::AddElementToStart(const T& element){
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


template<class T>
void LinkedList<T>::AddElementToEnd(const T& element){

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


template<class T>
int LinkedList<T>::Length(){
    return m_NodeCount;
}

template<class T>
LinkedList<T>::~LinkedList(){
    LinkedListNode<T>* curr = m_Head;
    LinkedListNode<T>* next = nullptr;

    while(curr != nullptr){
        next = curr->next;

        delete curr->data;
        delete curr;

        curr = next;
    }
}

template<class T>
LinkedListNode<T>* LinkedList<T>::GetNode(int index){
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
