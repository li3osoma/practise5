#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include "BinaryFile.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct Node {
	int key;
	film* ref;
	Node* parent;
	Node* left;
	Node* right;
	Node(){
		key = -1;
		ref = nullptr;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}
	Node(film* F) {
		key = F->id;
		ref = F;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	int height()
	{
		if (left == nullptr && right == nullptr) {
			return 0;
		}
		else if (left == nullptr) return right->height() + 1;
		else if (right == nullptr) return left->height() + 1;
		else return max(right->height(), left->height()) + 1;
	}
	void addLeft(Node* n) {
		left = new Node();
		left->parent = this;
		left->key=n->key;
		left->ref = n->ref;
	}
	void addRight(Node* n) {
		right = new Node();
		right->parent = this;
		right->key = n->key;
		right->ref = n->ref;
	}
	void addElement(Node* n) {
		if (this->parent == nullptr && this->key == -1) {
			this->key = n->key;
			this->ref = n->ref;
		}
		else{
			if (n->key < this->key){
				if (this->left == nullptr) this->addLeft(n);
				else this->left->addElement(n);
			}
			else {
				if (this->right == nullptr)	this->addRight(n);
				else this->right->addElement(n);
			}
		}
	}
	Node* searchKey(int k) {
		if (k == this->key) return this;
		else if (k < this->key) {
			if (left != nullptr) left->searchKey(k);
			else return nullptr;
		}
		else {
			if (right != nullptr) right->searchKey(k);
			else return nullptr;
		}
	}
	Node* searchMax() {
		if (right == nullptr) return this;
		else return right->searchMax();
	}
	Node* searchMin() {
		if (left == nullptr) return this;
		else return left->searchMin();
	}
	int deleteKey(int key) {
		Node* replace = new Node();
		Node* del = searchKey(key);

		if (del->left == nullptr && del->right == nullptr) {
			if (del->parent != nullptr) {
				if (del == del->parent->left) del->parent->left = nullptr;
				else del->parent->right = nullptr;
			}
		}
		else {
			if (del->left != nullptr) {
				replace = del->left->searchMax();

				if (replace == replace->parent->left) del->left = replace->left;
				else del->left = replace->parent;
				if (del->left != nullptr) del->left->parent = del;

			}
			else if (del->right != nullptr) {
				replace = del->right->searchMin();

				if (replace == replace->parent->right) del->right = replace->right;
				else del->right = replace->parent;
				if (del->right != nullptr) del->right = replace->right;
			}
			del->key = replace->key;
			del->ref = replace->ref;
			if (replace == replace->parent->left) replace->parent->left = nullptr;
			else if (replace == replace->parent->right) replace->parent->right = nullptr;
		}
		return 0;
	}
	void showTree() {
		vector<pair<Node*, int>> line;
		int level = 0;
		int max_elems = 0;
		for (int i = 0;i <= height();i++) {
			max_elems += pow(2, i);
		}
		line.push_back(make_pair(this, level));
		for (int i = 0;i < max_elems && i < line.size();i++) {

			level = line[i].second + 1;

			if (line[i].first->key != -1 && line[i].first->left != nullptr)
				line.push_back(make_pair(line[i].first->left, level));
			else line.push_back(make_pair(new Node(), level));

			if (line[i].first->key != -1 && line[i].first->right != nullptr)
				line.push_back(make_pair(line[i].first->right, level));
			else line.push_back(make_pair(new Node(), level));
		}

		int level_max = height();
		string step;
		for (int i = 0;i < line.size();i++) {
			step = string(pow(2, level_max - line[i].second) - 1, ' ');
			if (i == 0 || i > 0 && line[i].second != line[i - 1].second) {
				if (i != 0) cout << endl;
				if (line[i].first->key == -1) cout << step << " ";
				else cout << step << line[i].first->key;
			}
			else {
				if(line[i].first->key == -1) cout << step << step << " " <<" ";
				else cout << step << step << " " << line[i].first->key;
			}
		}
	}
	void show(int level) {
		if (right != nullptr) this->right->show(level + 1);
		for (int i = 0;i < level;i++) cout << "   ";
		cout << this->key << endl;
		if (left != nullptr) this->left->show(level + 1);
	}
};

#endif