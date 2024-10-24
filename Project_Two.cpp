#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Define the structure that will hold course information
struct Courses {
	string courseId;
	string courseName;
	vector <string> prereqs;
};

// Create the internal structure for the tree node
struct Node {
	Courses course;
	Node* left;
	Node* right;

	// Create the default constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// Initialize with the course
	Node(Courses aCourse) :Node() {
		course = aCourse;
	}
};

// Define a class containing the data members and methods that will be used to implement the binary search tree
class BinarySearchTree {

private:
	Node* root;

	void addNode(Node* node, Courses course);
	void inOrder(Node* node);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void Insert(Courses course);
	void InOrder();
	Courses Search(string courseId);

};

/*
* Default Counstructor
*/
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}
//Destructor
BinarySearchTree::~BinarySearchTree() {
}

/*
* Insert a course
*/
void BinarySearchTree::Insert(Courses course) {
	// This will add a new root if the root is empty
	if (root == nullptr) {
		root = new Node(course);
	}
	else {
		// This will add a Node root and course
		this->addNode(root, course);
	}
}

/*
* Add course to some node (recursive)
*
* @param node Current node in tree
* @param course Courses to be added
*/

void BinarySearchTree::addNode(Node* node, Courses course) {
	// If node is greater than course, add to left subtree
	if (node->course.courseId.compare(course.courseId) > 0) {
		if (node->left == nullptr) {
			node->left = new Node(course);
		}
		// If left node exists, keep going down the left subtree
		else {
			this->addNode(node->left, course);
		}
	}
	// If node is less than course, add to right subtree
	else {
		if (node->right == nullptr) {
			node->right = new Node(course);
		}
		//If right node exists, keep going down the right subtree
		else {
			this->addNode(node->right, course);
		}
	}
}

/*
* Travel through the tree in order
*/
void BinarySearchTree::InOrder() {
	this->inOrder(root);
}

void BinarySearchTree::inOrder(Node* node) {
	// If node is not equal to null ptr
	if (node != nullptr) {

		// InOrder node left
		inOrder(node->left);

		// Output the course ID, course Name and prereqs
		cout << node->course.courseId << ", " << node->course.courseName << endl;

		// InOrder node right
		inOrder(node->right);
	}
}

/*
* Create a search for a course
*/
Courses BinarySearchTree::Search(string courseId) {

	// We have to set the current node equal to the root
	Node* current = root;

	// Keep traveling down the tree until the bottom is reached or we find a matching bidId
	while (current != nullptr) {
		if (current->course.courseId.compare(courseId) == 0) {
			return current->course;
		}
		if (courseId.compare(current->course.courseId) < 0) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	Courses course;
	return course;
}

// Create a method to display the course information
void displayCourse(Courses course) {
	cout << course.courseId << ", " << course.courseName << endl;
	cout << "Prerequisites: ";

	// If prereuqisite vector is zero
	if (course.prereqs.size() == 0) {
		cout << "No prerequisites required";
	}
	else {
		// Print the prerequisite at index zero
		cout << course.prereqs.at(0);

		// Starting at index 1 and printing any additional prerequiste courses needed, without any range errors
		for (unsigned int i = 1; i < course.prereqs.size(); ++i) {
			cout << ", " << course.prereqs.at(i);
		}
	}
	return;
}

/*
* Open the file and parses the lines at the comma
* @parm fileName, BinarySearch Tree bst
*/

void courseLoader(string fileName, BinarySearchTree* bst) {
	// Variables
	string token;
	string line;

	int nCount = 0;

	// Read the data from the file and displays it
	ifstream myFile;

	// Open the file
	myFile.open(fileName, ios::in);

	// If file is open get a line and split it at the comma
	if (myFile.is_open()) {
		cout << "File is open" << endl;
		while (getline(myFile, line)) {
			vector <string> prereqs;
			stringstream ss(line);

			// Scope and object that will set the structure variables
			Courses course;
			nCount = 1;

			// First pass splists the line at the comma. It will take the first element, then increments the count, and continue.
			// Once the line is finished, the count will reset to 1 and continue to the next line.
			while (getline(ss, token, ',')) {
				if (nCount == 1) {

					// Store the token at position 1 in the course structure
					course.courseId = token;
				}
				// Store the token at position 2 in the course structure
				if (nCount == 2) {
					course.courseName = token;
				}
				// Pushes the elements in a line at position 2 greater than 2 to a vector
				if (nCount > 2) {
					prereqs.push_back(token);
				}
				++nCount;
			}

			// Iterate over the vector to push the elements into the structure vector
			for (unsigned int i = 0; i < prereqs.size(); ++i) {
				course.prereqs.push_back(prereqs.at(i));
			}

			// Inserts the structure vaiable elements to the Binary Search Tree
			bst->Insert(course);
		}
	}
	else {
		cout << "File could not be opened" << endl;
	}
};

int main() {
	// Variables
	int menuSelection;
	string fileName;
	string courseSearch;

	// Define a binary search tree to hold all bids
	BinarySearchTree* bst;
	bst = new BinarySearchTree();
	Courses course;

	do {
		// Create a while loop for the menu selection
		cout << endl;
		cout << "     Course Planner     " << endl;
		cout << "------------------------" << endl;
		cout << "1) Load Course Info     " << endl;
		cout << "2) Print All Courses    " << endl;
		cout << "3) Print Course Info    " << endl;
		cout << "9) Exit                 " << endl;
		cout << "------------------------" << endl;
		cout << endl;

		do {
			// Create a while loop for the user input validation

			cin >> menuSelection;
			if (cin.fail()) {
				cin.clear(); // This clears the cin
				cin.ignore(80, '\n');
			}
		} while (cin.fail()); // Creates a while loop until cin.fail is false

		// Passes the user menu selection to a switch case
		switch (menuSelection) {
		case 1:
			cout << "Enter the file name: " << endl;
			// This will hold the user input
			cin >> fileName;
			// This will call the course loader method and passes the file name and bst method
			courseLoader(fileName, bst);
			cout << endl;
			break;
		case 2:
			cout << "Here is your sample schedule: " << endl;
			cout << endl;
			// This will call the inOrder Method of the bst, which should automatically sort it alphabetically
			bst->InOrder();
			break;
		case 3:
			cout << "Which course would you like to know about?" << endl;
			cin >> courseSearch;

			// Converts lowercase user input to upper case for the search method
			for (int i = 0; courseSearch[i] != '\0'; i++) {
				if (courseSearch[i] >= 'a' && courseSearch[i] <= 'z')
					courseSearch[i] = courseSearch[i] - 32;
			}
			cout << endl;
			// Pass the searched course into the search method
			course = bst->Search(courseSearch);

			if (!course.courseId.empty()) {
				displayCourse(course);
			}
			else {
				cout << "Course " << courseSearch << " not found";
			}
			cout << endl;
			break;
		case 9:
			cout << "Thank you. You are now exiting the course planner." << endl;
			cout << endl;
			break;
		default:
			cout << menuSelection << " is not a valid option." << endl;
			cout << endl;
			break;
		}
		// Menu Exit Selection
	} while (menuSelection != 9);
	return 0;
}