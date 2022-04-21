#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <assert.h>

using namespace std;

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

/* tree function
//make root
  struct Node* root = new Node(1);

  //follow tree
  root->left = new Node(2);
  root->right = new Node(3);

  root->left = new Node(4);

  return 0;
 */




// Driver program to test above functions
int main() {
  
  ifstream fileInput("input.txt");
  string line;
  string input;
  string tempStr;
  int tempInt;
  int inputNum;
  vector<int> inputVect;
  
  cout << "Commands (Case Sensitive):" << endl;
  cout << "Line: enter a list of numbers in the input line" << endl;
  cout << "File: will use the list of names provided on the .txt file included" << endl;
  cin >> input;
  
  if (input == "Line") {
    int numofNum, i;
    cout << "How many number will you enter?" << endl;
    cin >> numofNum;
    
    
    for (i = 1; i <= numofNum; i++) {
      cout << "Enter number " << (i) << endl;
      cin >> tempInt;
      thisHeap.insert(tempInt);
      cout << endl << "Size of array: " << thisHeap.getCount() << endl;
    }
  }
  
  else if (input == "File") {
    while (std::getline(fileInput, line)) {
      thisHeap.insert(std::atoi(line.c_str()));
    }
  }
  while (thisHeap.getCount() > 0) {
    cout << thisHeap.rmMax() << endl;
  }
}
