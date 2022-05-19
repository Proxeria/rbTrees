#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <assert.h>

using namespace std;

class Tree {
public:
  void insert(int);
  int find(int);
  void print(void);
  int deleteNode(int);
  
private:
  struct Node {
    int data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    bool isRed;
    
    Node(int val) {
      data = val;
      isRed = true;
      //initialize l/r node children to null
      parent = NULL;
      left = NULL;
      right = NULL;
    }
  };
  struct Node nilNode = Node(0);
  struct Node* nilNodePTR = &nilNode;
  void addNode(struct Node*);
  void printNode(struct Node*, int indentLevel);
  struct Node* findNode(struct Node* node, int x);
  void leftRotate(struct Node*); // x
  void rightRotate(struct Node*); // x
  void treeInsert(struct Node*);
  struct Node* treeMin(struct Node*);
  struct Node* remove(struct Node*);
  struct Node* treeSucc(struct Node*);
  void fixup(struct Node*);
  bool isNilNode(struct Node* node) {
    return node == NULL || node == nilNodePTR;
  }
  
  
  Node* root = NULL;
};

//from http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm
void Tree::fixup(struct Node* xNode) {
  struct Node* wNode;
  while (xNode != root && xNode->isRed == false) {
    assert(!isNilNode(xNode->parent));
    if (xNode == xNode->parent->left) {
      wNode = xNode->parent->right;
      if (wNode->isRed) {
	wNode->isRed = false;                               //Case 1
	xNode->parent->isRed = true;                        //Case 1
	leftRotate(xNode->parent);                          //Case 1
	wNode = xNode->parent->right;                       //Case 1
      }
      if ((!isNilNode(wNode->left) && wNode->left->isRed == false) &&
	  (!isNilNode(wNode->right) && wNode->right->isRed == false)) {
	wNode->isRed = true;                                 //Case 2
	xNode = xNode->parent;                               //case 2
      }
      else if (!isNilNode(wNode->right) && wNode->right->isRed == false) {
	wNode->left->isRed = false;                       //Case 3
	wNode->isRed = true;                              //Case 3
	rightRotate(wNode);                               //Case 3
	wNode = xNode->parent->right;                     //Case 3
      }
      wNode->isRed = xNode->parent->isRed;                //Case 4
      xNode->parent->isRed = false;                       //Case 4
      if (!isNilNode(wNode->right)) {
	wNode->right->isRed = false;                        //Case 4
      }
      leftRotate(xNode->parent);                          //Case 4
      xNode = root;                                       //Case 4     
    }
    else {
      wNode = xNode->parent->left;
      if (!isNilNode(wNode) && wNode->isRed) {
	wNode->isRed = false;                               //Case 5
	xNode->parent->isRed = true;                        //Case 5
	rightRotate(xNode->parent);                          //Case 5
	wNode = xNode->parent->left;                       //Case 5
      }
      if ((!isNilNode(wNode->right) && wNode->right->isRed == false) &&
	  (!isNilNode(wNode->left) && wNode->left->isRed == false)) {
	wNode->isRed = true;                                 //Case 6
	xNode = xNode->parent;                               //case 6
      }
      else if (!isNilNode(wNode->left) && wNode->left->isRed == false) {
	wNode->right->isRed = false;                       //Case 7
	wNode->isRed = true;                              //Case 7
	leftRotate(wNode);                               //Case 7
	wNode = xNode->parent->left;                     //Case 7
      }
      wNode->isRed = xNode->parent->isRed;                //Case 8
      xNode->parent->isRed = false;                       //Case 8
      if (!isNilNode(wNode->left)) {
	wNode->left->isRed = false;                        //Case 8
      }
      rightRotate(xNode->parent);                          //Case 8
      xNode = root;                                       //Case 8
    }
  }
  xNode->isRed = false;
}

//from http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm
struct Tree::Node* Tree::remove(struct Node* thisNode) {
  struct Node* yNode;
  struct Node* xNode;
  if (isNilNode(thisNode->left) || isNilNode(thisNode->right)) {
    yNode = thisNode;
  }
  else {
    yNode = treeSucc(thisNode);
  }
  if (!isNilNode(yNode->left)) {    
    xNode = yNode->left;
  }
  else {
    if (isNilNode(yNode->right)) {
      // Use sentinel for nil nodes
      nilNode.parent = yNode;
      nilNode.isRed = false;
      xNode = nilNodePTR;
    }
    else {
      xNode = yNode->right;
    }
  }
  xNode->parent = yNode->parent;
  if (isNilNode(yNode->parent)) {
    root = xNode;
  }
  else if (yNode == yNode->parent->left) {
    yNode->parent->left = xNode;
  }
  else {
    yNode->parent->right = xNode;
  }
  if (yNode != thisNode) {
    thisNode->data = yNode->data;
  }
  if (yNode->isRed == false) {
    fixup(xNode);
  }
  return yNode;
}
 
