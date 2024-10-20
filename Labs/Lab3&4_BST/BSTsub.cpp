// Lab 3 - BST_skeleton.cpp - rename it to BST.cpp
// Author: *** Stephan Takacs ***

#include<iostream>
#include <vector>
#include <limits.h>
#include "BST.h"

// ***do not change the headers***

// you solutions go here
// remember that you do not need to implement all of them
// follow the document to see which ones you need to implement

BST::BST(){
}

BST::~BST(){}

std::shared_ptr<Node> BST::search(int target){
    return search(root, target);
}

std::shared_ptr<Node> BST::search(std::shared_ptr<Node> n, int target){
  //recursively search through the nodes for the target
    //first step is the base case if the node is not found return nothing
    if(n == nullptr){
        return nullptr;
    }
    if(target == n->value){
        return n;
    }
    //search left subtree first
    else if(target < n->value){
        return search(n->left, target);
    }
    //then finally search the right subtree
    else{
        return search(n->right, target);
    }
}

std::shared_ptr<Node> BST::minimum(){
  return nullptr;
}

std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n){
  return nullptr;
}

std::shared_ptr<Node> BST::maximum(){
  return nullptr;
}

std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n){
  return nullptr;
}

void BST::insertValue(int val){
    root = insertValue(root, val);
}
//first part of the assignment insert function
std::shared_ptr<Node> BST::insertValue(std::shared_ptr<Node> n, int val){
    if(n ==  nullptr){
        //create a new node
        std::shared_ptr<Node> new_node;
        new_node = std::shared_ptr<Node>(new Node(val));
        return new_node;
    }
    if (val < n->value){
        n->left = insertValue(n->left, val);
    }
    else if(val > n->value){
        n->right = insertValue(n->right, val);
    }
    //after comparisons then the val would be a duplicate value, no need to insert
    return n;
}

void BST::deleteValue(int val){
}

std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val){
  return nullptr;
}

// helper function to recursively call to  the isBST main function. public
bool BST::isBST(std::shared_ptr<Node> n){
  //public method to check if entire tree is BST recursively
    return isBST(n, INT_MIN, INT_MAX);
}

bool BST::isBST(std::shared_ptr<Node> n, int low, int high){
    
    if(!n) {
        return true;
    }
    if(n->value <= low || n->value >= high){
        return false;
    }
    //pass the nodes back through on right and left side
    return isBST(n->left, low, n->value) && isBST(n->right, n->value, high);
}

void BST::preOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
 //pretty sure for preorder all that has to be done is swapping the left and right nodes and changing gtheir order recursibvely
    if(!n) {
        return;
    }
    order.push_back(n);
    preOrder(n->left, order);
    preOrder(n->right, order);
    
}

void BST::inOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
}

void BST::postOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
}
