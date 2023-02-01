#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include "BinaryFile.h"

//hash function
int hesh(int key, int length) {
	return key % length;
}

struct HashNode {
	int key;
	int indexInFile;
	bool isFree = true;
	bool isDeleted = false;
	HashNode() {
		key = -1;
		indexInFile = -1;
	}
	HashNode(film* F, int index) {
		key = F->id;
		indexInFile = index;
		isFree = false;
	}
};

struct HashTable {
	int length;
	int closedAddressesNum;
	int deletedNum;
	HashNode** node;
	HashTable(int l) {
		length = l;
		node = new HashNode * [length];
		closedAddressesNum = 0;
		deletedNum = 0;
		for (int i = 0;i < length;i++) {
			node[i] = new HashNode();
		}
	}

	//insert the key
	void insertIntoTable(HashNode* HNode) {

		if (length - closedAddressesNum <= length / 4) {
			rehash();
		}

		int ind = hesh(HNode->key, this->length);
		while (!node[ind]->isFree) {
			ind++;
		}
		if (ind < length) {
			node[ind] = HNode;
			closedAddressesNum++;
		}
	}

	//delete the key
	void deleteFromTable(HashNode* HNode) {
		int ind = hesh(HNode->key, length);
		while (!node[ind]->isFree && node[ind]->key != HNode->key && !node[ind]->isDeleted) {
			ind++;
		}
		if (ind < length) {
			node[ind]->isFree = true;
			node[ind]->isDeleted = true;
			closedAddressesNum--;
		}
	}

	//search the key
	HashNode* getNodeByKey(int key) {
		int ind = hesh(key, length);
		while (ind < length && node[ind]->key != key) {
			ind++;
			if (ind < length && node[ind]->key == key && node[ind]->isDeleted) ind++;
		}
		if (ind < length && !node[ind]->isDeleted) {
			return node[ind];
		}
		return nullptr;
	}

	//hash table containing
	void tableContaining() {
		int ind = 0;
		printf("%-12s", "ind");
		printf("%-12s", "key");
		printf("%-12s", "in file");
		printf("%-12s", "is free");
		printf("%-12s", "is del");
		cout << endl;
		while (ind < length) {
			printf("%-12d", ind);
			printf("%-12d", node[ind]->key);
			printf("%-12d", node[ind]->indexInFile);
			printf("%-12d", node[ind]->isFree);
			printf("%-12d", node[ind]->isDeleted);
			cout << endl;
			ind++;
		}
	}

	void rehash() {
		HashTable* HTableNew = new HashTable(length * 2);

		for (int i = 0;i < length;i++) {
			if (node[i]->isDeleted) {
				node[i]->indexInFile = -1;
				node[i]->key = -1;
				node[i]->isFree = true;
				node[i]->isDeleted = false;
			}
			if (node[i]->key != -1) HTableNew->insertIntoTable(node[i]);
		}
		length = length * 2;
		node = HTableNew->node;
	}

};
#endif

#pragma once
