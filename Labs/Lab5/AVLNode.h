// CSCI 311 - Spring 2023
// AVLNode header
// Author: Carter Tillquist

#ifndef AVLNODE_H
#define AVLNODE_H

#include <memory>

class AVLNode{
  public:
    int value;
    int height;
    int balanceFactor;
    std::shared_ptr<AVLNode> left;
    std::shared_ptr<AVLNode> right;
    std::shared_ptr<AVLNode> parent; // you are not required to update parent nodes but you may use them if you want
    
    AVLNode();
    AVLNode(int);
};

#endif