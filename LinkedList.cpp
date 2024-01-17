#include <iostream>
#include "LinkedList.h"
#include "Student.h"


// TODO: Task 2.2
LinkedList::LinkedList(const LinkedList& ll) {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;

    LLNode* current = ll.getHead();
    while (current != nullptr) {
        add(current->getData());
        current = current->getNext();
    }
}

// TODO: Task 2.1
bool LinkedList::contains(const Student* data) const {
    LLNode *current = this->getHead();
    while(current != nullptr){
        if(current->data == data){
            return true;
        }
       
        current = current -> next;
    }
    return false;
}

// TODO: Task 2.3
LinkedList& LinkedList::operator=(const LinkedList& ll) {
    if (this == &ll) {
        return *this;
    }

    clear();

    LLNode* current = ll.getHead();
    while (current != nullptr) {
        add(current->getData());
        current = current->getNext();
    }

    return *this;
}
