#include<iostream>

using namespace std;

bool StrCmp(char *lhs, char *rhs) {
	int i = 0;
	for (; lhs[i] != '\0' && rhs[i] != '\0'; i++)
	{
		if (lhs[i] != rhs[i])
			return false;
	}

	if (lhs[i] == '\0' && rhs[i] == '\0')
		return true;
	else
		return false;
}

void StrCpy(char *lhs, char *rhs) {
	int i = 0;
	for (; rhs[i] != '\0'; i++)
		lhs[i] = rhs[i];
	lhs[i] = '\0';
}


class HashListNode {
public:
	char key[20];
	int value;

	HashListNode *pNext;
	HashListNode *pPrev;

	HashListNode() {
		value = -1;
		pNext = 0;
		pPrev = 0;
	}

};

HashListNode hashListNodePool[10000];
int hashListNodePoolIndex;

void HashListNodePoolInit() {
	hashListNodePoolIndex = 0;

	for (int i = 0; i < 10000; i++) {
		hashListNodePool[i].pNext = 0;
		hashListNodePool[i].pPrev = 0;
	}
}

HashListNode* NewHashListNode() {
	HashListNode* newNode;
	newNode = &hashListNodePool[hashListNodePoolIndex];
	hashListNodePoolIndex++;

	newNode->value = -1;
	newNode->pNext = 0;
	newNode->pPrev = 0;
	return newNode;
}

class HashList {
public:
	int cnt;
	HashListNode *front;
	HashListNode *back;

	HashList() {
		cnt = 0;
		front = NewHashListNode();
		back = NewHashListNode();
		front->pNext = back;
		back->pPrev = front;
	}

	void PushBack(char *key, int value) {
		HashListNode *newNode = NewHashListNode();
		newNode->value = value;
		StrCpy(newNode->key, key);
		
		HashListNode *before = back->pPrev;
		before->pNext = newNode;
		back->pPrev = newNode;

		newNode->pPrev = before;
		newNode->pNext = back;

		cnt++;
	}

	HashListNode* Find(char *key) {
		HashListNode *it = front->pNext;
		for (; it != back; it = it->pNext) {
			if (StrCmp(it->key, key))
				return it;
		}
		return 0;
	}

	HashListNode* Erase(HashListNode *erase) {
		HashListNode *before = erase->pPrev;
		HashListNode *after = erase->pNext;

		before->pNext = after;
		after->pPrev = before;

		return after;
	}

	HashListNode* Erase(char *key) {
		HashListNode *erase = Find(key);

		if (erase != 0)
			return Erase(erase);
		else
			return 0;
	}

	void Clear() {
		front->pNext = back;
		back->pPrev = front;
	}

};


class Hash {
public:
	HashList table[1000];

	int HashFunc(char *key) {
		int ret = 0;
		for (int i = 0; key[i] != '\0'; i++)
			ret = ((ret * 26) + key[i] - 'a') % 1000;
		return ret;
	}

	HashListNode* Find(char* key) {
		int address = HashFunc(key);

		HashListNode *ret = table[address].Find(key);
		return ret;
	}

	//이미 저장된 key가 중복 저장 안되도록 주의할것
	void Insert(char *key, int value) {
		int address = HashFunc(key);
		table[address].PushBack(key, value);
	}

	void Erase(char *key) {
		int address = HashFunc(key);
		table[address].Erase(key);
	}

	void Clear() {
		for (int i = 0; i < 1000; i++)
			table[i].Clear();
	}

};


int main(void) {
	HashListNodePoolInit();

	Hash hash;

	char key0[20] = "hello";
	hash.Insert(key0, 100);

	char key1[20] = "world";
	hash.Insert(key1, 200);

	char key2[20] = "nice";
	hash.Insert(key2, 300);

	char key3[20] = "zzzzz";
	hash.Insert(key3, 400);

	HashListNode *node;
	node = hash.Find(key0);
	if (node != 0)
		cout << node->value << endl;

	node = hash.Find(key1);
	if (node != 0)
		cout << node->value << endl;

	node = hash.Find(key2);
	if (node != 0)
		cout << node->value << endl;

	node = hash.Find(key3);
	if (node != 0)
		cout << node->value << endl;

	hash.Erase(key0);
	hash.Erase(key1);

	node = hash.Find(key0);
	if (node != 0)
		cout << node->value << endl;

	node = hash.Find(key1);
	if (node != 0)
		cout << node->value << endl;

	hash.Insert(key0, 100);
	hash.Insert(key1, 200);

	node = hash.Find(key0);
	if (node != 0)
		cout << node->value << endl;

	node = hash.Find(key1);
	if (node != 0)
		cout << node->value << endl;

	node = hash.Find(key2);
	if (node != 0)
		cout << node->value << endl;

	node = hash.Find(key3);
	if (node != 0)
		cout << node->value << endl;


	/*
	HashList list;
	
	char key0[20] = "hello";
	list.PushBack(key0, 5);

	char key1[20] = "world";
	list.PushBack(key1, 6);

	char key2[20] = "nice";
	list.PushBack(key2, 7);

	char key3[20] = "zzzzz";
	list.PushBack(key3, 8);

	for (HashListNode *it = list.front->pNext; it != list.back; it = it->pNext)
		cout << it->value << " ";
	cout << endl;

	list.Erase(key1);
	list.Erase(key2);

	for (HashListNode *it = list.front->pNext; it != list.back; it = it->pNext)
		cout << it->value << " ";
	cout << endl;

	char key4[20] = "abcd";
	list.PushBack(key4, 100);

	char key5[20] = "efgh";
	list.PushBack(key5, 200);

	for (HashListNode *it = list.front->pNext; it != list.back; it = it->pNext)
		cout << it->value << " ";
	cout << endl;
	*/
	return 0;
}
