#include<iostream>

using namespace std;

class TreeNode {
public:
	int value;
	TreeNode *left, *right, *parent;
};

TreeNode treeNodePool[1500000];
int treeNodePoolIndex;

TreeNode* NewTreeNode() {
	int tmp = treeNodePoolIndex;
	treeNodePoolIndex++;
	treeNodePool[tmp].value = -1;
	treeNodePool[tmp].left = 0;
	treeNodePool[tmp].right = 0;
	treeNodePool[tmp].parent = 0;

	return &treeNodePool[tmp];
}

class Tree {
public:
	TreeNode * root;

	void Init() {
		root = 0;
	}

	void Insert(int value) {
		TreeNode *parent = 0, *finder = root, **p = 0;

		while (1) {
			if (finder == 0) {
				TreeNode *newNode = NewTreeNode();
				newNode->value = value;
				if (root == 0) {
					root = newNode;
				}
				else {
					*p = newNode;
					newNode->parent = parent;
				}
				return;
			}

			parent = finder;
			if (value >= finder->value) {
				p = &parent->right;
				finder = finder->right;
			}
			else {
				p = &parent->left;
				finder = finder->left;
			}
		}
	}

	TreeNode* Find(int value) {
		TreeNode *finder = root;
		while (1) {
			if (finder == 0)				
				return 0;
			
			if (finder->value == value)
				return finder;

			if (value > finder->value)
				finder = finder->right;
			else
				finder = finder->left;
		}
	}

	TreeNode* Erase(int value) {
		TreeNode *eraser = Find(value);
		
		if (eraser == 0)
			return 0;
		
		TreeNode *parent = eraser->parent, **p = 0;
		if (eraser != root) {
			if (parent->right == eraser)
				p = &parent->right;
			else if (parent->left == eraser)
				p = &parent->left;
		}

		if (eraser->left == 0 && eraser->right == 0) {
			//자식이 하나도 없을 경우
			if (eraser == root)
				root = 0;
			else
				*p = 0;
		}
		else if (eraser->left != 0 && eraser->right == 0) {
			//자식이 왼쪽에만 있을 경우
			if (eraser == root) {
				root = eraser->left;
				eraser->left->parent = 0;
			}
			else {
				*p = eraser->left;
				eraser->left->parent = parent;
			}
		}
		else if (eraser->left == 0 && eraser->right != 0) {
			//자식이 오른쪽에만 있을 경우
			if (eraser == root) {
				root = eraser->right;
				eraser->right->parent = 0;
			}
			else {
				*p = eraser->right;
				eraser->right->parent = parent;
			}
		}
		else if (eraser->left != 0 && eraser->right != 0) {
			//자식이 양쪽에 있을 경우
			TreeNode *finder = eraser->left;
			while (1) {
				if (finder->right == 0)
					break;
				finder = finder->right;
			}
		
			Erase(finder->value);

			if (eraser == root) {
				root = finder;
				finder->parent = 0;
			}
			else {
				*p = finder;
				finder->parent = parent;
			}

			finder->left = eraser->left;
			finder->right = eraser->right;

			if (eraser->left != 0)
				finder->left->parent = finder;
			
			if (eraser->right != 0)
				finder->right->parent = finder;
		}
	}
};

Tree tree;

void Init() {
	treeNodePoolIndex = 0;
	tree.Init();
}


int main(void) {
	Init();

	int N;
	cin >> N;
	int input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		tree.Insert(input);
	}

	for (int i = 0; i < N; i++) {
		cin >> input;
		tree.Erase(input);
	}

	return 0;
}

/*
7
100
150
50
175
125
25
75

100
150
50
175
125
25
75
*/
