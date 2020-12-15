#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct node {
	char data;
	int frequency;
	node* left, * right;

	//constructors
	node() {
		this->data = ' ';
		this->frequency = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
	node(char data, int freq) {
		this->data = data;
		this->frequency = freq;
	}
};

//what we compare on
struct compare {
	bool operator()(node* l, node* r)
	{
		return (l->frequency > r->frequency);
	}
};


//checks whether node s is in the vector
bool check(node* s, vector<node*> v) {
	for (int i = 0; i < v.size(); i++)
	{
		if (s->data == v[i]->data) {
			return true;
		}
	}
	return false;
}

//inserts the chars and their frequencies into a vector
vector<node*> timesFound(string str) {

	vector<node*> v;
	//so that the first element has the correct frequency
	int num = 1;

	for (int i = 0; i < str.length(); i++)
	{
		node* temp = new node();
		temp->data = str[i];
		temp->frequency = num;
		num = 0;

		for (int j = 1; j < str.length(); j++)
		{
			if (temp->data == str[j]) {
				temp->frequency++;
			}
		}
		if (!check(temp, v)) {
			v.push_back(temp);
		}
	}
	return v;
}

//inserts all the nodes in order of least frequent one to the most
void heapify(vector<node*>& v, priority_queue<node*, vector<node*>, compare>& minHeap) {
	for (int i = 0; i < v.size(); i++)
	{
		minHeap.push(v[i]);
	}
}

//print the heap
void printHeap(priority_queue<node*, vector<node*>, compare>& minHeap) {

	while (!minHeap.empty())
	{
		cout << minHeap.top()->data << " " << minHeap.top()->frequency << endl;
		minHeap.pop();
	}
}

//we print the codes of the elements
void printCodes(node* root, string str)
{
	if (root == nullptr) {
		return;
	}

	if (root->data != '$') {
		cout << root->data << ": " << str << "\n";
	}

	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

void HuffmanTree(priority_queue<node*, vector<node*>, compare>& minHeap) {

	node* left, * right;

	while (minHeap.size() != 1) {

		//remove the 2 node with least freq
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		//create a new node with added frequencies
		node* top = new node('$', left->frequency + right->frequency);
		top->left = left;
		top->right = right;

		//push the new node into the heap
		minHeap.push(top);
	}
	//print tree with the codes of the symbols
	printCodes(minHeap.top(), "");
}

