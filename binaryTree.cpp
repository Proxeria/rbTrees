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
    struct Node* left;
    struct Node* right;
    
    Node(int val) {
      data = val;
      
      //initialize l/r node children to null
      left = NULL;
      right = NULL;
    }
  };
  void addToNode(struct Node*, struct Node*);
  void printNode(struct Node*, int indentLevel);
  Node* root = NULL;
};

/* tree function
//make root
  struct Node* root = new Node(1);

  //follow tree
  root->left = new Node(2);
  root->right = new Node(3);

  root->left = new Node(4);

  return 0;
 */

void Tree::addToNode(struct Node* treeNode, struct Node* nextNode) {
  if (treeNode->data > nextNode->data) {
    //going left
    if (treeNode->left == NULL) {
      treeNode->left = nextNode;
    }
    else {
      addToNode(treeNode->left, nextNode);
    }
  }
  //going right
  else {
    if (treeNode->right == NULL) {
      treeNode->right = nextNode;
    }
    else {
      addToNode(treeNode->right, nextNode);
    }
  }
}

void Tree::insert(int x) {
  struct Node* newNode = new Node(x);
  if (root == NULL) {
    root = newNode;
  }
  else {
    addToNode(root, newNode);
  }
}

void Tree::remove(int x) {
  return;
}

int Tree::find(int x) {
  return x;
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
    cout << node->data << endl;
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
    
    else if (input == "File") {
      while (std::getline(fileInput, line)) {
	thisTree.insert(std::atoi(line.c_str()));
      }
    }
    else if (input == "Remove") {
      cout << "Enter a number to remove: " << endl;
      cin >> tempInt;
      thisTree.remove(tempInt);
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
