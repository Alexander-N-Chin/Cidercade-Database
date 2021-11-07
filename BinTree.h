/****************************************************************************************************************

Alexander N. Chin | NetID: ANC200008
CS 2337.002 Jason Smith
Project 3 ""Cidercade database" Final Submission
11/6/2021

*****************************************************************************************************************/

#include "Node.h"
#include <iostream>
#include <queue>
#include <vector>

#ifndef BINTREE_H
#define BINTREE_H

template<typename T>
class BinTree {
private:
    Node<T>* root;
public:
    //constructor
    BinTree() {root = nullptr;}

    //destructor
    ~BinTree();
    void deleteTree(Node<T>* pos);

    //overloaded recursive and helper function headers
    Node<T>* searchNode(T key, Node<T>* pos);
    Node<T>* searchNode(T key);

    Node<T>* searchParent(Node<T>* key, Node<T>* pos);
    Node<T>* searchParent(Node<T>* key);

    void insertNode(Node<T>* key, Node<T>* parent);
    void insertNode(Node<T>* key);

    Node<T>* removeNode(T key);
    Node<T>* removeNode(Node<T>* target, Node<T>* parent);

    void displayInOrder(std::ostream &out, bool isDescending);
    void displayInOrder(std::ostream &out, bool isDescending, Node<T>* pos);

    void displayBreadthFirst(std::ostream &out);
    void displayBreadthFirst(std::ostream &out, int level, Node<T>* pos);

    int getHeight();
    int getHeight(Node<T>* pos);

    std::vector<Node<T>*> vectorizeInOrder();
    std::vector<Node<T>*> vectorizeInOrder(Node<T>* pos);

    //accessors
    Node<T>* getRoot() const {return root;}
};
//default binary tree constructor
template<typename T>
BinTree<T>::~BinTree(){
    deleteTree(root);
}

//binary tree destructor using post order traversal
template<typename T>
void BinTree<T>::deleteTree(Node<T>* pos){
    if (!pos)
        return;
    else{
        deleteTree(pos->right);
        deleteTree(pos->left);
        delete pos;
    }
}

//overloaded recursive helper function
template<typename T>
void BinTree<T>::insertNode(Node<T>* key){
    if (!root) {
        root = key;
        return;
    }
    insertNode(key, root);
}
//Create a new node and add it to the tree
template<typename T>
void BinTree<T>::insertNode(Node<T> *key, Node<T> *parent){
    if (key->data < parent->data){
        if (!parent->left) {
            parent->left = key;
        }
        else {
            insertNode(key, parent->left);
        }
    }
    else{
        if (!parent->right) {
            parent->right = key;
        }
        else {
            insertNode(key, parent->right);
        }
    }
}

//overloaded recursive helper function
template<typename T>
void BinTree<T>::displayInOrder(std::ostream &out, bool isDescending){
    if (root) {
        displayInOrder(out, isDescending, root);
    }
}
//display the tree via in order depth first traversal left to right or right to left (descending)
template<typename T>
void BinTree<T>::displayInOrder(std::ostream &out, bool isDescending, Node<T>* pos){
    if (isDescending) {
        if (!pos)
            return;
        else {
            displayInOrder(out, isDescending, pos->right);
            out << pos << std::endl;
            displayInOrder(out, isDescending, pos->left);
        }
    }
    else {
        if (!pos)
            return;
        else {
            displayInOrder(out, isDescending, pos->left);
            out << pos << std::endl;
            displayInOrder(out, isDescending, pos->right);
        }
    }
}

//overloaded recursive helper function
template<typename T>
int BinTree<T>::getHeight() {
    if (root) {
        return getHeight(root);
    }
    return 0;
}
//gets the height of the tree by adding branch and finding the max of the left and right
template<typename T>
int BinTree<T>::getHeight(Node<T>* pos) {
    if (!pos)
        return 0;
    int leftHeight = getHeight(pos->left);
    int rightHeight = getHeight(pos->right);
    return std::max(leftHeight, rightHeight) + 1;
}

