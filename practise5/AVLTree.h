#ifndef _AVLTREE_H
#define _AVLTREE_H

#include "BinaryFile.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int static roteNum = 0;

struct AVLNode {
	int key;
	film* ref;
	AVLNode* parent;
	AVLNode* left;
	AVLNode* right;
	int balance=0;
	int h=0;
	AVLNode() {
		key = -1;
		ref = nullptr;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		balance = 0;
		h = 0;
	}
	AVLNode(film* F) {
		key = F->id;
		ref = F;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		balance = 0;
		h = 0;
	}

	int height()
	{
		if (left == nullptr && right == nullptr) {
			h = 0;
		}
		else if (left == nullptr) h = right->height() + 1;
		else if (right == nullptr) h = left->height() + 1;
		else h = max(right->height(), left->height()) + 1;

		return h;
	}

	void addLeft(AVLNode* n) {
		left = new AVLNode();
		left->parent = this;
		left->key = n->key;
		left->ref = n->ref;
	}
	void addRight(AVLNode* n) {
		right = new AVLNode();
		right->parent = this;
		right->key = n->key;
		right->ref = n->ref;
	}

	void balanceL() {
		AVLNode* old_root=new AVLNode();
		AVLNode* new_root=new AVLNode();

		old_root->key = this->key;
		old_root->ref = this->ref;
		new_root->key = this->right->key;
		new_root->ref = this->right->ref;

		if (this->right->right != nullptr) {
			new_root->right = this->right->right;
			new_root->right->parent = new_root;
		}
		if (this->right->left != nullptr) {
			old_root->right = this->right->left;
			old_root->right->parent = old_root;
		}
		if (this->left != nullptr) {
			old_root->left = this->left;
			old_root->left->parent = old_root;
		}

		old_root->parent = new_root;
		new_root->left = old_root;

		if (this->parent != nullptr) {
			if (this->parent->left == this) this->parent->left = new_root;
			else this->parent->right = new_root;
			new_root->parent = this->parent;
		}
		else new_root->parent = nullptr;
	}
	void balanceR() {
		AVLNode* old_root=new AVLNode();
		AVLNode* new_root=new AVLNode();

		old_root->key = this->key;
		old_root->ref = this->ref;
		new_root->key = this->left->key;
		new_root->ref = this->left->ref;

		if (this->left->left != nullptr) {
			new_root->left = this->left->left;
			new_root->left->parent = new_root;
		}

		if (this->right != nullptr) {
			old_root->right = this->right;
			old_root->right->parent = old_root;
		}

		if (this->left->right != nullptr) {
			old_root->left = this->left->right;
			old_root->left->parent = old_root;
		}

		old_root->parent = new_root;
		new_root->right = old_root;

		if (this->parent != nullptr) {
			if (this->parent->left == this) this->parent->left = new_root;
			else this->parent->right = new_root;
			new_root->parent = this->parent;
		}
		else new_root->parent = nullptr;
	}
	void balanceLR() {
		this->left->balanceL();
		this->balanceR();

	}
	void balanceRL() {
		this->right->balanceR();
		this->balanceL();
	}

	void setHeightAndBalance(AVLNode* current) {
		if (current->left == nullptr && current->right == nullptr) {
			current->h = 0;
			current->balance = 0;
		}
		else if (current->left != nullptr && current->right == nullptr) {
			current->h = current->left->h + 1;
			current->balance = -current->h;
		}
		else if (current->left == nullptr && current->right != nullptr) {
			current->h = current->right->h + 1;
			current->balance = current->h;
		}
		else {
			int hl = current->left->h;
			int hr= current->right->h;
			if (hl > hr) current->h=hl + 1;
			else current->h = hr + 1;
			current->balance = hr-hl;
		}
	}
	void addElementAVL(AVLNode* n) {
		AVLNode* current=new AVLNode();
		int lr=0, rl=0;
		if (this->parent == nullptr && this->key == -1) {
			this->key = n->key;
			this->ref = n->ref;
		}
		else {
			if (n->key < this->key) {
				if (this->left == nullptr) {
					this->addLeft(n);

					current = this->left;
					setHeightAndBalance(current);
					while (current->parent != nullptr && current->balance >= -1 
						&& current->balance <= 1) {
						if (current == current->parent->right) rl = 1;
						current = current->parent;
						setHeightAndBalance(current);
					}
					if (current->balance < -1 || current->balance > 1) {
						if (rl) {
							current->balanceRL();
						}
						else {
							current->balanceR();
						}
					}
				}
				else {
					this->left->addElementAVL(n);
				}
			}
			else {
				if (this->right == nullptr) {
					this->addRight(n);

					current = this->right;
					setHeightAndBalance(current);
					while (current->parent != nullptr && current->balance >= -1 
						&& current->balance <= 1) {
						if (current == current->parent->left) lr = 1;
						current = current->parent;
						setHeightAndBalance(current);
					}
					if (current->balance > 1 || current->balance < -1) {
						if (lr) {
							current->balanceLR();
						}
						else {
							current->balanceL();
						}
					}
				}
				else {
					this->right->addElementAVL(n);
				}
			}
		}
	}

