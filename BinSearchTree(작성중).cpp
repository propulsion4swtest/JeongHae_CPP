#include<iostream>

using namespace std;

class BinTreeNode {
public:
	int key, value;
	BinTreeNode *pLeft, *pRight;

	BinTreeNode() {
		key = -1;
		value = -1;
		pLeft = 0;
		pRight = 0;
	}

	BinTreeNode(BinTreeNode &newNode) : key(newNode.key), value(newNode.value) {
		pLeft = 0;
		pRight = 0;
	}
	
};

class BinTree {
public:
	BinTreeNode * root;
	//root Node는 시작과 동시에 수동으로 추가되어야 한다

	bool Insert(BinTreeNode *newNode) {
		BinTreeNode *parent = root;
		BinTreeNode *child = 0;

		while (parent != 0) {
			if (parent->key == newNode->key)
				return false;

			if (parent->key < newNode->key) {
				child = parent->pRight;
			}
			else if (parent->key > newNode->key) {
				child = parent->pLeft;
			}

			if (child == 0)
				break;

			parent = child;
		}

		child = new BinTreeNode(*newNode);

		//parent의 child위치에 새로운 노드를 추가한다
		if (parent->key < newNode->key) {
			parent->pRight = child;
		}
		else if (parent->key > newNode->key) {
			parent->pLeft = child;
		}
	}

	BinTreeNode* Find(BinTreeNode *arg, BinTreeNode *argParent) {		
		BinTreeNode *parent = 0;
		BinTreeNode *child = root;

		while (1) {
			if (child->key == arg->key)
			{
				argParent = parent;
				return child;
			}
			parent = child;

			if (parent->key < arg->key)
				child = parent->pRight;
			else if (parent->key > arg->key)
				child = parent->pLeft;

			if (child == 0)
				return 0;

		}
	}

	BinTreeNode* Find(BinTreeNode *arg) {
		BinTreeNode *ret;
		BinTreeNode *dummy = 0;
		ret = Find(arg, dummy);
		return ret;
	}

	/*
	void Erase(BinTreeNode *arg) {
		BinTreeNode *parent;
		BinTreeNode *delNode;

		delNode = Find(arg, parent);

		//삭제할 노드의 오른쪽이 비었을 경우(바로 부모와 삭제 노드의 왼쪽을 이어준다)
		if (delNode->pRight == 0)
		{
			if (root == delNode) {				
				if (parent->pRight == delNode)
					parent->pRight = delNode->pLeft;
				else if (parent->pLeft == delNode)
					parent->pLeft = delNode->pLeft;
			}
			else {
				if (parent->pRight == delNode)
					parent->pRight = delNode->pLeft;
				else if (parent->pLeft == delNode)
					parent->pLeft = delNode->pLeft;
			}
			delete delNode;
		}
		else {	//삭제할 노드의 양쪽이 다 뭔가로 있을경우
			//한칸 왼쪽으로 이동 후 제일 오른쪽에 있는 요소를 찾는다.
			if (delNode->pLeft == 0) {
				//왼쪽에 이을만한 요소가 없으므로 

			}

		}
	}
	*/
};



int main(void) {
	BinTree binTree;
	binTree.root = new BinTreeNode;
	binTree.root->key = 100;
	binTree.root->value = 100;

	BinTreeNode tmpNode;
	
	tmpNode.key = 50;
	tmpNode.value = 50;
	binTree.Insert(&tmpNode);

	tmpNode.key = 25;
	tmpNode.value = 25;
	binTree.Insert(&tmpNode);

	tmpNode.key = 10;
	tmpNode.value = 10;
	binTree.Insert(&tmpNode);

	tmpNode.key = 70;
	tmpNode.value = 70;
	binTree.Insert(&tmpNode);

	tmpNode.key = 100;
	tmpNode.value = 100;
	binTree.Insert(&tmpNode);

	tmpNode.key = 200;
	tmpNode.value = 200;
	binTree.Insert(&tmpNode);

	tmpNode.key = 250;
	tmpNode.value = 250;
	binTree.Insert(&tmpNode);


	BinTreeNode *ret;
	BinTreeNode *dummy;

	tmpNode.key = 25;
	tmpNode.value = 25;
	ret = binTree.Find(&tmpNode);
	if (ret != 0)
		cout << ret->value << " ";
	else
		cout << -1 << " ";

	tmpNode.key = 100;
	tmpNode.value = 100;
	ret = binTree.Find(&tmpNode);
	if (ret != 0)
		cout << ret->value << " ";
	else
		cout << -1 << " ";

	tmpNode.key = 125;
	tmpNode.value = 125;
	ret = binTree.Find(&tmpNode);
	if (ret != 0)
		cout << ret->value << " ";
	else
		cout << -1 << " ";


	tmpNode.key = 250;
	tmpNode.value = 250;
	ret = binTree.Find(&tmpNode);
	if (ret != 0)
		cout << ret->value << " ";
	else
		cout << -1 << " ";


	tmpNode.key = 25;
	tmpNode.key = 25;
	ret = binTree.Find(&tmpNode);
	if (ret != 0)
		cout << ret->value << " ";
	else
		cout << -1 << " ";

	tmpNode.key = 75;
	tmpNode.key = 75;
	ret = binTree.Find(&tmpNode);
	if (ret != 0)
		cout << ret->value << " ";
	else
		cout << -1 << " ";


	return 0;
}
