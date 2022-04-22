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
  cout << "Delete: deletes a user specified node" << endl;
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
	
	
      }
    }
    
    else if (input == "File") {
      while (std::getline(fileInput, line)) {
	
      }
    }
    else if (input == "Delete") {
      
    }
    else if (input == "Find") {
      
    }
    else if (input == "Print") {
      
    }
    else if (input == "Quit") {
      break;
    }
  }
}
