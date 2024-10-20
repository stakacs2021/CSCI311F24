// CSCI 311 - Spring 2023
// Lab 4 BST header
// Author: Carter Tillquist

#ifndef BST_H
#define BST_H

#include <memory>
#include <vector>
#include "Node.h"

class BST{
  public:
    std::shared_ptr<Node> root;
    int size;

    BST();
    ~BST();

    std::shared_ptr<Node> search(int);
    std::shared_ptr<Node> search(std::shared_ptr<Node>, int);

    std::shared_ptr<Node> minimum();
    std::shared_ptr<Node> minimum(std::shared_ptr<Node>);
    std::shared_ptr<Node> maximum();
    std::shared_ptr<Node> maximum(std::shared_ptr<Node>);

    void insertValue(int);
    std::shared_ptr<Node> insertValue(std::shared_ptr<Node>, int);
    void deleteValue(int);
    std::shared_ptr<Node> deleteValue(std::shared_ptr<Node>, int);

    bool isBST(std::shared_ptr<Node>);
    bool isBST(std::shared_ptr<Node>, int, int);
  
    void preOrder(std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>&);
    void inOrder(std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>&);
    void postOrder(std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>&);
};

#endif