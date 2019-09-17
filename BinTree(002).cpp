#include<iostream>

using namespace std;

class BinTreeNode {
public:
	int key, value;
	BinTreeNode *parent, *left, *right;

};

BinTreeNode binTreeNodePool[30000];
int binTreeNodeIndex;

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
	int cnt;
	BinTreeNode *root;

	void Init() {
		cnt = 0;
		root = 0;
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

	void Insert(int key, int value) {		
		BinTreeNode *parent = 0;
		BinTreeNode *child = root;
		BinTreeNode **p = 0;
		BinTreeNode *newNode = NewBinTreeNode();
		newNode->key = key;
		newNode->value = value;

		while (1) {
			if (child == 0) {
				//삽입할곳을 찾음
				if (child == root) {
					root = newNode;
				}
				else {
					*p = newNode;
					newNode->parent = parent;
				}
				return;
			}

			//중복된 key를 삽입 할 수 없다
			if (child->key == key)
				return;

			if (child->key < key) {
				parent = child;
				child = child->right;
				p = &parent->right;
			}
			else {
				parent = child;
				child = child->left;
				p = &parent->left;
			}			
		}
	}


	void Erase(int key) {
		BinTreeNode *parent = 0;
		BinTreeNode *eraser = Find(key);
		BinTreeNode **p = 0;

		if (eraser != root) {
			parent = eraser->parent;
			if (parent->left == eraser)
				p = &parent->left;
			else
				p = &parent->right;
		}

		if (eraser->left == 0 && eraser->right == 0) {
			//자식이 하나도 없는경우
			if (eraser == root)
				root = 0;
			else
				*p = 0;
		}
		else if (eraser->left == 0 && eraser->right != 0) {
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
		else if (eraser->left != 0 && eraser->right == 0) {
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
			//자식이 둘다 있을 경우
			//왼쪽 밑으로 한칸 이동후 오른쪽 밑으로 이동한다.
			//찾아낸 node를 지워진 위치에 대체시킨다.
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

			if(eraser->left != 0)
				newNode->left->parent = newNode;
			
			if(eraser->right != 0)
			newNode->right->parent = newNode;
		}
	}
};

void Init() {
	binTreeNodeIndex = 0;
}

int main(void) {
	Init();
	BinTree tree;
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

7

100
50
150
25
75
125
175

*/
