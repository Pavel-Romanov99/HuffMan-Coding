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

//contains the symbol and it's code
struct table {
	char data;
	string code;

	table(char data, string code) {
		this->data = data;
		this->code = code;
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


//we print the codes of the elements
void printCodes(node* root, string str, vector<table*> &v)
{
	if (root == nullptr) {
		return;
	}

	if (root->data != '$') {
		cout << root->data << ": " << str << "\n";
		table *temp = new table(root->data, str);
		v.push_back(temp);
	}

	printCodes(root->left, str + "0", v);
	printCodes(root->right, str + "1", v);
}

node* HuffmanTree(vector<node*>& v, priority_queue<node*, vector<node*>, compare>& minHeap, string &code) {


	for (int i = 0; i < v.size(); i++)
	{
		minHeap.push(v[i]);
	}


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
	return minHeap.top();
}

//decode based on the root of the tree and the code
string decode(node* root, string code) {

	string answer = "";
	node* curr = root;

	for (int i = 0; i < code.size(); i++)
	{
		if (code[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// reached leaf node 
		if (curr->left == NULL and curr->right == NULL)
		{
			answer += curr->data;
			curr = root;
		}
	} 
	return answer + '\0';
}

//create a code from the input and symbol codes
string createCode(string& input, string& code, vector<table*>& v1) {
	for (int j = 0; j < input.length(); j++)
	{
		for (int i = 0; i < v1.size(); i++)
		{
			if (input[j] == v1[i]->data) {
				code += v1[i]->code;
				break;
			}
		}
	}
	return code;
}