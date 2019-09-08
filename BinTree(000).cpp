#include<iostream>

using namespace std;


class BinTreeNode {
public:
	int value, key;
	BinTreeNode *pLeft, *pRight;
};

BinTreeNode binTreeNodePool[1000000];
int binTreeNodePoolIndex = 0;

void BonTreeNode() {
	binTreeNodePoolIndex = 0;
}

BinTreeNode* NewBinTreeNode() {
	binTreeNodePool[binTreeNodePoolIndex].value = 0;
	binTreeNodePool[binTreeNodePoolIndex].pLeft = 0;
	binTreeNodePool[binTreeNodePoolIndex].pRight = 0;

	return &binTreeNodePool[binTreeNodePoolIndex++];
}

class BinTree {
public:
	int cnt;
	BinTreeNode *root;	//시작과 동시에 값이 설정 되어야 한다.

	void Init(){
		cnt = 0;
		root = NewBinTreeNode();
	}

	bool Insert(int key, int value) {
		BinTreeNode *parent;
		BinTreeNode *child = root;

		while (1) {			
			
			if (root->key == key)
				return false;

			if (parent->key < key)
				child = parent->pRight;
			else if (parent->key > key)
				child = parent->pLeft;

			if (child == 0) {
				child = NewBinTreeNode();
				child->key = key;
				child->value = value;
				child->pLeft = 0;
				child->pRight = 0;
				return true;
			}

			parent = child;
		}
	}

	BinTreeNode* Find(int key) {
		BinTreeNode *parent = root;
		BinTreeNode *child;
		while (1) {
			if (parent->key == key)
				return parent;
		
			if (parent->key < key)
				child = parent->pRight;
			else if (parent->key > key)
				child = parent->pLeft;

			if (child == 0)
				return 0;
			
			parent = child;
		}
	}

	BinTreeNode* Erase(int key) {
		BinTreeNode *parent = 0;
		BinTreeNode *child = root;

		while (1) {
			if (child->key == key) {
				if (child->pLeft == 0 && child->pRight == 0) {
					//자식이 없을경우	
					if (parent->pRight == child)
						parent->pRight = 0;
					else
						parent->pLeft = 0;
				}
				else if ((child->pLeft == 0 && child->pRight != 0)||(child->pLeft != 0 && child->pRight == 0)) {
					//자식이 하나 일 경우
				
					if (parent != 0) {
						if (parent->pRight == child) {
							if (child->pLeft != 0)
								parent->pRight = child->pLeft;
							else
								parent->pRight = child->pRight;
						}
					}
					else if (parent == 0) {
						if (parent->pLeft == child) {
							if (child->pLeft != 0)
								root = child->pLeft;
							else
								root = child->pRight;
						}
					}
				}
				else {
					//자식이 둘일 경우
					//왼쪽 자식부터 시작, 제일 오른쪽에 있는 자식을 지워야할 위치까지 옮긴다.

				}



			}

			parent = child;

			if (parent->key < key)
				child = parent->pRight;
			else if (parent->key > key)
				child = parent->pLeft;

			if (child == 0)
				return;
		}
	}



};


int main(void) {


	return 0;
}
