// CSCI 311 - Spring 2023
// Lab 5 - AVL Tree Driver
// Author: Carter Tillquist

#include <iostream>
#include <vector>
#include "AVLTree.h"
using namespace std;

void printVector(const vector<std::shared_ptr<AVLNode>> &v);
void runSearch(std::shared_ptr<AVLTree> T);
void runInsert(std::shared_ptr<AVLTree> T);
void runDelete(std::shared_ptr<AVLTree> T);

/****************************************
 * Simple main to test AVL Tree methods *
 * **************************************/
int main(){
  std::shared_ptr<AVLTree> T(new AVLTree());
  std::shared_ptr<AVLNode> n;

  int operation;
  cin >> operation;

  while (operation > 0){
    vector<std::shared_ptr<AVLNode>> order;
    switch(operation){
      case 1: // search
        cout << "SEARCH FOR ";
        runSearch(T);
        break;
      case 2: // insert
        cout << "INSERT ";
        runInsert(T);
        break;
      case 3: // delete
        cout << "DELETE ";
        runDelete(T);
        break;
      case 4: // preorder
        cout << "PREORDER" << endl;
        T->preOrder(T->getRoot(), order);
        printVector(order);
        break;
      case 5: // inorder
        cout << "INORDER" << endl;
        T->inOrder(T->getRoot(), order);
        printVector(order);
        break;
      case 6: // postorder
        cout << "POSTORDER" << endl;
        T->postOrder(T->getRoot(), order);
        printVector(order);
        break;
      case 7: // minimum
        cout << "MINIMUM" << endl;
        n = T->minimum();
        if (n != nullptr){ cout << n->value << endl; }
        else{ cout << "null" << endl; }
        break;
      case 8: // maximum
        cout << "MAXIMUM" << endl;
        n = T->maximum();
        if (n != nullptr){ cout << n->value << endl; }
        else{ cout << "null" << endl; }
        break;
      case 9: // size
        cout << "SIZE" << endl;
        cout << T->getSize() << endl;
        break;
      default:
        break;
    }
    cin >> operation;
  }

  return 0;
}

/***********************************************************************
 * Print the values of nodes in a vector                               *
 * v - const vector<std::shared_ptr<AVLNode>> & - a vector of AVLNodes *
 * *********************************************************************/
void printVector(const vector<std::shared_ptr<AVLNode>> &v){
  for (int i = 0; i < v.size(); i++){
    cout << v[i]->value << " ";
  }
  cout << endl;
}

/******************************************************************************************************
 * Given an AVL Tree, get a value to search for from the console and apply the AVL Tree search method *
 * T - std::shared_ptr<AVLTree> - an AVLTree Tree                                                     *
 * ****************************************************************************************************/
void runSearch(std::shared_ptr<AVLTree> T){
  int target;
  cin >> target;
  cout << target << endl;
  std::shared_ptr<AVLNode> n = T->search(target);
  if (n){ cout << n->value << endl; }
  else{ cout << "Not found" << endl; }
}

/**************************************************************************
 * Given an AVL Tree, get a value from the console and add it to the tree *
 * T - std::shared_ptr<AVLTree> - an AVL Tree                             *
 * ************************************************************************/
void runInsert(std::shared_ptr<AVLTree> T){
  int newVal;
  cin >> newVal;
  cout << newVal << endl;
  T->insertValue(newVal);
}

/********************************************************************************************
 * Given an AVL Tree, get a value from the console and remove it from the tree if it exists *
 * T - std::shared_ptr<AVLTree> - an AVL Tree                                               *
 * ******************************************************************************************/
void runDelete(std::shared_ptr<AVLTree> T){
  int remove;
  cin >> remove;
  cout << remove << endl;
  T->deleteValue(remove);
}