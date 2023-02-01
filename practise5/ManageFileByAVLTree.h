#ifndef _FILEBYAVL_H
#define _FILEBYAVL_H

#include "AVLTree.h"

int createAVLTreeFromFileNodes(string binfile, AVLNode* Tree) {
	int res;
	for (int i = 1;i <= recordsNum;i++) {
		film* F = new film();
		res = searchFilmInBinByNumber(binfile, i, F);
		if (res) return res;
		if (F != nullptr) {
			AVLNode* n = new AVLNode(F);
			Tree->addElementAVL(n);
			//cout << endl << "Created AVL tree containing: " << endl;
			//Tree->showTree();
		}
		F->~film();
	}
	return 0;
}

film* searchNodeInFileByAVLTree(int key, AVLNode* Tree) {
	AVLNode* n = Tree->searchKey(key);
	if (n != nullptr) {
		return n->ref;
	}
	else return nullptr;
}

int deleteFromFileByAVLTree(string binfile, int key, AVLNode* Tree) {
	AVLNode* n = Tree->searchKey(key);
	int res = 1;
	if (n != nullptr) {
		res = Tree->deleteKeyAVL(key);
		if (res == 0) deleteFilmById(binfile, n->ref->id);
	}
	return res;
}

#endif

