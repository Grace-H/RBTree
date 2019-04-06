/*Class RBTree, implementation of a Red Black Tree
 *This Class can currently add nodes to tree, working on balancing
 *Author: Grace Hunter
 *Date: 26 March 2019
 */

#include <cstring>
#include <iostream>
#include "RBTree.h"

using namespace std;

//constuctor
RBTree::RBTree(){
  head = NULL;
}

//destructor
RBTree::~RBTree(){
  //while(head != NULL){
  //remove(head->data);
  //}
}

//rotate right with given node as root
int RBTree::rotateR(node* root){
  node* pivot = root->left;
  //change root's parent
  //if root is head
  if(root == head){
    head = pivot;
  }
  //if root is right child
  else if(root->parent->right == root){
    root->parent->right = pivot;
  }
  //if root is left child
  else{
    root->parent->left = pivot;
  }
  //pass pivot's right child
  root->left = pivot->right;
  if(root->left != NULL){
    root->left->parent = root;
  }
  //change root to pivot's child
  pivot->parent = root->parent;  
  root->parent = pivot;
  pivot->right = root;
  return 0;
}

//rotate left with given node as root
int RBTree::rotateL(node* root){
  node* pivot = root->right;
  //change root's parent
  //if root is head
  if(root == head){
    head = pivot;
  }
  //if root is right child
  else if(root->parent->right == root){
    root->parent->right = pivot;
  }
  //if root is left child
  else{
    root->parent->left = pivot;
  }
  //pass pivot's left child
  root->right = pivot->left;
  if(root->right != NULL){
    root->right->parent = root;
  }
  //change root to pivot's child
  pivot->parent = root->parent;  
  root->parent = pivot;
  pivot->left = root;
  return 0;
}

//gets grandparent of node*
node* RBTree::getGramp(node* n){
  if(n->parent != NULL){
    return n->parent->parent;
  }
  else{
    return NULL;
  }
}

//returns uncle of given node
node* RBTree::getUncle(node* n){
  //uncle is parent's sibling
  if(n->parent != NULL){
    return getSibling(n->parent);
  }
  else{
    return NULL;
  }
}

//returns the sibling of a given node*
node* RBTree::getSibling(node* n){
  //get sibling
  //if parent exists
  if(n->parent != NULL){
    if(n->parent->right == n){
      return n->parent->left;
    }
    else{
      return n->parent->right;
    }
  }
  //else return NULL
  else{
    return NULL;
  }
}

//returns the parent of a given node*
node* RBTree::getParent(node* n){
  bool found = false;
  node* parent = NULL;
  node* cur = head;
  while(!found){
    if(cur == n){
      found = true;
    }
    else if(cur->data >= n->data){
      parent = cur;
      cur = cur->left;
    }
    else if(cur->data < n->data){
      parent = cur;
      cur = cur->right;
    }
  }
  return parent;
}

//creates node from data value, then calls recursive insert to insert node
int RBTree::insert(int data){
  node* newnode = new node;
  newnode->data = data;
  newnode->left = NULL;
  newnode->right = NULL;
  newnode->color = 'R';
  newnode->parent = NULL;  
  //if head is null, just make it head (case1)
  if(head == NULL){
    head = newnode;
    newnode->color = 'B';
  }
  else{
    insert(newnode, head);
    newnode->parent = getParent(newnode);
    cout << "parent of new node: " << newnode->parent->data << endl;
    //if parent is red & uncle is NULL (black) (case 4)
    if(newnode->parent->color == 'R' && getUncle(newnode) == NULL){
      cout << "parent is red and uncle is NULL" << endl;
    }
    //else if parent is red & uncle is black (case 4)
    else if(newnode->parent->color == 'R' && getUncle(newnode)->color == 'B'){
      cout << "parent is R & uncle is black" << endl;
    
    }
    //else if parent is red & uncle is red (case 3)
    else if(newnode->parent->color == 'R' && getUncle(newnode)->color == 'R'){
      cout << "parent is R, uncle is R" << endl;
      casePRUR(newnode);
    }
  }
  return 0;
}

//determine how to fix tree
int RBTree::repairTree(node* n){

}
//insert case 3: parent & uncle == red
int RBTree::casePRUR(node* n){

}

//inserts a node using recursion
int RBTree::insert(node* newnode, node* current){
  //determine if newnode goes to left or right
  //left
  if(current->data >= newnode->data){
    //if no left child
    if(current->left == NULL){
      current->left = newnode;
    }
    //else move to child
    else{
      insert(newnode, current->left);
    }
  }
  //right
  else if(current->data < newnode->data){
    //if no right child
    if(current->right == NULL){
      current->right = newnode;
    }
    else{
      insert(newnode, current->right);
    }
  }
  return 0;
}

//determines whether data value exists in tree below/including node* cur
//returns 1 if data value does not exist
//returns 0 if data value does exist
int RBTree::contains(int data, node* cur){
  if(head == NULL){
    return 1;
  }
  else if(data == cur->data){
    return 0;
  }
  else if(data <= cur->data && cur->left != NULL){
    return contains(data, cur->left);
  }
  else if(data > cur->data && cur->right != NULL){
    return contains(data, cur->right);
  }
  else{
    return 1;
  }
}

//calls recursive visualize method
int RBTree::visualize(){
  visualize(head, 0);
  return 0;
}

//uses recursion to print tree horizontally:
//left side printed first, lower levels on the right
int RBTree::visualize(node* cur, int level){
  if(head != NULL){
  //if has left child, go left
    if(cur->right != NULL){
      int newlevel = level + 1;
      visualize(cur->right, newlevel);
    }
    //print
    for(int i = level; i > 0; i--){
      cout << "    ";
    }
    cout << cur->data << cur->color << endl;
    //if right child go right
    if(cur->left != NULL){
      int newlevel = level + 1;
      visualize(cur->left, newlevel);
    }
  }
  else{
    cout << "Tree is empty" << endl;
  }
  return 0;
}
