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
      cout << "getSibling(): returning left" << endl;
      return n->parent->left;
    }
    else{
      cout << "getSibling(): returning right" << endl;
      return n->parent->right;
    }
  }
  //else return NULL
  else{
    cout << "returning NULL" << endl;
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
  cout << "CURRENT DATA NUMBER TO REMOVE: " << data << endl;
  visualize();
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
    cout << "todelete: " << todelete->data << todelete->color << endl;
    //cout << "found: " << found->data << endl;
    //cout << "child: " << child->data << endl;
    
    //if todelete is red
    if(todelete->color == 'R'){
      cout << "todelete is red" << endl;
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
      cout << "remove(): todelete is B" << endl;
      if(child != NULL)
	cout << "child: " << child->data << child->color << endl;
      else
	cout << "child is NULL" << endl;
      cout << "found: " << found->data << found->color << endl;
      cout << "todelete: " << todelete->data << todelete->color << endl;
      if(todelete == head && todelete->parent == NULL && todelete->left == NULL && todelete->right == NULL){
	head = NULL;
	delete todelete;
      }
      else if(todelete == head && todelete->parent == NULL && todelete->left == NULL){
	child->parent = NULL;
	head = child;
	child->color = 'B';
	delete todelete;
      }
      else if(todelete->parent == NULL){
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
	cout << "beginning cases" << endl;
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
      //      else if(found->right == 
      else if(todelete->parent->color == 'B'){
cout << "todelete's parent is black" << endl;
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
	cout << "parent is black, beginning cases" << endl;
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
	cout << "remove(): todelete is black and parent is red" << endl;
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

int RBTree::rcasePNULL(node* n, node* p, node* s){
  if(p != NULL){
    cout << "rcasePNULL(): n is " << n->color << endl;
    if(n == NULL){
      cout << "rcasePNULL(): n is NULL" << endl;
    }
    cout << "rcasePNULL(): moving to rcase(n,p,s);" << endl;
    rcaseSR(n, p, s);
  }
  else{
    head = n;
  }
  return 0;
}

//remove case 2: sibling is red, calls case 3
int RBTree::rcaseSR(node* n, node* p, node* s){
  if(n == NULL){
    cout << "rcaseSR(): n is NULL at beginning of fn" << endl;
  }
  cout << "rcaseSR(): n is " << n->color << endl;
  if(s != NULL){
    if(s->color == 'R'){
      cout << "rcaseSR(): s is R" << endl;
      p->color = 'R';
      s->color = 'B';
      cout << "rcaseSR(): swapped colors: PR SB" << endl;
      visualize();
      cout << "rcaseSR(): visualized" << endl;
      if(p->right == n){
	cout << "rcaseSR(): rotating right" << endl;
	if(n == NULL){
	  cout << "rcaseSR(): n is NULL before rotating right" << endl;
	}
	rotateR(p);
	if(n == NULL){
	  cout << "rcaseSR(): n is NULL after rotating right" << endl;
	}
      }
      else{
	cout << "rcaseSR(): rotating left" << endl;
	if(n == NULL){
	  cout << "rcaseSR(): n is NULL before rotating left" << endl;
	}
	rotateL(p);
	visualize();
	if(n == NULL){
	  cout << "rcaseSR(): n is NULL after rotating left" << endl;
	}
      }
    }
  }
  if(n == NULL){
    cout << "rcaseSR(): n is NULL" << endl;
  }
  cout << "moving to next case rcasePBSBsBsB()" << endl;

  node* gotten = getSibling(n);
  cout << "rcaseSR(): got sibling" << endl;
  if(gotten == NULL){
    cout << "rcaseSR(): gotten is NULL" << endl;
  }
  rcasePBSBsBsB(n, p, getSibling(n));
  return 0;
}

//remove case 3: sibling, parent, and sibling's children are black
int RBTree::rcasePBSBsBsB(node* n, node* p, node* s){
  cout << "case 3" << endl;
  if(s == NULL){
    cout << "rcasePBSBsBsB(): s is NULL" << endl;
  }
  else{
    if(s->left == NULL){
      cout << "rcasePBSBsBsB(): left is NULL" << endl;
    }
    else{
      cout << "rcasePBSBsBsB(): left is " << s->left->color << endl;
    }
    if(s->right == NULL){
      cout << "rcasePBSBsBsB(): right is NULL" << endl;
    }
    else{
      cout << "rcasePBSBsBsB(): right is " << s->right->color << endl;
    }
  }
  cout << "rcasePBSBsBsB(): begining to evaluate: case 3" << endl;
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
	else if(s->right == NULL){
	  if(s->left->color == 'B'){
	    s->color = 'R';
	    rcasePNULL(p, p->parent, getSibling(p));
	  }
	  else{
	    rcasePRSBsBsB(n, p, s);
	  }
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
  cout << "rcasePRSBsBsB()" << endl;
  if(p == NULL){
    cout << "rcasePRSBsBsB(): p is NULL" << endl;
  }
  if(s == NULL){
    cout << "rcasePRSBsBsB(): sibling is NULL" << endl;
}
  else{
    if(s->right == NULL)
      cout << "rcasePRSBsBsB(): sibling right child is NULL" << endl;
    if(s->left == NULL)
      cout << "rcasePRSBsBsB(): sibling left child is NULL" << endl;
  }
  if(p->color == 'R'){
    if(s != NULL){
      if(s->color == 'B'){
	cout << "rcasePRSBsBsB(): I got here" << endl;
	if(s->left == NULL){
	  cout << "rcasePRSBsBsB(): left child is NULL" << endl;
	  if(s->right == NULL){
	    s->color = 'R';
	    p->color = 'B';
	    cout << "rcasePRSBsBsB(): swapped colors" << endl;
	  }
	  else if(s->right->color == 'B'){
	    s->color = 'R';
	    p->color = 'B';
	    cout << "rcasePRSBsBsB(): swapped colors" << endl;
	  }
	  else{
	    cout << "rcasePRSBsBsB(): moving to next case" << endl;
	    rcaseSBsRsBNL(n, p, s);
	  }
	}
	else if(s->right == NULL){
	  cout << "rcasePRSBsBsB() ln 547: right is NULL" << endl;
	  if(s->left->color == 'B'){
	    cout << "rcasePRSBsBsB(): right is NULL" << endl;
	    s->color = 'R';
	    p->color = 'B';
	  }
	  else{
	    cout << "rcasePRSBsBsB() ln 554: moving on to case 5" << endl;
	    rcaseSBsRsBNL(n, p, s);
	  }
	}
	else if(s->right->color == 'B' && s->left->color == 'B'){
	  cout << "rcasePRSBsBsB(): both are black" << endl;
	  s->color = 'R';
	  p->color = 'B';
	}
	else{
	  cout << "rcasePRSBsBsB(): moving on" << endl;;
	  rcaseSBsRsBNL(n, p, s);
	}
      }
      else{
	cout << "rcasePRSBsBsB(): doing else becuase sibling was NULL" << endl;
	cout << "rcasePRSBsBsB(): moving on" << endl;
	rcaseSBsRsBNL(n, p, s);
      }
    }
    else{
      cout << "rcasePRSBsBsB(): moving on" << endl;
      rcaseSBsRsBNL(n, p, s);
    }
  }
  else{
    cout << "rcasePRSBsBsB(): moving on" << endl;
    rcaseSBsRsBNL(n, p, s);
  }
  return 0;
}


//case 5: sibling is black, sibling's left child is red,
//sibling's right child is black, and n is left child of parent
int RBTree::rcaseSBsRsBNL(node* n, node* p, node* s){
  cout << "case5" << endl;
  //if n is left child of parent
  if(p->left == n){
    if(s != NULL){
      //sibling is black
      if(s->color == 'B'){
	//siblings's left child is red
	if(s->left != NULL){
	  if(s->left->color == 'R'){
	    //if s's right child is black
	    if(s->right == NULL){
	      rotateR(s);
	      s->color = 'R';
	      s->parent->color = 'B';
	    }
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
  visualize();
  rcaseSBsrRNL(n, p, getSibling(n));
  return 0;
}

//case 6: sibling is black, sibling's right child is red, node is left child
int RBTree::rcaseSBsrRNL(node* n, node* p, node* s){
  cout << "case6" << endl;
  if(p->left == n){
    cout << "rcaseSBsrRNL(): n is left child" << endl;
    if(s != NULL){
      //sibling is black
      if(s->color == 'B'){
	cout << "rcaseSBsrRNL(): s is B" << endl;
	//s's right child is red
	if(s->right != NULL){
	  if(s->right->color == 'R'){
	    cout << "rcaseSBsrRNL(): sr is R" << endl;
	    //rotate L and swap colors
	    visualize();
	    cout << "rcaseSBsrRNL(): n is " << n->data << n->color << endl;
	    cout << "rcaseSBsrRNL(): p is " << p->data << p->color << endl;
	    cout << "rcaseSBsrRNL(): p->right is " << p->right->data << p->right->color << endl;
	    cout << "rcaseSBsrRNL(): p->left is " << p->left->data << p->left->color << endl;
	    //node* twenty = locate(24, head);
	    //cout << "twentyfour: " << twenty->color << twenty->parent->data << endl;
	    rotateL(p);
	    visualize();
	    cout << "rcaseSBsrRNL(): ^rotated left" << endl;
	    char pcolor = p->color;
	    p->color = s->color;
	    s->color = pcolor;
	    s->right->color = 'B';
	    cout << "P is s's color & vice versa" << endl;
	  }
	}
      }
    }
  }
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
