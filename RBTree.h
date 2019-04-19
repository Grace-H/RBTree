/*header file for RBTree, implementation of a Red Black Tree
 *Author: Grace Hunter
 *Date: 26 March 2019
 */

#include <cstring>
#include <iostream>

using namespace std;

struct node{
  int data;
  char color;
  node* left;
  node* right;
  node* parent;
};

class RBTree{
 public:
  RBTree();                                     //constructor, head is NULL
  ~RBTree();                                    //destructor, remove all nodes
  int rotateR(node* root);                      //rotate right with root as root
  int rotateL(node* root);                      //rotate left with root as root
  node* getGramp(node* n);                      //get grandparent of n
  node* getParent(node* n);                     //get parent of n
  node* getSibling(node* n);                    //get sibling of n
  node* getUncle(node* n);                      //get uncle of n
  int remove(int data);                         //locates and removes node with given data
  int rcasePNULL(node* n, node* p, node* s);    //remove case 1: new head
  int rcaseSR(node* n, node* p, node* s);       //remove case 2: sibling is red
  int rcasePBSBsBsB(node* n, node* p, node* s); //remove case 3: parent, sibling & its children are black
  int rcasePRSBsBsB(node* n, node* p, node* s); //remove case 4: parent is red, sibling & its children are black
  int rcaseSBsRsBNL(node* n, node* p, node* s); //remove case 5: s & its right black, its left red, n is left child
  int rcaseSBsrRNL(node* n, node* p, node* s);  //remove case 6: s black, right child red, node is left child
  int insert(int data);                         //create a node and add to tree
  int repairTree(node* n);                      //diagnose tree
  int icasePRUR(node* n);                       //insert case 3: parent & uncle == red
  int icasePRUB(node* n);                       //insert case 4: parent == red & uncle == black
  int insert(node* newnode, node* current);     //insert a node recursively
  node* locate(int data, node* head);           //finds and returns node with data
  int search(int data);                         //prints whether number exists in tree
  int contains(int data, node* current);        //check if tree contains node
  int visualize();                              //calls other visualize function
  int visualize(node* current, int level);      //print out tree recursively
 private:
  node* head;                                   //head of tree
};
