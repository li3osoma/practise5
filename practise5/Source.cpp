#include "TestStructures.h"

int main() {
	Node* BinTree=new Node();
	AVLNode* AVLTree = new AVLNode();
	HashTable* HTable=new HashTable(recordsNum);
	string textfile, binfile;

	cout << "Text file name (without .txt): ";
	cin >> textfile;
	generateText(textfile + ".txt",100000);
	cout << endl;

	cout << "Confirming text file to binary file" << endl;
	cout << "Text file name (without .txt): ";
	cin >> textfile;
	cout << "Binary file name (without .txt): ";
	cin >> binfile;
	//fromTextToBin(textfile + ".txt", binfile + ".txt");
	//cout << endl;
	//fromFileTostructures(binfile + ".txt", HTable, BinTree, AVLTree);
	//searchByStructures(binfile + ".txt", HTable, BinTree, AVLTree);
	return 0;
}
