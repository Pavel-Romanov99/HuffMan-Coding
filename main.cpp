#include "MinHeap.h"

//input from file
//decompress
//commands



int main()
{
	string input = "ABRACADABRA";
	string code = "";

	vector<node*> v = timesFound(input);
	vector<table*> v1;

	priority_queue<node*, vector<node*>, compare> minHeap;


	node* root = HuffmanTree(v, minHeap, code);
	printCodes(root, "", v1);
	cout << "Code is: " << createCode(input, code, v1) << endl;
	cout << "Decoded: " << decode(root, code) << endl;
}