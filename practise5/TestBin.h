#ifndef _TESTBIN_H
#define _TESTBIN_H

#include "ManageFileByBinTree.h"

void test1(string binfile,Node* Tree) {
	int res=createTreeFromFileNodes(binfile,Tree);
	if (Tree!=nullptr) {
		cout << "Created binary tree containing: " << endl;
		Tree->showTree();
		cout << endl << "Binary tree is created" << endl;
	}
	else cout << "Tree can't be created" << endl;
}

void test2(Node* Tree) {
	int key;
	film* F=new film();
	cout << "Search binary file node by binary tree: " << endl;
	cout << "Input the key: ";
	while (cin >> key) {
		F = searchNodeInFileByTree(key, Tree);
		if (F != nullptr) {
			cout << "Found node: " << endl;
			cout << F->id << endl << F->theatre << endl 
				<< F->title << endl << F->freeplaces << endl;
		}
		else cout << "Key isn't found" << endl;
		cout << endl << "Input the key: ";
	}
}
void test3(string binfile,Node* Tree) {
	int key;
	film* F = new film();
	cout << endl<<"Delete binary file node by binary tree: " << endl;
	cout << "Created tree containing: " << endl;
	Tree->showTree();
	cout <<endl<< "Input the key: ";
	while (cin >> key) {
		int res=deleteFromFileByTree(binfile, key, Tree);
		if (res==0) {
			cout << endl<<"The key is deleted" << endl;
			cout << "Created tree containing: " << endl;
			Tree->showTree();
		}
		else cout << "Key isn't found" << endl;
		cout << endl << "Input the key: ";
	}
}

#endif
