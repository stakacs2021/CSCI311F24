// CSCI 311 - Spring 2023
// Lab 5 AVLTree header
// Author: Carter Tillquist

#ifndef AVLTREE_H
#define AVLTREE_H

#include <memory>
#include <vector>
#include "AVLNode.h"

class AVLTree{
  public:
    AVLTree();

    std::shared_ptr<AVLNode> getRoot();
    int getSize();

    std::shared_ptr<AVLNode> search(int);

    std::shared_ptr<AVLNode> minimum();
    std::shared_ptr<AVLNode> maximum();

    void insertValue(int);
    void deleteValue(int);
  
    void preOrder(std::shared_ptr<AVLNode>, std::vector<std::shared_ptr<AVLNode>>&);
    void inOrder(std::shared_ptr<AVLNode>, std::vector<std::shared_ptr<AVLNode>>&);
    void postOrder(std::shared_ptr<AVLNode>, std::vector<std::shared_ptr<AVLNode>>&);

  private:
    std::shared_ptr<AVLNode> root;
    int size;

    std::shared_ptr<AVLNode> search(std::shared_ptr<AVLNode>, int);
    std::shared_ptr<AVLNode> minimum(std::shared_ptr<AVLNode>);
    std::shared_ptr<AVLNode> maximum(std::shared_ptr<AVLNode>);
    std::shared_ptr<AVLNode> insertValue(std::shared_ptr<AVLNode>, int);
    std::shared_ptr<AVLNode> deleteValue(std::shared_ptr<AVLNode>, int);

    std::shared_ptr<AVLNode> rebalance(std::shared_ptr<AVLNode>);
    std::shared_ptr<AVLNode> rotateLeft(std::shared_ptr<AVLNode>);
    std::shared_ptr<AVLNode> rotateRight(std::shared_ptr<AVLNode>);
    std::shared_ptr<AVLNode> rotateLeftRight(std::shared_ptr<AVLNode>);
    std::shared_ptr<AVLNode> rotateRightLeft(std::shared_ptr<AVLNode>);
};

#endif