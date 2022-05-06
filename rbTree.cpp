#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <assert.h>

using namespace std;

class Tree {
public:
  void insert(int);
  void remove(int);
  int find(int);
  void print(void);
  
private:
  struct Node {
    int data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    bool isRed;
    
    Node(int val) {
      data = val;
      isRed = false;
      //initialize l/r node children to null
      parent = NULL;
      left = NULL;
      right = NULL;
    }
  };
  void addNode(struct Node*);
  void printNode(struct Node*, int indentLevel);
  struct Node* findNode(struct Node* node, int x);
  void leftRotate(struct Node*); // x
  void rightRotate(struct Node*); // x
  
  
  Node* root = NULL;
};
//psuedocode from http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm
void Tree::addNode(struct Node* newNode) {
  struct Node* yNode = NULL;
  newNode->isRed = true;
  while ((newNode != root) && (newNode->parent != NULL) && (newNode->parent->isRed)) {  
    if ((newNode->parent != NULL) && (newNode->parent->parent != NULL)) { 
      if (newNode->parent == newNode->parent->parent->left) {
	yNode = newNode->parent->parent->right; 
	if (yNode->isRed) {
	  newNode->parent->isRed = false; //case 1
	  yNode->isRed = false;     //case 1
	  newNode->parent->parent->isRed = true; //case 1
	  newNode = newNode->parent->parent; //case 1
	}
	else if (newNode == newNode->parent->right) {
	  newNode = newNode->parent;          //case 2
	  leftRotate(newNode);   //case 2
	  newNode->parent->isRed = false;    //case 3
	  newNode->parent->parent->isRed = true;   //case 3
	  rightRotate(newNode->parent->parent); //case 3
	}
      }
      //else clause is same as above with left/right inverted
      else {
	yNode = newNode->parent->parent->left; 
	if (yNode->isRed) {
	  newNode->parent->isRed = false; //case 1
	  yNode->isRed = false;     //case 1
	  newNode->parent->parent->isRed = true; //case 1
	  newNode = newNode->parent->parent; //case 1
	}
	else if (newNode == newNode->parent->left) {
	  newNode = newNode->parent;          //case 2
	  rightRotate(newNode);   //case 2
	  newNode->parent->isRed = false;    //case 3
	  newNode->parent->parent->isRed = true;   //case 3
	  leftRotate(newNode->parent->parent); //case 3
	}
      }
    }
  }
  root->isRed = false; 
}

void Tree::insert(int x) {
  struct Node* newNode = new Node(x);
  addNode(newNode);
}

void Tree::leftRotate(struct Node* node) {
  struct Node* yNode = NULL;
  yNode = node->right; //set y
  node->right = yNode->left; //turns y's left subtree into x's right subtree
  if (yNode->left != NULL) {
    yNode->left->parent = node;
  }
  yNode->parent = node->parent;  //link x's parent to y
   if (node->parent == NULL) {
     root = yNode;
   }
   else if (node == node->parent->left) {
     node->parent->left = yNode;
   }
   else {
     node->parent->right = yNode;
   }  
   yNode->left = node;   //put x on y's left
   node->parent = yNode;
}

void Tree::rightRotate(struct Node* node) { 
  struct Node* yNode = NULL;
  yNode = node->left; //set y
  node->left = yNode->right; //turns y's right subtree into x's left subtree
  if (yNode->right != NULL) {
    yNode->right->parent = node;
  }
  yNode->parent = node->parent;  //link x's parent to y
   if (node->parent == NULL) {
     root = yNode;
   }
   else if (node == node->parent->right) {
     node->parent->right = yNode;
   }
   else {
     node->parent->left = yNode;
   }  
   yNode->right = node;   //put x on y's right
   node->parent = yNode;
}

struct Tree::Node* Tree::findNode(struct Node* node, int x) {
  if (node == NULL) {
    return NULL;
  }
  else {
    if (node->data == x) {
      return node;
    }
    else {
      Node* match = findNode(node->left, x);
      if (match != NULL) {
	return match;
      }
      else {
	return findNode(node->right, x);
      }
    }
  }
}

int Tree::find(int x) {
  Node* node = findNode(root, x);
  if (node != NULL) {
    return 1;
  }
  else {
    return 0;
  }
}

void Tree::printNode(struct Node* node, int indentLevel) {
  if (node == NULL) {
    return;
  }
  else {
    printNode(node->right, indentLevel + 1);
    for (int i = 0; i < indentLevel; i++) {
      cout << "   ";
    }
	if (node->isRed == true) {
   	   cout << "R " << node->data << endl;
	}
	else {
	   cout << "B " << node->data << endl;
	}
    printNode(node->left, indentLevel + 1);
  }
}

void Tree::print() {
  printNode(root, 0);
}

// Driver program to test above functions
int main() {
  Tree thisTree;
  ifstream fileInput("input.txt");
  string line;
  string input;
  string tempStr;
  int tempInt;
  int tempIntOne;
  int inputNum;
  vector<int> inputVect;
  
  cout << "Commands (Case Sensitive):" << endl;
  cout << "Line: enter a list of numbers in the input line" << endl;
  cout << "File: will use the list of names provided on the .txt file included" << endl;
  cout << "Remove: removes a user specified node" << endl;
  cout << "Find: finds a user specified node" << endl;
  cout << "Print: prints the entire tree" << endl;
  cout << "Quit: exits the program" << endl;
  while (true) {
    cout << "Command: ";
    cin >> input;
    cout << endl;
    if (input == "Line") {
      int numofNum, i;
      cout << "How many number will you enter?" << endl;
      cin >> numofNum;
      
      
      for (i = 1; i <= numofNum; i++) {
	cout << "Enter number " << (i) << endl;
	cin >> tempInt;
	thisTree.insert(tempInt);	
      }
    }
    //consumes file's contents on use
    else if (input == "File") {
      while (std::getline(fileInput, line)) {
	thisTree.insert(std::atoi(line.c_str()));
      }
    }
    else if (input == "Remove") {
      cout << "Enter a number to remove: " << endl;
      cin >> tempInt;
      cout << "remove" << endl; //thisTree.remove(tempInt);
    }
    else if (input == "Find") {
      cout << "Enter a number to find: " << endl;
      cin >> tempInt;
      tempIntOne = thisTree.find(tempInt);
      if (tempIntOne == 0) {
	cout << "The given number was not found" << endl;
      }
      else {
	cout << "The given number was found" << endl;
      }
    }
    else if (input == "Print") {
      thisTree.print();
    }
    else if (input == "Quit") {
      break;
    }
  }
}