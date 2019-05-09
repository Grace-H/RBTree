/*Class RBTree, implementation of a Red-Black Tree
 *Cases for insertion and deletion were learned from https://en.wikipedia.org/wiki/Red-Black_Tree
 *Author: Grace Hunter
 *Date: 9 May 2019
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
  while(head != NULL){
    remove(head->data);
  }
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

//remove node with given data
int RBTree::remove(int data){
  //get node with value
  node* found = locate(data, head);
  //cout << "found: " << found->data << endl;
  //find node to delete and child
  if(found != NULL){
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
    
    //if todelete is black-->child is now doubleblack
    else if(todelete->color == 'B'){
      //if todelete is only node in tree
      if(todelete == head && todelete->parent == NULL && todelete->left == NULL && todelete->right == NULL){
	head = NULL;
	delete todelete;
      }
      //if todelete is head and has no left child
      else if(todelete == head && todelete->parent == NULL && todelete->left == NULL){
	child->parent = NULL;
	head = child;
	child->color = 'B';
	delete todelete;
      }
      //if todelete has no parent but has a left child
      else if(todelete->parent == NULL){
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
	if(child == NULL){
	  rcasePNULL(parent, parent->parent, getSibling(parent));
	}
	else if(child->color == 'R'){
	  child->color = 'B';
	}
	else{
	  rcasePNULL(child, parent, sibling);
	}
      }

      //if the parent is black
      else if(todelete->parent->color == 'B'){
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
	if(child == NULL){
	  node* temp = new node;
	  temp->color = 'B';
	  temp->data = 0;
	  temp->parent = parent;
	  temp->left = NULL;
	  temp->right = NULL;
	  if(parent->right == sibling){
	    parent->left = temp;
	  }
	  else{
	    parent->right = temp;
	  }
	  rcasePNULL(temp, parent, sibling);
	  if(parent->right == temp){
	    parent->right = NULL;
	  }
	  else{
	    parent->left = NULL;
	  }
	  delete temp;
	}
	else if(child->color == 'R'){
	  child->color = 'B';
	}
	else{
	  rcasePNULL(child, parent, sibling);
	}
      }
      
      //if todelete's parent is red
      else if(todelete->parent->color == 'R'){
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
	else{
	  rcaseNoChild(todelete->parent);
	}
	delete todelete;
      }
    }
  }
  else{
    cout << "Does not exist: " << data << endl;
  }
  return 0;
}

//if todelete has no children and parent is red
int RBTree::rcaseNoChild(node* p){
  //left child was removed
  if(p->left == NULL){
    //right is NULL too
    if(p->right == NULL){
      p->color = 'B';
    }
    else{
      //rotate subtree so rotation happens correctly
      if(p->right->left != NULL){
	rotateR(p->right);
      }
      rotateL(p);
      //adjust colors
      node* s = getSibling(p);
      if(s == NULL){
	p->parent->color = 'B';
	p->color = 'R';
      }
      else{
	s->color = 'B';
	p->color = 'B';
	p->parent->color = 'R';
      }
    }
  }
  else{
    //rotate subtree
    if(p->left->right != NULL){
      rotateL(p->left);
    }
    rotateR(p);
    //adjust colors
    node* s = getSibling(p);
    if(s == NULL){
      p->parent->color = 'B';
      p->color = 'R';
    }
    else{
      s->color = 'B';
      p->color = 'B';
      p->parent->color = 'R';
    }
  }
  return 0;
}

//case 1: parent is NULL
//n is new head, else move on
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
    //if s is red, swap colors with p and rotate
    if(s->color == 'R'){
      p->color = 'R';
      s->color = 'B';
      if(p->right == n){
	rotateR(p);
      }
      else{
	rotateL(p);
      }
    }
  }

  //go to case three with a new sibling
  node* gotten = getSibling(n);
  rcasePBSBsBsB(n, p, getSibling(n));
  return 0;
}

//remove case 3: sibling, parent, and sibling's children are black
//paint sibling red and go to case 1 with parent, else move on
int RBTree::rcasePBSBsBsB(node* n, node* p, node* s){
  //if parent is black
  if(p->color == 'B'){
    if(s != NULL){
      //if sibling is black
      if(s->color == 'B'){
	//if sibling left child is black (NULL)
	if(s->left == NULL){
	  //if sibling right child is black (NULL)
	  if(s->right == NULL){
	    s->color = 'R';
	    rcasePNULL(p, p->parent, getSibling(p));
	  }
	  //if right child is black
	  else if(s->right->color == 'B'){
	    s->color = 'R';
	    rcasePNULL(p, p->parent, getSibling(p));
	  }
	  else{
	    rcasePRSBsBsB(n, p, s);
	  }
	}
	//if right child is black (NULL)
	else if(s->right == NULL){
	  if(s->left->color == 'B'){
	    s->color = 'R';
	    rcasePNULL(p, p->parent, getSibling(p));
	  }
	  else{
	    rcasePRSBsBsB(n, p, s);
	  }
	}
	//if both are black
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
//swap colors of s and p, else/then move on to case 5
int RBTree::rcasePRSBsBsB(node* n, node* p, node* s){
  //if parent is red
  if(p->color == 'R'){
    if(s != NULL){
      //if sibling is black
      if(s->color == 'B'){
	//if sibling left child is black (NULL)
	if(s->left == NULL){
	  //if sibling right child is black (NULL)
	  if(s->right == NULL){
	    s->color = 'R';
	    p->color = 'B';
	  }
	  //if right child is black
	  else if(s->right->color == 'B'){
	    s->color = 'R';
	    p->color = 'B';
	  }
	  else{
	    rcaseSBsRsBNL(n, p, s);
	  }
	}
	//if right child is black (NULL)
	else if(s->right == NULL){
	  //if left child is black
	  if(s->left->color == 'B'){
	    s->color = 'R';
	    p->color = 'B';
	  }
	  else{
	    rcaseSBsRsBNL(n, p, s);
	  }
	}
	//if both are black
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
//if child is on inside, move to outside by rotating before going to case 6
int RBTree::rcaseSBsRsBNL(node* n, node* p, node* s){
  //if n is left child of parent
  if(p->left == n){
    if(s != NULL){
      //sibling is black
      if(s->color == 'B'){
	//siblings's left child is red
	if(s->left != NULL){
	  if(s->left->color == 'R'){
	    //if s's right child is black (NULL)
	    if(s->right == NULL){
	      rotateR(s);
	      s->color = 'R';
	      s->parent->color = 'B';
	    }
	    //right child is black
	    else if(s->right->color == 'B'){
	      rotateR(s);
	      s->color = 'R';
	      s->parent->color = 'B';
	    }
	  }
	}
      }
    }
  }
  //if n is right child of parent
  else if(p->right == n){
    if(s != NULL){
      //sibling is black
      if(s->color == 'B'){
	 //sibling's right child is red
	 if(s->right != NULL){
	   if(s->right->color == 'R'){
	     //sibling's left child is black
	     if(s->left == NULL){
	       rotateL(s);
	       s->color = 'R';
	       s->parent->color = 'B';
	     }
	     //left child is black
	     else if(s->left->color == 'B'){
	       rotateL(s);
	       s->color = 'R';
	       s->parent->color = 'B';
	     }
	   }
	 }
      }
    }
  }
  //move on to case 6
  rcaseSBsrRNL(n, p, getSibling(n));
  return 0;
}

//case 6: sibling is black, sibling's right child is red, node is left child
//rotate and swap colors of p and s
int RBTree::rcaseSBsrRNL(node* n, node* p, node* s){
  //n is left child
  if(p->left == n){
    if(s != NULL){
      //sibling is black
      if(s->color == 'B'){
	//s's right child is red
	if(s->right != NULL){
	  if(s->right->color == 'R'){
	    //rotate L and swap colors
	    rotateL(p);
	    char pcolor = p->color;
	    p->color = s->color;
	    s->color = pcolor;
	    s->right->color = 'B';
	  }
	}
      }
    }
  }
  //n is right child
  else if(p->right == n){
    if(s != NULL){
      //sibling is black
      if(s->color == 'B'){
	//s's left child is red
	if(s->left != NULL){
	  if(s->left->color == 'R'){
	    //rotate R and swap colors
	    rotateR(p);
	    char pcolor = p->color;
	    p->color = s->color;
	    s->color = pcolor;
	    s->left->color = 'B';
	  }
	}
      }
    }
  }   
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
  //cout << "visualize(): cur is: " << cur->data << endl;
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
      //cout << "visualize(): going left" << endl;
      visualize(cur->left, newlevel);
    }
  }
  else{
    cout << "Tree is empty" << endl;
  }
  return 0;
}
