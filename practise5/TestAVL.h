#ifndef _TESTAVL_H
#define _TESTAVL_H

#include "ManageFileByAVLTree.h"

void test4(string binfile, AVLNode* Tree) {
	int res = createAVLTreeFromFileNodes(binfile, Tree);
	if (Tree != nullptr) {}
	else cout << "Tree can't be created" << endl;
}

void test5(AVLNode* Tree) {
	int key;
	film* F = new film();
	cout << endl<<"Search binary file node by AVL tree: " << endl;
	cout << "Input the key: ";
	while (cin >> key) {
		F = searchNodeInFileByAVLTree(key, Tree);
		if (F != nullptr) {
			cout << "Found node: " << endl;
			cout << F->id << endl << F->theatre << endl
				<< F->title << endl << F->freeplaces << endl;
		}
		else cout << "Key isn't found" << endl;
		cout << endl << "Input the key: ";
	}
}

void test6(string binfile, AVLNode* Tree) {
	int key;
	film* F = new film();
	cout << endl << "Delete binary file node by AVL tree: " << endl;
	cout << "Created tree containing: " << endl;
	Tree->showTree();
	cout << endl << "Input the key: ";
	while (cin >> key) {
		int res = deleteFromFileByAVLTree(binfile, key, Tree);
		if (res == 0) {
			cout << endl << "The key is deleted" << endl;
			cout << "AVL tree containing: " << endl;
			Tree->showTree();
		}
		else cout << "Key isn't found" << endl;
		cout << endl << "Input the key: ";
	}
}



#endif