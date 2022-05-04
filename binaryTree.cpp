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
      
      //initialize l/r node children to null
      parent = NULL;
      left = NULL;
      right = NULL;
    }
  };
  void addToNode(struct Node*, struct Node*);
  void printNode(struct Node*, int indentLevel);
  struct Node* findNode(struct Node* node, int x);
  
  
  
  
  Node* root = NULL;
};

void Tree::addToNode(struct Node* treeNode, struct Node* nextNode) {
  if (treeNode->data > nextNode->data) {
    //going left
    if (treeNode->left == NULL) {
      treeNode->left = nextNode;
      nextNode->parent = treeNode;
    }
    else {
      addToNode(treeNode->left, nextNode);
    }
  }
  //going right
  else {
    if (treeNode->right == NULL) {
      treeNode->right = nextNode;
      nextNode->parent = treeNode;
    }
    else {
      addToNode(treeNode->right, nextNode);
    }
  }
}
//psuedocode from http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm
void Tree::insert(int x) {
  struct Node* newNode = new Node(x);
  if (root == NULL) {
    root = newNode;
  }
  else {
    addToNode(root, newNode);
  }
  /*
color(x)<-red
while (x != root[T] && color(p(x)) == red) {
   do if (p(x) == left(p(p(x))) {
      then y<-right(p(p(x))) {
         if (color(y) == red) {
            then color(p(x))<- black //case 1
                 color(y)<-black     //case 1
                 color(p(p(x)))<-red //case 1
                 x<-p(p(x))          //case 1
            else if (x == right(p(x))) {
               then x<-p(x)          //case 2
                  LEFT-ROTATE(T,x)   //case 2
               color(p(x))<-black    //case 3
               color(p(p(x)))<-red   //case 3
               RIGHT-ROTATE(T, p(p(x))) //case 3
            }
         }
      }
      else (same as then clause
            with "right" and "left" exchanged)
   }
}
color(root(T))<-black
   */
}
/*
void Tree::leftRotate(T, x) {
  y<-right(x) //set y
  right(x)<-left(y) //turns y's left subtree into x's right subtree
  if (left(y) != NULL) {
     then p(left(y))<-x
  }
  p(y)<-p(x)  //link x's parent to y
  if (p(x) == NULL) {
     then root(T)<-y
     else if (x == left(p(x))) {
        then left(p(x))<-y
        else right(p(x))<-y
     }
  }
  left(y)<-x   //put x on y's left
  p(x)<-y
}
*/












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
