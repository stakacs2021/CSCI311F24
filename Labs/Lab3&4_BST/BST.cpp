// Lab 4
// Author: *** Stephan Takacs ***
//
// Requirements for lab4 additions to the bst original file

// you solutions go here
// remember that you do not need to implement all of them
// follow the document to see which ones you need to implement

/*
 1. Implement the minimum method for binary search trees.
 2. Implement the maximum method for binary search trees.
 3. Implement the delete method for binary search trees. When the node to be removed has two children, search the right subtree for a replacement value. Do
 not forget to update the size of the tree when appropriate (including for
 insertion).
 4. Implement the in-order traversal method for binary search trees.
 5. Implement the post-order traversal method for binary search trees.

 */
#include<iostream>
#include <vector>
#include <limits.h>
#include "BST.h"



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

//
std::shared_ptr<Node> BST::minimum(){
    
    return minimum(root);
    
}

std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n){
  //traverse the binary tree to leftmost node to get min
    if(n== nullptr) return nullptr;
    
    while(n->left != nullptr){
        n = n->left;
    }
    return n;
}

std::shared_ptr<Node> BST::maximum(){
    return maximum(root);
}

std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n){
  //traverse through the tree to the rightmost node to find max
    if(n == nullptr) return nullptr;
    
    while (n->right != nullptr) {
        n = n->right;
    }
    return n;
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
/*
 deletion methods per slides 6.02
 if the node has no children, remove it
 if the node has one child replace it with its child
 if the node has two children:
    find minimum node or max node in right/left subtree
    replace this node with its right (or left) child
    change the value of the node to be removed to the value of this node
 */

void BST::deleteValue(int val){
    root = deleteValue(root, val);
}

std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val){
    //value to be deleted is not found
    if(n==nullptr) return n;
    
    if(val < n->value) n->left = deleteValue(n->left, val);
    else if (val > n->value) n->right = deleteValue(n->right, val);
    //now found the node with the required value time to delete
    else{
        //first case: no children, just remove the node
        if(n->left == nullptr && n->right == nullptr) return nullptr;
        
        //case2 1 child either left or right
        else if(n->left == nullptr) return n->right;
        else if(n->right == nullptr) return n->left;
        else {
            //case3, two childright find minimum in right subtree and replace
            std::shared_ptr<Node> minRightSub = minimum(n->right);
            //replace val
            n->value = minRightSub->value;
            //delete old node
            n->right = deleteValue(n->right, minRightSub->value);
            
        }
    }
    return n;
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
/*
 function preOrder(v)
    if v != null
    print(v.value)
    preOrder(left)
    preOrder(right)
 */
void BST::preOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
 //pretty sure for preorder all that has to be done is swapping the left and right nodes and changing gtheir order recursibvely
    if(!n) {
        return;
    }
    order.push_back(n);
    preOrder(n->left, order);
    preOrder(n->right, order);
    
}
/*
 puesdocode per slides 6.02
 function inOrder(v)
    if v != null
    inOrder(left)
    print(v.value)
    inOrder(right)
 */
void BST::inOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
    //visit nodes in ascending order
    //goes left node, node, right node
    if(n == nullptr) return;
    
    inOrder(n->left, order);
    order.push_back(n);
    inOrder(n->right, order);
}


/*
 puesdocode per slides 6.02
 function postOrder(v)
    if v != null
    postOrder(left)
    postOrder(right)
    print(v.value)
 */
void BST::postOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
    //opp of inorder, goes left, right, node
    if(n == nullptr) return;
    
    postOrder(n->left, order);
    postOrder(n->right, order);
    order.push_back(n);
}
