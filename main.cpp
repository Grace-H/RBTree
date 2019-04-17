/*Uses Binary Search Tree to store integer values
 *Author: Grace Hunter
 *Date: 24 March 2019
 */

#include <cstring>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include "RBTree.h"

using namespace std;

int search(RBTree* tree, char* nums);
int insert(RBTree* tree, char* nums);
int remove(RBTree* tree, char* nums);

int main(){
  //commands
  char* readstr = new char[20];
  char* addstr = new char[20];
  char* printstr = new char[20];
  char* removestr = new char[20];
  char* searchstr = new char[20];
  char* quitstr = new char[20];
  
  strcpy(readstr, "READ");
  strcpy(addstr, "ADD");
  strcpy(printstr, "PRINT");
  strcpy(removestr, "REMOVE");
  strcpy(searchstr, "SEARCH");
  strcpy(quitstr, "QUIT");
  
  char* input = new char[256];
  char* nums = new char[100000];

  //initialize tree
  RBTree* tree = new RBTree();

  cout << "note: commands do not have to be uppercase" << endl;
  
  //keep asking for command until user asks to quit
  bool go = true;
  while(go){
    //get input
    cout << "'READ' 'ADD' 'PRINT' 'REMOVE' 'SEARCH' or 'QUIT'?" << endl;
    cin.get(input, 256);
    cin.get();

    //uppercase
    for(int i = 0; i < strlen(input); i++){
      input[i] = toupper(input[i]);
    }
    
    //identify command & act accordingly
    //add
    if(strcmp(addstr, input) == 0){
   
      //uppercase
      for(int i = 0; i < strlen(input); i++){
        input[i] = toupper(input[i]);
      }
    
      //create char* from commamd line
      cout << "Enter number(s) (If more than one seperate by commas):" << endl;
      cin.get(nums, 100000);
      cin.get();

      //add to tree
      insert(tree, nums);
    }
    //read
    else if(strcmp(readstr, input) == 0){
      cout << "Enter complete file name. Numbers must be seperated by commas" << endl;
      cin.get(input, 256);
      cin.get();

      //get from file
      ifstream is(input);
      is.get(nums, 100000);
      cout << nums << endl;
      is.close();

      //add to tree
      insert(tree, nums);
    }
    
    //remove from tree
    else if(strcmp(removestr, input) == 0){
      cout << "Enter spaced-seperated numbers to remove from tree: " << endl;
      cin.get(nums, 100000);
      cin.get();
      //remove
      remove(tree, nums);
    }
    
    //print tree
    else if(strcmp(printstr, input) == 0){
      tree->visualize();
    }

    else if(strcmp(searchstr, input) == 0){

      //create char* from commamd line
      cout << "Enter number(s) (If more than one seperate by commas):" << endl;
      cin.get(nums, 100000);
      cin.get();

      //search tree for nums
      search(tree, nums);
    }
    //quit
    else if(strcmp(quitstr, input) == 0){
      go = false;
      delete [] input;
      delete [] nums;
      delete [] quitstr;
      delete [] printstr;
      //delete [] removestr;
      delete [] addstr;
      delete [] readstr;
      //delete tree;
    }  
    else{
      cout << "not an option" << endl;
    }
  }
  return 0;
}

//find if a number exists in tree
int search(RBTree* tree, char* nums){
  //get token
  int cur = 0;
  char* str;
  str = strtok(nums, ",");
  
  while(str != NULL){
    //convert to int  
    cur = atoi(str);
    //ask tree if exists  
    tree->search(cur);
    str = strtok(NULL, ",");
  }
}
  
//remove numbers in tree from char* array
int remove(RBTree* tree, char* nums){
  //get token
  int cur = 0;
  char* str;
  str = strtok(nums, ",");
  
  while(str != NULL){
    //convert to int  
    cur = atoi(str);
    //remove from tree
    tree->remove(cur);
    str = strtok(NULL, ",");
  }
  tree->visualize();
  return 0;
}

//adds numbers to tree from a char* array
int insert(RBTree* tree, char* nums){
  //get token
  int cur = 0;
  char* str;
  str = strtok(nums, ",");
  
  while(str != NULL){
    //convert to int  
    cur = atoi(str);
    //insert into tree  
    tree->insert(cur);
    str = strtok(NULL, ",");
  }
  tree->visualize();
  return 0;
}
