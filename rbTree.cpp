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
  void treeInsert(struct Node*);
  struct Node* treeMin(struct Node*);
  struct Node* remove(struct Node*);
  struct Node* treeSucc(struct Node*);
  void fixup(struct Node*);
  
  
  Node* root = NULL;
};


void Tree::fixup(struct Node* xNode) {
// while x != root[T] and color[x] = BLACK
//    do if x = left(p(x))
//       then w<-right(p(x))
//          if color(w) = RED
//             then color(w)<-BLACK                               //Case 1
//                  color(p(x))<-RED                              //Case 1
//                  LEFT-ROTATE(T,p(x))                           //Case 1
//                  w<-right(p(x))                                //Case 1
//          if color(left(w)) = BLACK and color(right(w)) = BLACK
//             then color(w)<-RED                                 //Case 2
//                X<-p(x)                                         //Case 2
//             else if color(right(w)) = BLACK
//                then color(left(W))<-BLACK                      //Case 3
//                     color(w)<-RED                              //Case 3
//                     RIGHT-ROTATE(T,w)                          //Case 3
//                     w<-right(p(x))                             //Case 3
//                  color(w)<-color(p(x))                         //Case 4
//                  color(p(x))<—BLACK                            //Case 4
//                  color(right(w))<-BLACK                        //Case 4
//                  LEFT-ROTATE(T, p(x))                          //Case 4
//                  x<-root(T)                                    //Case 4
//       else (same as then clause
//             with "right" and "left" exchanged)
// color(x)<-BLACK
}


struct Tree::Node* Tree::remove(struct Node* thisNode) {
  struct Node* yNode;
  struct Node* xNode;
  if (thisNode->left == NULL || thisNode->right == NULL) {
    yNode = thisNode;
  }
  else {
    yNode = treeSucc(thisNode);
  }
  if (yNode->left != NULL) {    
    xNode = yNode->left;
  }
  else {
    xNode = yNode->right;
  }
  xNode->parent = yNode->parent;
  if (yNode->parent == NULL) {
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
  if (xNode->right != NULL) {
    return treeMin(xNode->right);
  }
  yNode = xNode->parent;
  while (yNode != NULL && xNode == yNode->right) {
    xNode = yNode;
    yNode = yNode->parent;
  }
  return yNode;
}
 
struct Tree::Node* Tree::treeMin(struct Node* thisNode) {
  assert(thisNode != NULL);
  while (thisNode->left != NULL) {
    thisNode = thisNode->left;
  }
  return thisNode;
}

//from http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap13.htm
void Tree::treeInsert(struct Node* newNode) {
  struct Node* yNode = NULL;
  struct Node* xNode = root;
  
  while (xNode != NULL) {
       yNode = xNode;  
       if (newNode->data < xNode->data) {
	 xNode = xNode->left;
       }
       else {
	 xNode = xNode->right;
       }
  }
  newNode->parent = yNode;  
  if (yNode == NULL) {
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
  while ((newNode != root) && (newNode->parent != NULL) && (newNode->parent->isRed)) {  
    if ((newNode->parent != NULL) && (newNode->parent->parent != NULL)) { 
      if (newNode->parent == newNode->parent->parent->left) {
	yNode = newNode->parent->parent->right;
	// if (yNode == NULL) {
	//   break;
	// }
	if ((yNode != NULL) && (yNode->isRed)) {
	  newNode->parent->isRed = false; //case 1
	  yNode->isRed = false;     //case 1
	  newNode->parent->parent->isRed = true; //case 1
	  newNode = newNode->parent->parent; //case 1
	}
	else if (newNode == newNode->parent->right) {
	  newNode = newNode->parent;          //case 2
	  leftRotate(newNode);   //case 2
	}
	if (newNode->parent != NULL) {
	  newNode->parent->isRed = false;    //case 3
	  if (newNode->parent->parent != NULL) {
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
	if ((yNode != NULL) && (yNode->isRed)) {
	  newNode->parent->isRed = false; //case 4
	  yNode->isRed = false;     //case 4
	  newNode->parent->parent->isRed = true; //case 4
	  newNode = newNode->parent->parent; //case 4
	}
	else if (newNode == newNode->parent->left) {
	  newNode = newNode->parent;          //case 5
	  rightRotate(newNode);   //case 5
	}
	if (newNode->parent != NULL) {
	  newNode->parent->isRed = false;    //case 6
	  if (newNode->parent->parent != NULL) {
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

int Tree::deleteNode(int x) {
  Node* node = findNode(root, x);
  if (node != NULL) {
    delete(remove(node));
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
