#include "MinHeap.h"

//input from file
//decompress
//commands

int main()
{
	vector<node*> v = timesFound("abracadabraf");
	priority_queue<node*, vector<node*>, compare> minHeap;
	heapify(v, minHeap);
	HuffmanTree(minHeap);
}