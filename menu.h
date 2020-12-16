#include "MinHeap.h"

node* root;

void compress() {

	//get the input and output files
	string f1, f2;
	cout << "What file do you want to compress? - "; cin >> f1;
	cout << "Where do you want to write the results? - "; cin >> f2;

	//read the first line of the input file and save it in input
	ifstream input_file(f1);
	string input;
	if (input_file.good())
	{
		getline(input_file, input);
	}
	input_file.close();

	string code;
	//how many times a character is found in input file
	vector<node*> symbol_frequency = timesFound(input);
	//vector for the symbols and their codes
	vector<table*> symbol_codes;

	priority_queue<node*, vector<node*>, compare> minHeap;

	//create the tree and store its root
	root = HuffmanTree(symbol_frequency, minHeap, code);
	//print the codes and store them in symbol_codes
	printCodes(root, "", symbol_codes);

	//create the final code based on symbol codes and input
	string final_code = createCode(input, code, symbol_codes);

	double ratio = 1;
	ratio = (double)final_code.length() / (input.length() * 8);
	cout << "Compressed / Decompressed ratio = " << ratio << endl;

	//write the code into the output file
	ofstream output_file(f2);
	output_file << final_code;
	output_file.close();
}

void decompress() {

	//get the input and output files
	string f1, f2;
	cout << "What file do you want to decompress? - "; cin >> f1;
	cout << "Where to do want to write the decompressed code? - "; cin >> f2;

	//read the first line of the input file and save it in input
	ifstream input_file(f1);
	string code;
	if (input_file.good())
	{
		getline(input_file, code);
	}
	input_file.close();

	//write the decoded message into the output file
	ofstream output_file(f2);
	//decode based on the tree and code
	output_file << decode(root, code);
	output_file.close();
}

//for debug mode
int binaryToDecimal(string binaryString)
{
	int value = 0;
	int indexCounter = 0;
	for (int i = binaryString.length() - 1; i >= 0; i--) {

		if (binaryString[i] == '1') {
			value += pow(2, indexCounter);
		}
		indexCounter++;
	}
	return value;
}

void debugMode() {
	//get the input and output files
	string f1;
	cout << "What file do you want to debug? - "; cin >> f1;

	//read the first line of the input file and save it in input
	ifstream input_file(f1);
	string code;
	if (input_file.good())
	{
		getline(input_file, code);
	}
	input_file.close();
	
	string byte = "";
	int i = 0;
	int counter = 1;
	cout << "Debug Mode: ";
	while (code[i] != '\0') {
		byte += code[i];
		i++;
		counter++;
		if (counter == 8) {
			cout << binaryToDecimal(byte) << " ";
			byte = "";
			counter = 0;
		}
	}

}

void menu() {
	cout << "Welcome to my Huffman coding project" << endl;
	cout << "To compress a file press - c " << endl;
	cout << "To decompress a file press - d " << endl;
	cout << "Type ""exit"" to close" << endl;

	string command;
	while (true) {
		cout << "My command: ";
		cin >> command;
		if (command[0] == 'c' && command.length() == 1) {
			//read filename and compress it's contents
			compress();
			string choice;
			cout << "Type debug for debug mode or decompress to decompress" << endl; cin >> choice;
			while (true) {
				if (choice == "debug") {
					debugMode(); break;
				}
				else if (choice == "decompress") {
					decompress(); break;
				}
				else {
					cout << "Invalid input! Try again: " << endl;
					cin >> choice;
				}
			}
			break;
		}
		else if (command[0] == 'd' && command.length() == 1){
			//read filename and decompress the code inside of it
			string choice;
			cout << "You cannot decompress before compressing first" << endl;
			cout << "Do you wish to compress? - y or n" << endl; cin >> choice;
			if (choice == "y") {
				compress();
			}
			decompress();
			break;
		}
		else if (command == "exit") {
			cout << "See you next time! " << endl;
			return;
		}
		else cout << "Invalid command. Try again!" << endl;
	}
}

