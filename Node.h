/****************************************************************************************************************

Alexander N. Chin | NetID: ANC200008
CS 2337.002 Jason Smith
Project 3 ""Cidercade database" Final Submission
11/6/2021

*****************************************************************************************************************/
#include <iostream>

#ifndef NODE_H
#define NODE_H

template <typename T>
class BinTree;

template <typename T>
class Node {
private:
   T data;
   Node<T>* left;
   Node<T>* right;
   friend class BinTree<T>;
public:
   //overloaded constructors
   Node() {left = nullptr; right = nullptr;}
   Node(T _data) {data=_data; left = nullptr; right = nullptr;}

   //accessors and mutators
   Node<T>* getLeft() const {return left;}
   Node<T>* getRight() const {return right;}
   T& getData() {return data;}
   void setLeft(Node<T>* _left)  {left=_left;}
   void setRight(Node<T>* _right) {right=_right;}
   void setData(T _data) {data=_data;}

   //overloaded relational & insertion operators in line due to template
   friend std::ostream& operator<< (std::ostream& out, Node<T>* node) {
      if (node) {
        out << node->data;
      }
      return out;
   }
   bool operator< (const Node<T>* node) {
      return (data < node->data);
   }
   bool operator> (const Node<T>* node) {
      return (data > node->data);
   }
};
#endif
