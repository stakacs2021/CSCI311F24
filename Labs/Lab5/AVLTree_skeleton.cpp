// Lab 5 Skeleton - rename it to "AVLTree.cpp"


#include <iostream>
#include <limits.h>
#include "AVLTree.h"
using namespace std;

//do not change anything in the above
//implement the following methods, starting here, do not add new functions

AVLTree::AVLTree(){
}

std::shared_ptr<AVLNode> AVLTree::getRoot(){
  return nullptr;
}

int AVLTree::getSize(){
  return -1;
}

std::shared_ptr<AVLNode> AVLTree::search(int val){
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::search(std::shared_ptr<AVLNode> n, int val){
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::minimum(){
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::minimum(std::shared_ptr<AVLNode> n){
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::maximum(){
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::maximum(std::shared_ptr<AVLNode> n){
  return nullptr;
}

int getHeight(std::shared_ptr<AVLNode> n){
  return -1;
}

int getBalanceFactor(std::shared_ptr<AVLNode> n){
  return -99;
}

void AVLTree::insertValue(int val){
}

std::shared_ptr<AVLNode> AVLTree::insertValue(std::shared_ptr<AVLNode> n, int val){
  return nullptr;
}

void AVLTree::deleteValue(int val){
}

std::shared_ptr<AVLNode> AVLTree::deleteValue(std::shared_ptr<AVLNode> n, int val){
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::rebalance(std::shared_ptr<AVLNode> n){
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::rotateLeft(std::shared_ptr<AVLNode> n){
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::rotateRight(std::shared_ptr<AVLNode> n){
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::rotateLeftRight(std::shared_ptr<AVLNode> n){
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::rotateRightLeft(std::shared_ptr<AVLNode> n){
  return nullptr;
}

void AVLTree::preOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
}

void AVLTree::inOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
}

void AVLTree::postOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
}

