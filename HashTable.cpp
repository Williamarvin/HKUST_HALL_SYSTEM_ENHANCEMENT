#include <climits>
#include "HashTable.h"
#include "Student.h"

using namespace std;

// TODO: Task 4.1
HashTable::HashTable(int size) {
    if(size <= 0){
        return;
    }
    else{
        this->size = size;
        table = new LinkedList[size];
    }
}

// TODO: Task 4.2
HashTable::~HashTable() {
    delete []table;
}

// TODO: Task 4.3
int HashTable::hash(int sid) {
    int64_t intermediateProduct = static_cast<int64_t>(sid) * sid;
    int hash = intermediateProduct % INT_MAX;
    return hash;
}

// TODO: Task 4.4
void HashTable::add(Student* student) {
    if(student){
        int hashResult = hash(student->getSid());
        hashResult %= size;
        if(hashResult < size && hashResult >= 0){
            table[hashResult].add(student);
        }
    } 
}

// TODO: Task 4.5
Student* HashTable::get(int sid) const {
    int hashResult = hash(sid);
    hashResult %= size;
    if(hashResult < size){
        LinkedList& newLinked = table[hashResult];
        
        if(newLinked.getSize() != 0 && hashResult >= 0){
            LLNode* newNode = newLinked.getHead();

            while(newNode != nullptr){
                if(newNode->getData()->getSid() == sid){
                    return newNode->getData();
                } 
                if(newNode->getNext() != nullptr)
                newNode = newNode -> getNext();
            }
        }
    }
    return nullptr;
}

// TODO: Task 4.6
void HashTable::remove(const Student* student) {
    Student* deleteStudent = get(student->getSid());
    if(deleteStudent){
        int hashs = hash(student->getSid());
        hashs %= size;
        if(hashs >= 0)
            if(table[hashs].getHead()!=nullptr)
        table[hashs].remove(deleteStudent);
    }
}

// GIVEN: DO NOT EDIT
void HashTable::printTable() const {
    for (int i = 0; i < size; i++) {
        cout << "table[" << i << "] = " << table[i] << endl;
    }
}