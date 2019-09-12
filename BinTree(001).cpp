#include<iostream>

using namespace std;

class Tree {
public:
	class Node {
	public:
		int key, value;
		Node *parent, *left, *right;
	};

	Node nodePool[10000];
	int nodeIndex = 0;

	Node* NewNode() {
		int tmp = nodeIndex;
		nodeIndex++;
		nodePool[tmp].key = 0;
		nodePool[tmp].value = 0;
		nodePool[tmp].parent = 0;
		nodePool[tmp].left = 0;
		nodePool[tmp].right = 0;

		return &nodePool[tmp];
	}

	int cnt;
	Node *root;



	void Init() {
		nodeIndex = 0;
		cnt = 0;
		root = 0;
	}

	void Insert(int key, int value) {
		Node *p = root, **pp;
		if (p == 0) {
			Node *newNode = NewNode();
			root = newNode;
			newNode->key = key;
			newNode->value = value;
			return;
		}

		while (1) {
			if (p->key < key) {
				//오른쪽으로
				if (p->right == 0) {
					pp = &(p->right);
					break;
				}
				p = p->right;
			}
			else {
				//왼쪽으로
				if (p->left == 0) {
					pp = &(p->left);
					break;
				}
				p = p->left;
			}	
		}

		Node *newNode = NewNode();
		*pp = newNode;
		newNode->parent = p;
		newNode->key = key;
		newNode->value = value;
	}


	Node* Find(int key) {
		Node *p = root;

		while (1) {
			if (p == 0)
				return 0;

			if (p->key == key)
				return p;

			if (p->key < key)
				p = p->right;
			else
				p = p->left;
		}
	}


	int GetValue(int key) {
		Node *p = Find(key);
		if (p != 0)
			return p->value;
		else
			return 0;
	}
	

	/*
	나중에 마저 만들기
	void Erase(int key) {
		Node *p = Find(key);
		if (p == 0)
			return;
		Node *parent = p->parent;	
		
		if (p->right == 0 && p->left == 0) {
			//자식이 없을경우
			if (parent == root)
				root = 0;
			else {
				if (parent->left == p)
					parent->left = 0;
				else
					parent->right = 0;
			}
		}
		else if((p->right == 0 && p->left != 0)||(p->right != 0 && p->left == 0)){
			//자식이 하나일 경우
			Node **pp;
			if (parent->right == p)
				pp = &parent->right;
			else
				pp = &parent->left;
			
			if (p->right != 0)
				*pp = p->right;
			else
				*pp = p->left;
		}
		else {
			//자식이 둘다 있을 경우
			//한칸 왼쪽밑으로 내려가고 오른쪽 끝으로 이동한다
			Node **pp;
			if (parent->right == p)
				pp = &parent->right;
			else
				pp = &parent->left;
			
			Node *it = p->left;
			while (1) {
				if (it->right == 0)
					break;

				it = it->right;
			}
		}		
	}
	*/
};


int main(void) {
	Tree tree;
	int input;
	for (int i = 0; i < 8; i++) {
		cin >> input;
		tree.Insert(input, input);
	}


	cout << endl;
	return 0;
}
