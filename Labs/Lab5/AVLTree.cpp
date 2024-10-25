// Lab 5 Skeleton - rename it to "AVLTree.cpp"


#include <iostream>
#include <limits.h>
#include <algorithm>
#include <memory>
#include "AVLNode.h"
#include "AVLTree.h"
using namespace std;

//do not change anything in the above
//implement the following methods, starting here, do not add new functions
//Stephan Takacs


AVLTree::AVLTree(){
    //need to intialize the first node with nullpointer
    root = nullptr;
    size = 0;
}

std::shared_ptr<AVLNode> AVLTree::getRoot(){
    return root;
}

int AVLTree::getSize(){
  //need to return the size variable
    return size;
}

std::shared_ptr<AVLNode> AVLTree::search(int val){
    //point to true rt and get searching
    return search(root, val);
}

std::shared_ptr<AVLNode> AVLTree::search(std::shared_ptr<AVLNode> n, int val){

    if(n == nullptr || n->value == val) return n;

    if(val < n->value) return search(n->left, val);

    else return search(n->right, val);
}

//using bst method
std::shared_ptr<AVLNode> AVLTree::minimum(){
  return minimum(root);
}

std::shared_ptr<AVLNode> AVLTree::minimum(std::shared_ptr<AVLNode> n){
    if(n == nullptr) return nullptr;

    //loop until null
    while(n->left != nullptr) n = n->left;
    return n;
}

std::shared_ptr<AVLNode> AVLTree::maximum(){
    return maximum(root);
}

std::shared_ptr<AVLNode> AVLTree::maximum(std::shared_ptr<AVLNode> n){
    if(n==nullptr) return nullptr;

    //loop until null
    while(n->right != nullptr) n = n->right;

    return n;

}

int getHeight(std::shared_ptr<AVLNode> n){
    if(n == nullptr) return -1;
    else return n->height;
}

/*
 per lecture slides balance factor is left - right heights
 */
int getBalanceFactor(std::shared_ptr<AVLNode> n){
    if(n == nullptr) return 0;
    else return getHeight(n->left) - getHeight(n->right);
}

/*
 puesdocode from lecture slides:
 fu n ction i n s e r t ( n , v a l )
 i f n == n u l l
 n =n ew n od e(val)
 return n
 e l s e i f v a l < n .valu e
 n . l e f t = i n s e r t ( n . l e f t , v a l u e ) e l s e
 i f v a l > n.value
 n . r i g h t = i n s e r t ( n . r i g h t , v a l )
 n .h eigh t = m a x ( n . l e f t . h e i g h t , n . r i g h t . h e i g h t ) + 1
 n.balanceFactor = n . r i g h t . h e i g h t - n . l e f t . h e i g h t n =
 reb alan ce(n )
 return n
 */
//void func to call insert val and reset root
void AVLTree::insertValue(int val){
    root = insertValue(root, val);
    if(root != nullptr) root->parent = nullptr;

}


std::shared_ptr<AVLNode> AVLTree::insertValue(std::shared_ptr<AVLNode> n, int val){
    if(n == nullptr){
        size++;
        //now using shared_ptr to make it consistent with the rest of the class
        return std::shared_ptr<AVLNode>(new AVLNode (val));
    }
    else if(val < n->value){
        n->left = insertValue(n->left, val);
        n->left->parent = n;
    }
    else if(val > n->value){
        n->right = insertValue(n->right, val);
        n->right->parent = n;
    }
    else{
        //dupe handler
        return n;
    }

    int leftHeight, rightHeight;
    if(n->left != nullptr) leftHeight = n->left->height;
    else  leftHeight = - 1;

    if(n->right != nullptr) rightHeight = n->right->height;
    else rightHeight = -1;

    n->height = std::max(leftHeight, rightHeight) + 1;
    n->balanceFactor = rightHeight - leftHeight;

    //rebalance the node
    n = rebalance(n);
    return n;



}

