#ifndef _FILEBYBIN_H
#define _FILEBYBIN_H

#include "BinaryTree.h"

int createTreeFromFileNodes(string binfile,Node* Tree) {
	int res;

	for (int i = 1;i <= recordsNum;i++) {
		film* F = new film();
		res = searchFilmInBinByNumber(binfile, i, F);
		if (res) return res;
		if (F != nullptr){
			Node* n = new Node(F);
			Tree->addElement(n);
			n->~Node();
		}
		F->~film();
	}
	return 0;
}

film* searchNodeInFileByTree(int key,Node* Tree) {
	Node* n = Tree->searchKey(key);
	if (n != nullptr) {
		return n->ref;
	}
	else return nullptr;
}

int deleteFromFileByTree(string binfile,int key,Node* Tree) {
	Node* n = Tree->searchKey(key);
	int res=1;
	if (n != nullptr) {
		res=Tree->deleteKey(key);
		if(res==0) deleteFilmById(binfile, n->ref->id);
	}
	return res;
}
#endif
