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
};

class RBTree{
 public:
  RBTree();
  ~RBTree();
  node* getParent(node* n);     //get parent of n
  node* getSibling(node* n);    //get sibling of n
  node* getUncle(node* n);      //get uncle of n
  int insert(int data);         //create a node and add to tree
  int insert(node* newnode, node* current); //insert a node recursively
  int contains(int data, node* current);  //check if tree contains node
  int visualize();              //calls next function
  int visualize(node* current, int level);  //print out tree recursively
 private:
  node* head;                   //head of tree
};