/*
 puesdocode from lecture slides:
 fu n ction d e l e t e ( n , v a l )
 i f n ! = n u l l
 i f v a l < n .valu e
 n . l e f t = d e l e t e ( n . l e f t , v a l )
 e l s e i f v a l > n .valu e
 n . r i g h t = d e l e t e ( n . r i g h t , v a l )
 e l s e i f n . l e f t == n u l l and n . r i g h t == n u l l
 n = n u l l
 e l s e i f n . l e f t == n u l l
 n = n . r i g h t
 e l s e i f n . r i g h t == n u l l
 n = n . l e f t
 e l s e
 m = minimum(n.right)
 n .va lu e = m.value
 n . r i g h t = d e l e t e ( n . r i g h t , m.value)
 _______________continued___________
 function d e l e t e ( n , v a l )
 / / . . . continued . . .
 i f n == n u l l
 return n
 n.height = m a x ( n . l e f t . h e i g h t , n . r i g h t . h e i g h t ) + 1
 n.balanceFactor = n . r i g h t . h e i g h t - n . l e f t . h e i g h t
 n = reb alan ce(n )
 return n
 */
 //void func to call insert val and reset root
void AVLTree::deleteValue(int val){
    root = deleteValue(root, val);
    if(root != nullptr) root->parent = nullptr;
}

std::shared_ptr<AVLNode> AVLTree::deleteValue(std::shared_ptr<AVLNode> n, int val){
    if(n != nullptr){
        if(val < n->value){
            n->left = deleteValue(n->left, val);
            if(n->left != nullptr){
                n->left->parent = n;
            }
        }
        else if(val > n->value){
            n->right = deleteValue(n->right, val);
            if(n->right != nullptr){
                n->right->parent = n;
            }
        }
        else{
            //found node to delete
            //no children
            if(n->left == nullptr && n->right == nullptr){
                n = nullptr;
                size--;
            }
            //right child 1 child
            else if(n->left == nullptr){
                std::shared_ptr<AVLNode> temp = n->right;
                temp->parent = n->parent;
                n = temp;
                size--;
            }
            //left child 1 child
            else if(n->right == nullptr){
                std::shared_ptr<AVLNode> temp = n->left;
                temp->parent = n->parent;
                n = temp;
                size--;
            }
            //two children
            else{
                std::shared_ptr<AVLNode> m = minimum(n->right);
                n->value = m->value;
                n->right = deleteValue(n->right, m->value);
                if(n->right != nullptr){
                    n->right->parent = n;
                }
            }
        }
    }

    if(n == nullptr){
        return n;
    }

    //now reset the height and balance factor
    int leftHeight, rightHeight;

    if(n->left != nullptr){
        leftHeight = n->left->height;
    } else {
        leftHeight = -1;
    }
    if(n->right != nullptr){
        rightHeight = n->right->height;
    } else {
        rightHeight = -1;
    }
    n->height = std::max(leftHeight, rightHeight) + 1;
    n->balanceFactor = rightHeight - leftHeight;

    //now rebalance the node
    n = rebalance(n);
    return n;
}

/*
 puesdocode from lecture slides:
 fu n ct io n reb alan ce(v)
 i f v.balanceFactor == 2 and
 v . r i g h t . b a l a n c e F a c t o r >= 0
 return r o t a t e L e f t ( v )
 e l s e i f v.balanceFactor == 2 and
 v . r i g h t . b a l a n c e F a c t o r < 0
 return r o t a t e R i g h t L e f t ( v )
 e l s e i f v.balanceFactor == - 2 and
 v . l e f t . b a l a n c e F a c t o r <= 0
 return r o t a t e R i g h t ( v )
 e l s e i f v.balanceFactor == - 2 and
 v . l e f t . b a l a n c e F a c t o r > 0
 return r o t a t e L e f t R i g h t ( v )
 e l s e
 return v
 */
std::shared_ptr<AVLNode> AVLTree::rebalance(std::shared_ptr<AVLNode> n){

    int leftHeight, rightHeight;
    if(n->left != nullptr) leftHeight = n->left->height;
    else leftHeight = -1;

    if(n->right != nullptr) rightHeight = n->right->height;
    else rightHeight = -1;

    n->height = std::max(leftHeight, rightHeight) + 1;
    n->balanceFactor = rightHeight - leftHeight;

    if(n->balanceFactor == 2){
        if(n->right != nullptr){
            if(n->right->balanceFactor >= 0){
                return rotateLeft(n);
            }
            else if(n->right->balanceFactor < 0){
                return rotateRightLeft(n);
            }
        }
    }
    else if(n->balanceFactor == -2){
        if(n->left != nullptr){
            if(n->left->balanceFactor <= 0){
                return rotateLeft(n);
            }
            else if(n->left->balanceFactor > 0){
                return rotateLeftRight(n);
            }
        }

    }
    return n;
}

