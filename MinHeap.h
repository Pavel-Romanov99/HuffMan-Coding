#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
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
//used for making the final_code
struct table {
	char data;
	string code;

	table(char data, string code) {
		this->data = data;
		this->code = code;
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
			//if the element is already there increase its frequency
			if (temp->data == str[j]) {
				temp->frequency++;
			}
		}
		//if the element is new
		if (!check(temp, v)) {
			v.push_back(temp);
		}
	}
	return v;
}


//what we compare on
struct compare {
	bool operator()(node* l, node* r)
	{
		return (l->frequency > r->frequency);
	}
};

//creates a huffman tree
node* HuffmanTree(vector<node*>& v, priority_queue<node*, vector<node*>, compare>& minHeap) {

	//push the chars and their freq into the minHeap
	for (int i = 0; i < v.size(); i++)
	{
		minHeap.push(v[i]);
	}

	node* left, * right;

	//while there is only one l
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

//we print the codes of the elements
void printCodes(node* root, string str, vector<table*>& v)
{
	if (root == nullptr) {
		return;
	}

	//if the node is not from the newly created nodes
	//then add its value and code to the vector
	if (root->data != '$') {
		table* temp = new table(root->data, str);
		v.push_back(temp);
	}

	printCodes(root->left, str + "0", v);
	printCodes(root->right, str + "1", v);
}

//create a code from the input and symbol codes
string createCode(string& input, vector<table*>& v1) {

	string code;
	for (int j = 0; j < input.length(); j++)
	{
		for (int i = 0; i < v1.size(); i++)
		{
			//when we see a symbol 
			if (input[j] == v1[i]->data) {
				//we add it's code to the final_code
				code += v1[i]->code;
				break;
			}
		}
	}
	//we return the final_code of all symbols
	return code;
}

//decode based on the root of the tree and the code
string decode(node* root, string code) {

	string answer = "";
	node* curr = root;

	for (int i = 0; i < code.size(); i++)
	{
		//we go through the tree based on the final_code
		//if we have a 0 then we go left, otherwise we go right
		if (code[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// reached leaf node 
		if (curr->left == NULL and curr->right == NULL)
		{
			//we add it to the final answer
			answer += curr->data;
			//then we start again from the root of the tree
			curr = root;
		}
	} 
	//we return the final decoded message
	return answer + '\0';
}

