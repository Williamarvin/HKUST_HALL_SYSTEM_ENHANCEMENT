#ifndef __BST_IMPLEMENTATION_H__
#define __BST_IMPLEMENTATION_H__

#include "BST.h"
#include "BSTNode.h"
#include "LinkedList.h"

// TODO: Task 3.1
template <typename K>
const BST<K>* BST<K>::find(K key) const {
    if(this->isEmpty()){
        return nullptr;
    }
    else if(this->getKey() > key){
        return this->root->left.find(key);
    }
    else if(this->getKey() < key){
        return this->root->right.find(key);
    }
    else{
        return this;
    }
}

// TODO: Task 3.2
template <typename K>
bool BST<K>::contains(K key, const Student* student) const {
    const BST<K>* newBST = this->find(key);

    if(newBST != nullptr){
        if(newBST->root->value.contains(student)){
            return true;
        }
    }
    return false;
}

// TODO: Task 3.3
template <typename K>
int BST<K>::size() const {
    int i = 0;
    if(root == nullptr){
        return 0;
    }

    i += root->right.size();

    if(root->value.getHead()!= nullptr){
        i += root->value.getSize();
    }

    i += root->left.size();

    return i;
}

// TODO: Task 3.4
template <typename K>
void BST<K>::add(K key, Student* student) {
    if(this->isEmpty()){
        this->root = new BSTNode<K>{key, student};
    }
    else if(key > this->getKey()){
        return this->root->right.add(key,student);
    }
    else if(key < (this->getKey())){
        return this->root->left.add(key, student);
    }
    else if(key == this->getKey()){
        this->root->value.add(student);
    }
}

// TODO: Task 3.5
template <typename K>
LinkedList BST<K>::getAllValues() const {
    LinkedList resultList;

    if (root == nullptr) {
        return resultList;
    }

    resultList.add(root->right.getAllValues());

    resultList.add(root->value);

    resultList.add(root->left.getAllValues());

    return resultList;
}

// TODO: Task 3.6
template <typename K>
const BST<K>* BST<K>::kthLargest(int k) const {
    const BST<K>* answer = nullptr;

    if (root) {
        int rightSize = root->right.getAllValues().getSize();

        if (rightSize >= k) {
            answer = root->right.kthLargest(k);
            return answer;
        }

        if (rightSize + 1 == k) {
            return this;
        }

        answer = root->left.kthLargest(k - rightSize - 1);
    }

    return answer;
}

// TODO: Task 3.7
template <typename K>
void BST<K>::remove(K key) {
    if(isEmpty()){
        return;
    }
    else if(key > this->root->key){
        root->right.remove(key);
    }
    else if(key < this->root->key){
        root->left.remove(key);
    }
    else if(root->right.root != nullptr && root->left.root != nullptr){
        const BST<K> *newNode = root->left.kthLargest(1);
        root->value = newNode->root->value;
        root->key = newNode->root->key;
        root->left.remove(root->key);
    }
    else{
        BSTNode<K> *delete_node = root;
        root = (root->left.isEmpty()) ? root->right.root : root->left.root;
        delete_node->left.root = delete_node->right.root = nullptr;
        delete delete_node;
    }
}

// TODO: Task 3.8
template <typename K>
void BST<K>::remove(K key, const Student* student) {
    const BST<K>* findNode = this->find(key);
    if(findNode == nullptr){
        return;
    }
    else{
        findNode->root->value.remove(student);
        if(findNode->root->value.getSize() == 0){
            this->remove(key);
        }
    }
}
#endif