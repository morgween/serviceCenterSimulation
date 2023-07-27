#ifndef DBL_LIST_H
#define DBL_LIST_H

#include "ListNode.h"

template <typename T>
class DblList {
   public:
    DblList();
    virtual ~DblList();
    int size();
    bool isEmpty();

    // adding
    void addFront(T data);
    void addBack(T data);
    void add(int pos, T data);

    T get(int pos);
    T &at(int pos);

    // removing
    T removeFront();
    T removeBack();
    T remove(int pos);

   private:
    ListNode<T>* m_front;
    ListNode<T>* m_back;
    int m_size;
};

template <typename T>
DblList<T>::DblList() {
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template <typename T>
DblList<T>::~DblList() {
    // todo - free memory - loop through and delete
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template <typename T>
int DblList<T>::size() {
    return m_size;
}

template <typename T>
bool DblList<T>::isEmpty() {
    return (m_size == 0);
}

template <typename T>
void DblList<T>::addFront(T data) {
    ListNode<T>* newNode = new ListNode<T>(data);  // CREATING A NEW NODE
    if (!isEmpty()) {
        newNode->m_next = m_front;  // new nodes next is the old nodes front
        m_front->m_prev = newNode;  // old fronts previous is the new node
    } else {
        m_back = newNode;  // else the list is empty so also change it to point to the back
    }
    m_front = newNode;
    ++m_size;
}

template <typename T>
void DblList<T>::addBack(T data) {
    ListNode<T>* newNode = new ListNode<T>(data);  // CREATING A NEW NODE
    if (!isEmpty()) {
        newNode->m_prev = m_back;  // new nodes previous is the old back node
        m_back->m_next = newNode;  // old backs node next is now the newNode
    } else {
        m_front = newNode;  // else the list is empty so also change it to point to the front
    }
    m_back = newNode;
    ++m_size;
}

template <typename T>
void DblList<T>::add(int pos, T data) {
    if (isEmpty()) {
        addFront(data);
    } else if (pos == 0) {
        addFront(data);
    } else if (pos >= m_size) {
        addBack(data);
    } else {
        ListNode<T>* current = m_front;  // temporary pointer to the front to know where the current node is at aka which node we are visting at that time
        int cPos = 0;
        while (cPos != pos) {
            current = current->m_next;  // loops through each position until we get to the position we are looking for
            ++cPos;
        }  // once we at the position we want do the following below
        ListNode<T>* newNode = new ListNode<T>(data);
        current->m_prev->m_next = newNode;  // make the current nodes previous nodes next pointer and now point it to new Node
        newNode->m_prev = current->m_prev;  // set newNodes previous pointer to point to current nodes
        current->m_prev = newNode;          // set current nodes previous pointer to new node
        newNode->m_next = current;          // set new nodes next pointer to current
        ++m_size;
    }
}

template <typename T>
T DblList<T>::removeFront() {
    // make sure not empty
    T data = m_front->m_data;  // keep track of what the data is...starting from the front
    if (m_size == 1) {
        delete m_front;
        m_front = NULL;
        m_back = NULL;
    } else {
        ListNode<T>* currFront = m_front;  // temp pointer to the current front
        m_front = m_front->m_next;         // change the front to be the old fronts next obj
        m_front->m_prev = NULL;            // change the new fronts previous pointer to null because it is now the new front
        delete currFront;
    }
    --m_size;
    return data;
}

template <typename T>
T DblList<T>::removeBack() {
    // make sure not empty
    T data = m_back->m_data;  // keep track of what the data is...starting from the back
    if (m_size == 1) {
        delete m_back;
        m_front = NULL;
        m_back = NULL;
    } else {
        ListNode<T>* currBack = m_back;
        m_back = m_back->m_prev;  // change the back to be the old backs next obj
        m_back->m_next = NULL;    // change the new backs next pointer to null because it is now the new back
        delete currBack;
    }
    --m_size;
    return data;
}

template <typename T>
T DblList<T>::remove(int pos) {
    // make sure not empty
    T data;
    if (pos == 0) {
        data = removeFront();
    } else if (pos >= m_size - 1) {
        data = removeBack();
    } else {
        ListNode<T>* current = m_front;  // temporary pointer to the front to know where the current node is at aka which node we are visting at that time
        int cPos = 0;
        while (cPos != pos) {
            current = current->m_next;
            ++cPos;
        }
        data = current->m_data;                     // get current nodes data and now set it equal to data
        current->m_prev->m_next = current->m_next;  // go to currents previous nodes next data and set that equal to currents nodes next pointer
        current->m_next->m_prev = current->m_prev;  // go to currents nexts nodes previous pointer and set that equal to current nodes previous pointer
        delete current;
        --m_size;
    }
    return data;
}

template <typename T>
T DblList<T>::get(int pos) {
    // is pos in range, etc.
    ListNode<T>* current = m_front;
    int cPos = 0;
    while (cPos != pos) {
        current = current->m_next;
        ++cPos;
    }  // once you find the node you were looking for return its data
    return current->m_data;
}

template<typename T>
T& DblList<T>::at(int pos) {
    if (pos < 0 || pos > m_size) {
        // Handle the case when the position is out of range
        // Return an appropriate value or throw an exception
        // For simplicity, let's assume T is int and return a reference to a static variable
        static T dummy;
        return dummy;
    }

    ListNode<T>* current = m_front;
    int cPos = 0;
    while (cPos != pos) {
        current = current->m_next;
        ++cPos;
    }
    return current->m_data;
}
#endif