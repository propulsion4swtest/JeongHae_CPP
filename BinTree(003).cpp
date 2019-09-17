#include<iostream>

using namespace std;

class BinTreeNode {
public:
	int key, value;
	BinTreeNode *parent, *left, *right;
};

BinTreeNode binTreeNodePool[30000];
int binTreeNodeIndex;

void InitBinTreeNodePool() {
	binTreeNodeIndex = 0;
}

BinTreeNode* NewBinTreeNode() {
	int tmp = binTreeNodeIndex;
	binTreeNodeIndex++;

	binTreeNodePool[tmp].key = -1;
	binTreeNodePool[tmp].value = -1;
	binTreeNodePool[tmp].parent = 0;
	binTreeNodePool[tmp].left = 0;
	binTreeNodePool[tmp].right = 0;

	return &binTreeNodePool[tmp];
}


class BinTree {
public:
	BinTreeNode * root;

	void Init() {
		root = 0;
	}


	void Insert(int key, int value) {
		BinTreeNode *parent = 0, *child = root;
		BinTreeNode **p = 0;
		
		while (1) {
			if (child == 0) {
				//이곳에 삽입한다.
				BinTreeNode *newNode = NewBinTreeNode();
				newNode->key = key;
				newNode->value = value;

				if (child == root) {
					root = newNode;
				}
				else {
					*p = newNode;
					newNode->parent = parent;
				}

				return;
			}

			if (child->key == key)
				return;

			parent = child;
			if (child->key < key) {
				child = child->right;
				p = &parent->right;
			}
			else {
				child = child->left;
				p = &parent->left;
			}
		}
	}

	BinTreeNode* Find(int key) {
		BinTreeNode *finder = root;
		while (1) {
			if (finder == 0)
				return 0;
			
			if (finder->key == key) 
				return finder;
			
			if (finder->key < key)
				finder = finder->right;
			else
				finder = finder->left;

		}
	}


	void Erase(int key) {
		BinTreeNode *eraser;
		eraser = Find(key);
		if (eraser == 0)
			return;

		BinTreeNode *parent = 0, **p = 0;
		if (eraser != root) {
			parent = eraser->parent;
			if (parent->right == eraser)
				p = &parent->right;
			else
				p = &parent->left;
		}

		if (eraser->left == 0 && eraser->right == 0) {
			//자식이 하나도 없을 경우
			if (eraser == root)
				root = 0;
			else
				*p = 0;
		}
		else if (eraser->left == 0 && eraser->right != 0) {
			//오른쪽에만 자식이 있을 경우
			if (eraser == root) {
				root = eraser->right;
				eraser->right->parent = 0;
			}
			else {
				*p = eraser->right;
				eraser->right->parent = eraser->parent;
			}
		}
		else if (eraser->left != 0 && eraser->right == 0) {
			//오른쪽에만 자식이 있을 경우
			if (eraser == root) {
				root = eraser->left;
				eraser->left->parent = 0;
			}
			else {
				*p = eraser->left;
				eraser->left->parent = eraser->parent;
			}
		}
		else if (eraser->left != 0 && eraser->right != 0) {
			//자식이 양쪽 다 있을경우
			BinTreeNode *newNode = eraser->left;
			while (1) {
				if (newNode->right == 0)
					break;
				newNode = newNode->right;
			}

			Erase(newNode->key);

			if (eraser == root) {
				root = newNode;
				newNode->parent = 0;
			}
			else {
				*p = newNode;
				newNode->parent = parent;
			}

			newNode->left = eraser->left;
			newNode->right = eraser->right;

			if (eraser->left != 0) 
				newNode->left->parent = newNode;

			if (eraser->right != 0)
				newNode->right->parent = newNode;
		}
	}	
};


int main(void) {
	BinTree tree;
	InitBinTreeNodePool();
	tree.Init();

	int N;
	cin >> N;
	int input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		tree.Insert(input, input);
	}

	tree.Erase(150);

	return 0;
}


/*

9
100
50
150
25
75
125
175
10
80


5
10
20
30
40
50

*/
