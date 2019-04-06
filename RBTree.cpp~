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

//returns true if all trees below node have same black height
/*bool isBalanced(node* cur){

}*/

//gets grandparent of node*
node* RBTree::getGramp(node* n){
  node* parent = getParent(n);
  if(parent != NULL){
    parent = getParent(parent);
  }
  return parent;
}

//returns uncle of given node
node* RBTree::getUncle(node* n){
  node* parent = getParent(n);
  
  //uncle is parent's sibling
  if(parent != NULL){
    return getSibling(parent);
  }
  else{
    return NULL;
  }
}

//returns the sibling of a given node*
node* RBTree::getSibling(node* n){
  //get parent
  node* parent = getParent(n);

  //get sibling
  //if parent exists
  if(parent != NULL){
    if(parent->right == n){
      return parent->left;
    }
    else{
      return parent->right;
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
  //if head is null, just make it head
  if(head == NULL){
    head = newnode;
  }
  else{
    insert(newnode, head);
    node* parent = getParent(newnode);
    cout << "parent of new node: " << parent->data << endl;
  }
  return 0;
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