/*
 puesdocode copied from slides 7.02:
 fu n ct io n r o t a t e L e f t ( y )
 x = y . r i g h t
 y . r i g h t = x . l e f t
 updateHeight(y)
 updateBF(y)
 x . l e f t = y
 updateHeight(x)
 updateBF(x)
 return x
 6 / 33

 */
std::shared_ptr<AVLNode> AVLTree::rotateLeft(std::shared_ptr<AVLNode> n){
    std::shared_ptr<AVLNode> x = n->right;
    n->right = x->left;
    if(x->left != nullptr) x->left->parent = n;

    //now updating height and bf of n
    int nLeftHeight, nRightHeight;
    if(n->left != nullptr) nLeftHeight = n->left->height;
    else nLeftHeight = -1;

    if(n->right != nullptr) nRightHeight = n->right->height;
    else nRightHeight = -1;

    n->height = std::max(nLeftHeight, nRightHeight) + 1;
    n->balanceFactor = nRightHeight - nLeftHeight;

    x->left = n;
    n->parent = x;

    int xLeftHeight, xRightHeight;
    if(x->left != nullptr) xLeftHeight = x->left->height;
    else xLeftHeight = -1;

    if(x->right != nullptr) xRightHeight = x->right->height;
    else xRightHeight = -1;

    x->height = std::max(xLeftHeight, xRightHeight) + 1;
    x->balanceFactor = xRightHeight - xLeftHeight;

    x->parent = nullptr;

    return x;
}
/*
 Puesdocode copied from slides 7.02:
 function rotateRight ( y )
 x = y.left
 y . left = x.right
 updateHeight(y)
 updateBF(y)
 x.right = y
 updateHeight(x)
 updateBF(x)
 return x
 */
std::shared_ptr<AVLNode> AVLTree::rotateRight(std::shared_ptr<AVLNode> n){
    std::shared_ptr<AVLNode> x = n->left;
    n->left = x->right;
    if(x->right != nullptr) x->right->parent = n;

    int nLeftHeight, nRightHeight;
    if(y->left != nullptr) nLeftHeight = n->left->height;
    else nLeftHeight = -1;

    if(y->right != nullptr) nRightHeight = n->right->height;
    else nRightHeight = -1;

    n->height = std::max(nLeftHeight, nRightHeight) + 1;
    n->balanceFactor = nRightHeight - nLeftHeight;

    x->right = n;
    n->parent = x;

    int xLeftHeight, xRightHeight;
    if(x->left != nullptr) nLeftHeight = x->left->height;
    else xLeftHeight = -1;

    if(x->right != nullptr) xRightHeight = x->right->height;
    else xRightHeight = -1;

    x->height = std::max(xLeftHeight, xRightHeight) + 1;
    x->balanceFactor = xRightHeight - xLeftHeight;

    x->parent = nullptr;

    return x;
}

/*
puesdocode from lecture slides:
 fu n ction r o t a t e L e f t R i g h t ( y )
 / / rotate l e f t
 x = y . l e f t
 z = x . r i g h t
 x . r i g h t = z . l e f t
 updateHeight(x)
 updateBF(x)
 z . l e f t = x
 y . l e f t = z
 / / rotate r i g h t
 y . l e f t = z . r i g h t
 updateHeight(y)
 updateBF(y)
 z . r i g h t = y
 updateHeight(z)
 updateBF(z)
 return z
 */
