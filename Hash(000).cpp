#include<iostream>

#define TABLE_SIZE 5000

using namespace std;

void StrCpy(char *lhs, char *rhs) {
	int index = 0;
	while (1) {
		if (rhs[index] == '\0')
			break;
		lhs[index] = rhs[index];
		index++;
	}
}

bool StrCmp(char *lhs, char *rhs) {
	int index = 0;
	while (1) {
		if (lhs[index] == '\0' || rhs[index] == '\0')
			break;
		if (lhs[index] != rhs[index])
			return false;
		index++;
	}

	if (lhs[index] == '\0' && rhs[index] == '\0')
		return true;
	else
		return false;
}

class HashListNode {
public:
	int value;
	char name[25];
	HashListNode *prev, *next;
};


HashListNode hashListNodePool[100000];
int hashListNodePoolIndex = 0;

void InitHashListNodePool() {
	hashListNodePoolIndex = 0;
}

HashListNode *NewHashListNode() {
	int tmp = hashListNodePoolIndex;
	hashListNodePoolIndex++;
	hashListNodePool[tmp].value = -1;
	hashListNodePool[tmp].prev = 0;
	hashListNodePool[tmp].next = 0;
	return &hashListNodePool[tmp];
}



class HashList {
public:
	int cnt = 0;
	HashListNode *front, *back;

	void Init() {
		cnt = 0;
		front = NewHashListNode();
		back = NewHashListNode();
		front->next = back;
		back->prev = front;
	}

	void Insert(int value, char *name) {
		HashListNode *newNode = NewHashListNode();
		StrCpy(newNode->name, name);
		newNode->value = value;

		HashListNode *before = back->prev;
		before->next = newNode;
		back->prev = newNode;

		newNode->prev = before;
		newNode->next = back;
	}

	HashListNode* Find(char *name) {
		HashListNode *finder;
		for (finder = front->next; finder != back; finder = finder->next) {
			if (StrCmp(finder->name, name))
				return finder;
		}
		return 0;
	}

};


class Hash {
public:
	HashList table[TABLE_SIZE];
};

Hash db;

void Init() {
	InitHashListNodePool();
	for (int i = 0; i < TABLE_SIZE; i++) {
		db.table[i].Init();
	}

}


int main(void) {
	char str1[25] = "hello";
	char str2[25] = "world";
	char str3[25] = "zzzz";

	HashList hashList;
	hashList.Init();
	hashList.Insert(5, str1);
	hashList.Insert(10, str2);

	cout << hashList.Find(str1)->value << "\n";
	cout << hashList.Find(str2)->value << "\n";
	cout << hashList.Find(str3) << "\n";

	return 0;
}
