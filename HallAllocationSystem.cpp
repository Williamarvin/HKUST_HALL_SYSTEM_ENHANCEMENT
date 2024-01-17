#include "HallAllocationSystem.h"
#include "BST.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Student.h"

// TODO: Task 5.1
HallAllocationSystem::HallAllocationSystem(int totalHallAvailable)
    : studentTable(new HashTable{193}),
      studentQueue(new BST<int>{}),
      studentPendingList(),
      totalHallAvailable(totalHallAvailable) {
}

// TODO: Task 5.2
HallAllocationSystem::~HallAllocationSystem() {
    delete studentTable;
    delete studentQueue;
}

// TODO: Task 5.3
void HallAllocationSystem::allocateHall() {
    if (!studentPendingList.isEmpty()) {
        return;
    }

    LinkedList resultList;
    while (totalHallAvailable > 0 && !studentQueue->isEmpty()) {
        const BST<int>* largestNode = studentQueue->kthLargest(1);

        if (largestNode && !largestNode->isEmpty()) {
            LinkedList allStudents = largestNode->getValue();
            resultList.add(allStudents);

            LLNode* nodePtr = allStudents.getHead();
            while (nodePtr != nullptr) {
                Student* student = nodePtr->getData();
                if (student != nullptr) {
                    student->setStatus(PENDING_ACTION);
                }
                nodePtr = nodePtr->getNext();
            }

            studentQueue->remove(largestNode->getKey());
            totalHallAvailable -= allStudents.getSize();
        } else {
            break;
        }
    }

    studentPendingList.add(resultList);
    if (totalHallAvailable < 0) {
        totalHallAvailable = 0;
    }
}

// TODO: Task 5.4
void HallAllocationSystem::addStudent(Student* student) {
    if(student){
        if(student->getStatus() == QUEUEING){
            if(studentTable->get(student->getSid()) == nullptr && !studentPendingList.contains(student) && !studentQueue->contains(student->getSid(), student)){
                studentTable->add(student);
                studentQueue->add(student->getTotalHallPoints(), student);
            }
            
        }
    }
}

// TODO: Task 5.5
void HallAllocationSystem::removeStudent(const Student* student) {
    if(student){
        studentQueue->remove(student->getTotalHallPoints(), student);
        studentPendingList.remove(student);
        studentTable->remove(student);
    }
}

// TODO: Task 5.6
bool HallAllocationSystem::predict(const Student* student) const {
    if (student) {
        if (studentQueue->contains(student->getTotalHallPoints(), student)) {
            if (studentQueue->kthLargest(totalHallAvailable) != nullptr) {
                int kBiggestPoint = studentQueue->kthLargest(totalHallAvailable)->getKey();
                if (student->getTotalHallPoints() >= kBiggestPoint) {
                    return true;
                }
            }
        }
    }
    return false;
}

// TODO: Task 5.7
void HallAllocationSystem::acceptOffer(Student* student) {
    if(student){
        if(studentPendingList.contains(student)){
            student->setStatus(ACCEPTED);
            studentPendingList.remove(student);
        }
    }
}

// TODO: Task 5.8
void HallAllocationSystem::rejectOffer(Student* student) {
    if(student){
        studentPendingList.remove(student);
        student->setStatus(REJECTED);
        totalHallAvailable+=1;
    }
}

// TODO: Task 5.9
void HallAllocationSystem::acceptAllOffers() {
    LLNode* allStudent = studentPendingList.getHead();
    if(allStudent == nullptr)return;
    while(allStudent!=nullptr){
        LLNode* next = allStudent->getNext();
        acceptOffer(allStudent->getData());
        allStudent = next;
    }   
}

// TODO: Task 5.10
void HallAllocationSystem::rejectAllOffers() {
    LLNode* allStudent = studentPendingList.getHead();
    if(allStudent == nullptr)return;
    while(allStudent!=nullptr){
        LLNode* next = allStudent->getNext();
        rejectOffer(allStudent->getData());
        allStudent = next;
    }
}