//implementation of breadth first traversal which utilizes the built in queue class to print each level from the top to the bottom
template <typename T>
void BinTree<T>::displayBreadthFirst(std::ostream &out){
    //create queue and push root
    if (!root) {
        return;
    }
    Node<T>* node;
    std::queue<Node<T>*> q;
    q.push(root);
    //while the queue isn't empty, write the node at the front to the file
    while(!q.empty()){
        node = q.front();
        out << node->getData() << std::endl;
        q.pop();

        if(node->getLeft()){
            q.push(node->getLeft());
        }
        if(node->getRight()){
            q.push(node->getRight());
        }
    }

}

//search the tree for a given value and output the node that contains it
template<typename T>
Node<T>* BinTree<T>::searchNode(T key, Node<T>* pos) {
    if (!pos) {
        return nullptr;
    }
    if (key == pos->data) {
        return pos;
    }
    else if (key < pos->data) {
        return searchNode(key, pos->left);
    }
    else {
        return searchNode(key, pos->right);
    }
}
//overloaded recursive helper function
template<typename T>
Node<T>* BinTree<T>::searchNode(T key) {
    if (root)
        return searchNode(key, root);
    return nullptr;
}

template<typename T>
Node<T>* BinTree<T>::searchParent(Node<T>* key, Node<T>* subroot) {
    if (!subroot)
        return nullptr;
    if (key == subroot->left || key == subroot->right)
        return subroot;
    else if (key->data < subroot->data)
        return searchParent(key, subroot->left);
    else
        return searchParent(key, subroot->right);
}
//overloaded recursive helper function
template<typename T>
Node<T>* BinTree<T>::searchParent(Node<T>* key) {
    if (root) {
        return searchParent(key, root);
    }
    return nullptr;
}

//overloaded recursive helper function
template<typename T>
Node<T>* BinTree<T>::removeNode(T key) {
    Node<T>* target = searchNode(key);
    Node<T>* parent = searchParent(target);
    if (!root) {
       return nullptr;
    }
    if (!target) {
       return nullptr;
    }

    return removeNode(target, parent);
}
//Delete the inputted value from the tree via searching for the node and its parent
template<typename T>
Node<T>* BinTree<T>::removeNode(Node<T>* target, Node<T>* parent) {
    if (target == nullptr) {
        return nullptr;
    }
    //remove node with 2 children
    if (target->left && target->right) {
        //find successor
        Node<T>* successor = target->right;
        Node<T>* successorParent = target;
        while (successor->left) {
            successorParent = successor;
            successor = successor->left;
        }

        //swap values
        T temp = target->data;
        target->data = successor->data;
        successor->data = temp;

        //remove successor
        return removeNode(successor, successorParent);
    }
    //remove root
    else if (target == root) {
        if (target->left) {
            root = target->left;
            target->left = nullptr;
        }
        else {
            root = target->right;
            target->right = nullptr;
        }
    }
    //remove a node with one left child
    else if (target->left) {
        if (parent->left == target)
            parent->left = target->left;
        else
            parent->right = target->left;
        target->left = nullptr;
    }
    //remove a node with one right or no child
    else {
        if (parent->right == target)
            parent->right = target->right;
        else
            parent->left = target->right;
        target->right = nullptr;
    }

    return target;
}

//vectorize helper function
template<typename T>
std::vector<Node<T>*> BinTree<T>::vectorizeInOrder(){
    if (root) {
        return vectorizeInOrder(root);
    }
    std::vector<Node<T>*> a;
    return a;
}
//recursively adds all nodes to a vector via in order traversal
template<typename T>
std::vector<Node<T>*> BinTree<T>::vectorizeInOrder(Node<T>* pos){
    std::vector<Node<T>*> vec = {};

    if(pos->left) {
        auto left_side = vectorizeInOrder(pos->left);
        vec.insert(std::end(vec), std::begin(left_side), std::end(left_side));
    }
    vec.push_back(pos);
    if(pos->right) {
        auto right_side = vectorizeInOrder(pos->right);
        vec.insert(std::end(vec), std::begin(right_side), std::end(right_side));
    }
    return vec;

}
#endif
