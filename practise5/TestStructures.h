#ifndef _TESTSTRUCTURES_H
#define _TESTSTRUCTURES_H

#include "ManageFileByBinTree.h"
#include "ManageFileByAVLTree.h"
#include "ManageFileByHashTable.h"
#include <ctime>

void generateText(string textfile, int n) {
	ofstream fout(textfile,ios::trunc|ios::out|ios::app);
	int k;

	for (int i = 1;i <= n;i++) {
		k = rand() % n + 1;
		fout << k << endl << "Cinema" << endl << "Title" << 100 << endl;
	}

	fout.close();
}

void fromFileTostructures(string binfile, HashTable* HTable, Node* BinTree, AVLNode* AVLTree) {
	cout << "Elements number: " << 100000 << endl;
	for (int i = 1;i <= 100000;i++) {
		recordFromBinaryToTable(binfile, i, HTable);
	}
	cout << "Binary file nodes are inserted into hash table" << endl;

	createTreeFromFileNodes(binfile, BinTree);
	cout << "Binary file nodes are inserted into binary tree" << endl;

	createAVLTreeFromFileNodes(binfile, AVLTree);
	cout << "Binary file nodes are inserted into AVL tree" << endl;
}

void searchByStructures(string binfile, HashTable* HTable, Node* BinTree, AVLNode* AVLTree) {

	int key;
	int start, finish;
	film* F=new film();

	cout << endl << "Key for search: ";
	while (cin >> key) {

		start = clock();
		getFromBinByKey(binfile, key, HTable, F);
		finish = clock();
		cout << endl << "Hash table: " << finish - start << endl;

		start = clock();
		searchNodeInFileByTree(key, BinTree);
		finish = clock();
		cout << endl << "Binary tree: " << finish - start << endl;

		start = clock();
		searchNodeInFileByAVLTree(key, AVLTree);
		finish = clock();
		cout << endl << "AVL tree: " << finish - start << endl;
		cout << endl << "Key for search: ";
	}
}

#endif