#include<iostream>

using namespace std;


void StrCpy(char *lhs, char *rhs) {
	int i = 0;
	for (; rhs[i] != '\0'; i++)
		lhs[i] = rhs[i];
	lhs[i] = '\0';
}


bool StrCmp(char *lhs, char *rhs) {
	int i = 0;
	
	for (; (lhs[i] != '\0' && rhs[i] != '\0'); i++) {
		if (lhs[i] != rhs[i])
			return false;
	}

	if (lhs[i] == rhs[i])
		return true;
	else
		return false;
}

class HashListNode {
public:
	int value;
	char key[20];
	HashListNode *pPrev, *pNext;

	HashListNode() {
		value = -1;
		pPrev = 0;
		pNext = 0;
	}
};

class HashList {
public:
	int cnt;
	HashListNode *front, *back;

	HashList() {
		cnt = 0;
		front = new HashListNode;
		back = new HashListNode;

		front->pNext = back;
		back->pPrev = front;
	}



	void PushBack(int value, char* key) {
		HashListNode *newNode = new HashListNode;
		newNode->value = value;
		StrCpy(newNode->key, key);
	
		HashListNode *lastNode = back->pPrev;
		lastNode->pNext = newNode;
		back->pPrev = newNode;

		newNode->pPrev = lastNode;
		newNode->pNext = back;
		cnt++;
	}


	bool Insert(int newValue, char* newKey) {
		//중복 여부 조사
		for (HashListNode *it = front->pNext; it != back; it = it->pNext) {
			if (StrCmp(it->key, newKey) == false)
				return false;
		}

		PushBack(newValue, newKey);

		return true;
	}


	HashListNode* Erase(HashListNode *deleteNode) {
		HashListNode *prevNode = deleteNode->pPrev;
		HashListNode *nextNode = deleteNode->pNext;

		prevNode->pNext = nextNode;
		nextNode->pPrev = prevNode;

		delete deleteNode;			
		cnt--;

		return nextNode;
	}

	int Find(char* key) {
		HashListNode *it = front->pNext;

		for (it = front->pNext; it != back; it = it->pNext) {
			if (StrCmp(it->key, key) == true)
				break;
		}

		if (it != back)
			return it->value;
		else
			return -1;
	}
};


class Hash {
public:
	int cnt;
	HashList hashTable[1000];

	Hash() {
		cnt = 0;
	}

	int HashFunction(char *key) {

		char c;
		int ret = 0;
		for (int i = 0; key[i] != '\0'; i++) {
			c = key[i];
			ret = ((ret * 31) + c - 'a') % 1000;
		}
		return ret;
	}


	int Find(char *key) {
		int address = HashFunction(key);

		int ret = hashTable[address].Find(key);

		return ret;
	}

	bool Insert(char *key, int value) {
		//이미있는지 점검과 삽입을 동시에 한다
		//삽입 도중에 이미 있음이 발견되면 바로 false 반환

		int address = HashFunction(key);

		bool ret = hashTable[address].Insert(value, key);
		return ret;
	}

};

int main(void) {

	/*
	char lhs[20] = "zzzzzaaa";
	char rhs[20] = "zzzzz";

	cout << StrCmp(lhs, rhs) << endl;
	*/

	/*
	char lhs[20];
	char rhs[20] = "abcdefgh";

	StrCpy(lhs, rhs);
	cout << lhs << endl;
	*/

	Hash hash;
	char key[20] = "hello";
	int value = 100;
	hash.Insert(key, value);

	int ret = hash.Find(key);

	return 0;
}
