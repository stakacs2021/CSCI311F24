// CSCI 311 - Spring 2023
// Node Class
// Author: Carter Tillquist

#include "Node.h"

Node::Node(){
  value = 0;
  left = nullptr;
  right = nullptr;
}

Node::Node(int v){
  value = v;
  left = nullptr;
  right = nullptr;
}

Node::~Node(){}