struct Tree::Node* Tree::treeSucc(struct Node* xNode) {
  struct Node* yNode;
  if (!isNilNode(xNode->right)) {
    return treeMin(xNode->right);
  }
  yNode = xNode->parent;
  while (!isNilNode(yNode) && xNode == yNode->right) {
    xNode = yNode;
    yNode = yNode->parent;
  }
  return yNode;
}
 
struct Tree::Node* Tree::treeMin(struct Node* thisNode) {
  assert(!isNilNode(thisNode));
  while (!isNilNode(thisNode->left)) {
    thisNode = thisNode->left;
  }
  return thisNode;
}

//from http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap13.htm
void Tree::treeInsert(struct Node* newNode) {
  struct Node* yNode = NULL;
  struct Node* xNode = root;
  
  while (!isNilNode(xNode)) {
       yNode = xNode;  
       if (newNode->data < xNode->data) {
	 xNode = xNode->left;
       }
       else {
	 xNode = xNode->right;
       }
  }
  newNode->parent = yNode;  
  if (isNilNode(yNode)) {
    root = newNode;
  }
  else if (newNode->data < yNode->data) {
    yNode->left = newNode;
  }
  else {
    yNode->right = newNode;
  }
}
//psuedocode from http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm
void Tree::addNode(struct Node* newNode) {
  struct Node* yNode = NULL;
  treeInsert(newNode);
  newNode->isRed = true;
  while ((newNode != root) && (!isNilNode(newNode->parent)) && (newNode->parent->isRed)) {  
    if ((!isNilNode(newNode->parent)) && (!isNilNode(newNode->parent->parent))) { 
      if (newNode->parent == newNode->parent->parent->left) {
	yNode = newNode->parent->parent->right;
	// if (yNode == NULL) {
	//   break;
	// }
	if ((!isNilNode(yNode)) && (yNode->isRed)) {
	  newNode->parent->isRed = false; //case 1
	  yNode->isRed = false;     //case 1
	  newNode->parent->parent->isRed = true; //case 1
	  newNode = newNode->parent->parent; //case 1
	}
	else if (newNode == newNode->parent->right) {
	  newNode = newNode->parent;          //case 2
	  leftRotate(newNode);   //case 2
	}
	if (!isNilNode(newNode->parent)) {
	  newNode->parent->isRed = false;    //case 3
	  if (!isNilNode(newNode->parent->parent)) {
	    newNode->parent->parent->isRed = true;   //case 3
	    rightRotate(newNode->parent->parent); //case 3
	  }
	}
      }
      //else clause is same as above with left/right inverted
      else {
	yNode = newNode->parent->parent->left; 
	// if (yNode == NULL) {
	//   break;
	// }
	if ((!isNilNode(yNode)) && (yNode->isRed)) {
	  newNode->parent->isRed = false; //case 4
	  yNode->isRed = false;     //case 4
	  newNode->parent->parent->isRed = true; //case 4
	  newNode = newNode->parent->parent; //case 4
	}
	else if (newNode == newNode->parent->left) {
	  newNode = newNode->parent;          //case 5
	  rightRotate(newNode);   //case 5
	}
	if (!isNilNode(newNode->parent)) {
	  newNode->parent->isRed = false;    //case 6
	  if (!isNilNode(newNode->parent->parent)) {
	    newNode->parent->parent->isRed = true;   //case 6
	    leftRotate(newNode->parent->parent); //case 6
	  }
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
  if (!isNilNode(yNode->left)) {
    yNode->left->parent = node;
  }
  yNode->parent = node->parent;  //link x's parent to y
  if (isNilNode(node->parent)) {
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
  if (!isNilNode(yNode->right)) {
    yNode->right->parent = node;
  }
  yNode->parent = node->parent;  //link x's parent to y
  if (isNilNode(node->parent)) {
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
  if (isNilNode(node)) {
    return NULL;
  }
  else {
    if (node->data == x) {
      return node;
    }
    else {
      Node* match = findNode(node->left, x);
      if (!isNilNode(match)) {
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
  if (!isNilNode(node)) {
    return 1;
  }
  else {
    return 0;
  }
}

int Tree::deleteNode(int x) {
  Node* node = findNode(root, x);
  if (!isNilNode(node)) {
    delete(remove(node));
    return 1;
  }
  else {
    return 0;
  }
}

void Tree::printNode(struct Node* node, int indentLevel) {
  if ((isNilNode(node)) || (node == nilNodePTR)) {
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
      thisTree.deleteNode(tempInt);
      cout << "Deleted" << endl;
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