std::shared_ptr<AVLNode> AVLTree::rotateLeftRight(std::shared_ptr<AVLNode> n){
    //new nodes
    std::shared_ptr<AVLNode> x = n->left;
    std::shared_ptr<AVLNode> z = x->right;

    //rotate left
    x->right = z->left;
    if(z->left != nullptr) z->left->parent = x;

    //update height and bf of x
    int xLeftHeight, xRightHeight;
    if(x->left != nullptr) xLeftHeight = x->left->height;
    else xLeftHeight = -1;


    if(x->right != nullptr) xRightHeight = x->right->height;
    else xRightHeight = -1;

    x->height = std::max(xLeftHeight, xRightHeight) + 1;
    x->balanceFactor = xRightHeight - xLeftHeight;


    z->left = x;
    x->parent = z;
    n->left = z;
    z->parent = n;

    //rotate right
    n->left = z->right;
    if(z->right != nullptr) z->right->parent = n;


    //update height and bf of n
    int nLeftHeight, nRightHeight;
        if(n->left != nullptr) nLeftHeight = n->left->height;
        else nLeftHeight = -1;

    if(n->right != nullptr) nRightHeight = n->right->height;
    else nRightHeight = -1;


    n->height = std::max(nLeftHeight, nRightHeight) + 1;
    n->balanceFactor = nRightHeight - nLeftHeight;

    z->right = n;
    n->parent = z;


    int zLeftHeight, zRightHeight;
    if(z->left != nullptr) zLeftHeight = z->left->height;
    else zLeftHeight = -1;

    if(z->right != nullptr) zRightHeight = z->right->height;
    else zRightHeight = -1;

    z->height = std::max(zLeftHeight, zRightHeight) + 1;
    z->balanceFactor = zRightHeight - zLeftHeight;

    z->parent = nullptr;

    return z;

}

/*
 puesdocode from lecture slides:
 fu n ct io n r o t a t e R i g h t L e f t ( y )
 / / rotate r i g h t
 x = y . r i g h t
 z = x . l e f t
 x . l e f t = z . r i g h t
 updateHeight(x)
 updateBF(x)
 z . r i g h t = x
 y . r i g h t = z
 / / rotate l e f t
 y . r i g h t = z . l e f t
 updateHeight(y)
 updateBF(y)
 z . l e f t = y
 updateHeight(z)
 updateBF(z)
 return z
 */
std::shared_ptr<AVLNode> AVLTree::rotateRightLeft(std::shared_ptr<AVLNode> n){
    //rtoate right
    std::shared_ptr<AVLNode> x = n->right;
    std::shared_ptr<AVLNode> z = x->left;

    x->left = z->right;
    if(z->right != nullptr) z->right->parent = x;

    int xLeftHeight, xRightHeight;
    if(x->left != nullptr)xLeftHeight = x->left->height;
    else xLeftHeight = -1;

    if(x->right != nullptr) xRightHeight = x->right->height;
    else xRightHeight = -1;

    x->height = std::max(xLeftHeight, xRightHeight) + 1;
    x->balanceFactor = xRightHeight - xLeftHeight;

    z->right = x;
    x->parent = z;
    n->right = z;
    z->parent = n;

    //rotate left
    n->right = z->left;
    if(z->left != nullptr) z->left->parent = n;

    //update n bf and height
    int nLeftHeight, nRightHeight;
    if(n->left != nullptr) nLeftHeight = n->left->height;
    else nLeftHeight = -1;

    if(n->right != nullptr) nRightHeight = n->right->height;
    else nRightHeight = -1;

    n->height = std::max(nLeftHeight, nRightHeight) + 1;
    n->balanceFactor = nRightHeight - nLeftHeight;

    //move down
    z->left = n;
    n->parent = z;

    //z bf and h update
    int zLeftHeight, zRightHeight;
    if(z->left != nullptr) zLeftHeight = z->left->height;
    else zLeftHeight = -1;

    if(z->right != nullptr) zRightHeight = z->right->height;
    else zRightHeight = -1;

    z->height = std::max(zLeftHeight, zRightHeight) + 1;
    z->balanceFactor = zRightHeight - zLeftHeight;

    z->parent = nullptr;

    return z;

}
/*
 from bst slides 6
 Root->Left->Right
 * The order they were added to the tree.*
 function preOrder(v)
 if v != null
 print(v.value)
 preOrder(left)
 preOrder(right)
 */
void AVLTree::preOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
    if(n != nullptr){
        order.push_back(n);
        preOrder(n->left, order);
        preOrder(n->right, order);
    }
}

/*
 from bst slides:
 Left -> Root -> Right
 function inOrder(v)
 if v != null
 inOrder(left)
 print(v.value)
 inOrder(right)
 */
void AVLTree::inOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
    if(n != nullptr){
        inOrder(n->left, order);
        order.push_back(n);
        inOrder(n->right, order)
    }
}

/*
 from bst slides:
 Left -> Right -> Root
 function postOrder(v)
 if v != null
 postOrder(left)
 postOrder(right)
 print(v.value)
 */
void AVLTree::postOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
    if(n != nullptr){
        postOrder(n->left, order);
        postOrder(n->right, order);
        order.push_back(n);
    }
}