	AVLNode* searchKey(int k) {
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

	AVLNode* searchMax() {
		if (right == nullptr) return this;
		else return right->searchMax();
	}
	AVLNode* searchMin() {
		if (left == nullptr) return this;
		else return left->searchMin();
	}
	int deleteKeyAVL(int key) {
		AVLNode* replace=new AVLNode();
		AVLNode* del = searchKey(key);
		AVLNode* check=new AVLNode();

		if (del->left == nullptr && del->right == nullptr) {
			if (del->parent != nullptr) {
				check = del->parent;
				if (del == del->parent->left) del->parent->left = nullptr;
				else del->parent->right = nullptr;
			}
		}
		else {
			if (del->left != nullptr) {
				replace = del->left->searchMax();
				check = replace->parent;

				if (replace == replace->parent->left) del->left = replace->left;
				else del->left = replace->parent;
				if(del->left!=nullptr) del->left->parent = del;

			}
			else if (del->right != nullptr) {
				replace = del->right->searchMin();
				check = replace->parent;

				if (replace == replace->parent->right) del->right = replace->right;
				else del->right = replace->parent;
				if(del->right!=nullptr) del->right = replace->right;
			}
			del->key = replace->key;
			del->ref = replace->ref;
			if (replace == replace->parent->left) replace->parent->left = nullptr;
			else if (replace == replace->parent->right) replace->parent->right = nullptr;
		}
		int lr = 0, rl = 0;
		setHeightAndBalance(check);
		while (check->parent != nullptr && check->balance >= -1 && check->balance <= 1) {
			check = check->parent;
			setHeightAndBalance(check);
		}
		if (check->balance < -1) {
			setHeightAndBalance(check->left);
			if (check->left->balance >= 1) check->balanceLR();
			else check->balanceR();
		}
		if (check->balance > 1) {
			setHeightAndBalance(check->right);
			if (check->right->balance <= -1) check->balanceRL();
			else check->balanceL();
		}
		return 0;
	}

	void showTree() {
		AVLNode* current = this;
		while (current->parent != nullptr) {
			current = current->parent;
		}

		vector<pair<AVLNode*, int>> line;
		int level = 0;
		int max_elems = 0;
		int level_max = height();
		for (int i = 0;i <= level_max;i++) {
			max_elems += pow(2, i);
		}
		line.push_back(make_pair(current, level));
		for (int i = 0;i < max_elems && i < line.size();i++) {

			level = line[i].second + 1;

			if (line[i].first->key != -1 && line[i].first->left != nullptr)
				line.push_back(make_pair(line[i].first->left, level));
			else line.push_back(make_pair(new AVLNode(), level));

			if (line[i].first->key != -1 && line[i].first->right != nullptr)
				line.push_back(make_pair(line[i].first->right, level));
			else line.push_back(make_pair(new AVLNode(), level));
		}

		string step;
		for (int i = 0;i < line.size();i++) {
			step = string(pow(2, level_max - line[i].second) - 1, ' ');
			if (i == 0 || i > 0 && line[i].second != line[i - 1].second) {
				if (i != 0) cout << endl;
				if (line[i].first->key == -1) cout << step << " ";
				else cout << step << line[i].first->key;
			}
			else {
				if (line[i].first->key == -1) cout << step << step << " " << " ";
				else cout << step << step << " " << line[i].first->key;
			}
		}
	}	
};

#endif
