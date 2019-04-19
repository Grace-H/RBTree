/*Class RBTree, implementation of a Red-Black Tree
 *Cases for insertion and deletion were learned from https://en.wikipedia.org/wiki/Red-Black_Tree
 *Author: Grace Hunter
 *Date: 19 April 2019
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

//remove node
int RBTree::remove(int data){
  //get node with value
  node* found = locate(data, head);
  cout << "found: " << found->data << endl;
  //find node to delete and child
  node* child;
  node* todelete = found;
  if(todelete->left != NULL){
    todelete = todelete->left;
    while(todelete->right != NULL){
      todelete = todelete->right;
    }
    child = todelete->left;
    found->data = todelete->data;
  }
  else{
    child = todelete->right;
  }
  cout << "todelete: " << todelete->data << endl;
  cout << "found: " << found->data << endl;
  //cout << "child: " << child->data << endl;

  //seg fault
  //if todelete is red
  if(todelete->color == 'R'){
    //change child & parent pointers
    if(todelete->parent->left == todelete){
      todelete->parent->left = child;
    }
    else{
      todelete->parent->right = child;
    }
    if(child != NULL){
      child->parent = todelete->parent;
    }
    
    //paint node black
    if(child != NULL){
      child->color = 'B';
    }
    delete todelete;
  }
  else if(todelete->parent != NULL){
    if(todelete->parent->color == 'R'){
      //change child & parent pointers
      if(todelete->parent->left == todelete){
	todelete->parent->left = child;
      }
      else{
	todelete->parent->right = child;
      }
      if(child != NULL){
	child->parent = todelete->parent;
      }
    
      //paint node black
      if(child != NULL){
	child->color = 'B';
      }
      delete todelete;
    }
  }
  
  //if todelete is black-->child is now doubleblack
  else{
    cout << "todelete is black" << endl;
    //get family members in case child is NULL
    node* parent = todelete->parent;
    node* sibling;
    if(parent->right == todelete){
      sibling = parent->left;
    }
    else{
      sibling = parent->right;
    }
    
    //change child & parent pointers
    if(parent != NULL){
      if(todelete->parent->left == todelete){
	todelete->parent->left = child;
      }
      else{
	todelete->parent->right = child;
      }
    }
    if(child != NULL){
      child->parent = todelete->parent;
    }
    delete todelete;

    //CHILD IS DOUBLE BLACK
    //begin cases
    rcasePNULL(child, parent, sibling);
  }
  return 0;
}

int RBTree::rcasePNULL(node* n, node* p, node* s){
  if(p != NULL){
    rcaseSR(n, p, s);
  }
  else{
    head = n;
  }
  return 0;
}

//remove case 2: sibling is red, calls case 3
int RBTree::rcaseSR(node* n, node* p, node* s){
  if(s != NULL){
    if(s->color == 'R'){
      p->color = 'R';
      s->color = 'B';
      if(p->left == n){
	rotateL(p);
      }
      else{
	rotateR(p);
      }
    }
  }
  rcasePBSBsBsB(n, p, getSibling(n));
  return 0;
}

//remove case 3: sibling, parent, and sibling's children are black
int RBTree::rcasePBSBsBsB(node* n, node* p, node* s){
  if(p->color == 'B'){
    if(s != NULL){
      if(s->color == 'B'){
	if(s->left == NULL){
	  if(s->right == NULL){
	    s->color = 'R';
	    rcasePNULL(p, p->parent, getSibling(p));
	  }
	  else if(s->right->color == 'B'){
	    s->color = 'R';
	    rcasePNULL(p, p->parent, getSibling(p));
	  }
	  else{
	    rcasePRSBsBsB(n, p, s);
	  }
	}
	else if(s->right == NULL && s->left->color == 'B'){
	  s->color = 'R';
	  rcasePNULL(p, p->parent, getSibling(p));
	}
	else if(s->right->color == 'B' && s->left->color == 'B'){
	  s->color = 'R';
	  rcasePNULL(p, p->parent, getSibling(p));
	}
	else{
	  rcasePRSBsBsB(n, p, s);
	}
      }
      else{
	rcasePRSBsBsB(n, p, s);
      }
    }
    else{
      rcasePRSBsBsB(n, p, s);
    }
  }
  else{
    rcasePRSBsBsB(n, p, s);
  }
  return 0;
}

//remove case 4: parent is red, but s and s's children are black
int RBTree::rcasePRSBsBsB(node* n, node* p, node* s){
  if(p->color == 'R'){
    if(s != NULL){
      if(s->color == 'B'){
	if(s->left == NULL){
	  if(s->right == NULL){
	    s->color = 'R';
	    p->color = 'B';
	  }
	  else if(s->right->color == 'B'){
	    s->color = 'R';
	    p->color = 'B';
	  }
	  else{
	    rcaseSBsRsBNL(n, p, s);
	  }
	}
	else if(s->right == NULL && s->left->color == 'B'){
	  s->color = 'R';
	  p->color = 'B';
	}
	else if(s->right->color == 'B' && s->left->color == 'B'){
	  s->color = 'R';
	  p->color = 'B';
	}
	else{
	  rcaseSBsRsBNL(n, p, s);
	}
      }
      else{
	rcaseSBsRsBNL(n, p, s);
      }
    }
    else{
      rcaseSBsRsBNL(n, p, s);
    }
  }
  else{
    rcaseSBsRsBNL(n, p, s);
  }
  return 0;
}


//case 5: sibling is black, sibling's left child is red,
//sibling's right child is black, and n is left child of parent
int RBTree::rcaseSBsRsBNL(node* n, node* p, node* s){
  cout << "case5" << endl;
  return 0;
}

//case 6: sibling is black, sibling's right child is red, node is left child
int RBTree::rcaseSBsrRNL(node* n, node* p, node* s){
  cout << "case6" << endl;
  return 0;
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
    //if parent is red & uncle is NULL (black) (case 4)
    if(newnode->parent->color == 'R' && getUncle(newnode) == NULL){
      icasePRUB(newnode);
    }
    //else if parent is red & uncle is black (case 4)
    else if(newnode->parent->color == 'R' && getUncle(newnode)->color == 'B'){
      icasePRUB(newnode);
    }
    //else if parent is red & uncle is red (case 3)
    else if(newnode->parent->color == 'R' && getUncle(newnode)->color == 'R'){
      icasePRUR(newnode);
    }
  }
  return 0;
}

//determine how to fix tree
int RBTree::repairTree(node* n){
  //if node is head (case 1)
  if(n == head){
    n->color = 'B';
  }
  //if parent is black (case 2)
  else if(n->parent->color == 'B'){
    return 0;
  }
  //if parent is red & uncle is NULL (black) (case 4)
  else if(n->parent->color == 'R' && getUncle(n) == NULL){
    icasePRUB(n);
  }
  //else if parent is red & uncle is black (case 4)
  else if(n->parent->color == 'R' && getUncle(n)->color == 'B'){
    icasePRUB(n);
  }
  //else if parent is red & uncle is red (case 3)
  else if(n->parent->color == 'R' && getUncle(n)->color == 'R'){
    icasePRUR(n);
  }
  return 0;
}

//insert case 3: parent & uncle == red
int RBTree::icasePRUR(node* n){
  n->parent->color = 'B';
  getUncle(n)->color = 'B';
  getGramp(n)->color = 'R';
  repairTree(getGramp(n));
  return 0;
}

//insert case 4: parent == red & uncle == black
int RBTree::icasePRUB(node* n){
  //check if node is inside tree
  //if node is parent is left child and node is right child
  if(getGramp(n)->left == n->parent && n->parent->right == n){
    rotateL(n->parent);
    n = n->left;
  }
  //else if node is right child and parent is left child
  else if(getGramp(n)->right == n->parent && n->parent->left == n){
    rotateR(n->parent);
    n = n->right;
  }

  //rotate tree
  if(n->parent->left == n){
    rotateR(getGramp(n));
  }
  else{
    rotateL(getGramp(n));
  }

  //change colors
  n->parent->color = 'B';
  getSibling(n)->color = 'R';
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


//finds and returns a node in the tree using recursion
node* RBTree::locate(int data, node* cur){
  if(cur == NULL){
    return NULL;
  }
  else if(data == cur->data){
    return cur;
  }
  else if(data <= cur->data){
    locate(data, cur->left);
  }
  else if(data > cur->data){
    locate(data, cur->right);
  }
}

//prints out if given number exists in tree
int RBTree::search(int data){
  int exists = contains(data, head);
  if(exists == 0){
    cout << "Exists: " << data << endl;
  }
  else{
    cout << "Does not exist: " << data << endl;
  }
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
