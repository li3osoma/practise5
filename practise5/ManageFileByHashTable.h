#ifndef _BINARYFILEANDHASHTABLE_H
#define _BINARYFILEANDHASHTABLE_H

#include "BinaryFile.h"
#include "HashTable.h"

//read record from file and insert into table
int recordFromBinaryToTable(string binfile, int recordIndex, HashTable* HTable) {
	film* F = new film();;
	int res;
	res = searchFilmInBinByNumber(binfile, recordIndex, F);
	if (res) return res;
	HashNode* HNode = new HashNode(F, recordIndex);
	HTable->insertIntoTable(HNode);
	return 0;
}

//delete from table and from file
int deleteFromTableAndFromFile(string binfile, HashTable* HTable, int key) {
	int res = deleteFilmById(binfile, key);
	if (res) return res;
	HashNode* HNode = HTable->getNodeByKey(key);
	if (HNode == nullptr) return 2;
	HTable->deleteFromTable(HNode);
	return 0;
}

//find in table by key and get in file
int getFromBinByKey(string binfile, int key, HashTable* HTable, film* F) {
	HashNode* HNode = HTable->getNodeByKey(key);
	if (HNode == nullptr) return 2;
	int res = searchFilmInBinByNumber(binfile, HNode->indexInFile, F);
	return res;
}

#endif
#pragma once
