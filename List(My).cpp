#include<iostream>

using namespace std;

class ListNode {
public:
	int value;
	ListNode *pPrev, *pNext;

	ListNode() {
		value = -1;
		pPrev = 0;
		pNext = 0;
	}
};

class List {
public:
	int cnt;
	ListNode *front, *back;

	List() {
		cnt = 0;
		front = new ListNode;
		back = new ListNode;

		front->pNext = back;
		back->pPrev = front;
	}

	void PushBack(int value) {
		ListNode *newNode = new ListNode;
		newNode->value = value;
	
		ListNode *lastNode = back->pPrev;
		lastNode->pNext = newNode;
		back->pPrev = newNode;

		newNode->pPrev = lastNode;
		newNode->pNext = back;
		cnt++;
	}

	void PushFront(int value) {
		ListNode *newNode = new ListNode;
		newNode->value = value;
	
		ListNode *firstNode = front->pNext;
		firstNode->pPrev = newNode;
		front->pNext = newNode;

		newNode->pPrev = front;
		newNode->pNext = firstNode;
		cnt++;
	}

	void Insert(ListNode *prevNode, int newValue) {
		ListNode *nextNode = prevNode->pNext;
		ListNode *newNode = new ListNode;

		prevNode->pNext = newNode;
		nextNode->pPrev = newNode;

		newNode->pPrev = prevNode;
		newNode->pNext = nextNode;

		cnt++;
	}

	ListNode* Erase(ListNode *deleteNode) {
		ListNode *prevNode = deleteNode->pPrev;
		ListNode *nextNode = deleteNode->pNext;

		prevNode->pNext = nextNode;
		nextNode->pPrev = prevNode;

		delete deleteNode;			
		cnt--;

		return nextNode;
	}
};

int main(void) {
	List list;
	for (int i = 0; i < 6; i++)
		list.PushBack(i);

	for (int i = 10; i < 16; i++)
		list.PushFront(i);

	for (ListNode *it = list.front->pNext; it != list.back; it = it->pNext)
		cout << it->value << " ";

	cout << endl;

	return 0;
}
