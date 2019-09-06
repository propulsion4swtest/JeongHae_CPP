#include<iostream>

using namespace std;

bool StrCmp(char *lhs, char *rhs) {
	int i = 0;
	while (lhs[i] != '\0' && rhs[i] != '\0') {
		if (lhs[i] != rhs[i])
			return false;
		i++;
	}

	if (lhs[i] == '\0' && rhs[i] == '\0')
		return true;
	else
		return false;
}


void StrCpy(char *lhs, char *rhs) {
	int i = 0;
	while (rhs[i] != '\0') {
		lhs[i] = rhs[i];
		i++;
	}

	lhs[i] = '\0';
}


class HashListNode {
public:
	char key[20];
	int value;

	HashListNode *pPrev, *pNext;

	HashListNode() {
		pPrev = 0;
		pNext = 0;
	}
};

class HashList{
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

	void PushBack(char *key, int value) {
		HashListNode *newNode = new HashListNode;
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
		for (HashListNode *it = front->pNext; it != back; it = it->pNext) {
			if (StrCmp(it->key, key))
				return it;
		}
		return 0;
	}

	//지워진 노드 바로 다음을 반환한다
	HashListNode* Erase(HashListNode *erase) {
		HashListNode *before = erase->pPrev;
		HashListNode *after = erase->pNext;

		before->pNext = after;
		after->pPrev = before;

		cnt--;

		delete erase;
		return after;
	}

	void Clear() {
		if (cnt >= 1) {
			HashListNode *it = front->pNext->pNext;
			for (; it != back; it = it->pNext) {
				delete it->pPrev;
			}

			delete it->pPrev;
		}
		cnt = 0;
	}

	~HashList() {
		Clear();
		delete front;
		delete back;
	}
};


class Hash {
public:
	int cnt;
	HashList table[1000];

	Hash() {
		cnt = 0;
	}

	int HashFunc(char *key) {
		int ret = 0;
		for (int i = 0; key[i] != '\0'; i++) {
			ret = ((ret * 26) + key[i] - 'a') % 1000;
		}
		return ret;
	}

	void Insert(char *key, int value) {
		int address = HashFunc(key);
		table[address].PushBack(key, value);
		cnt++;
	}

	void Erase(char *key) {
		int address = HashFunc(key);
		HashListNode *erase = table[address].Find(key);
		if(erase != 0)
			table[address].Erase(erase);
		cnt--;
	}

	HashListNode* Find(char *key) {
		int address = HashFunc(key);
		HashListNode *ret = table[address].Find(key);
		return ret;
	}


	void Clear() {
		for (int i = 0; i < 1000; i++)
			table[i].Clear();
	}
};


int main(void) {
	Hash hash;
	
	
	char str0[20] = "hello";
	hash.Insert(str0, 120);

	char str1[20] = "world";
	hash.Insert(str1, 200);

	char str2[20] = "nice";
	hash.Insert(str2, 250);

	char str3[20] = "zzz";
	hash.Insert(str3, 400);

	HashListNode *ret;
	
	ret = hash.Find(str0);
	if (ret != 0)
		cout << ret->value << endl;
	else
		cout << "cant find" << endl;

	ret = hash.Find(str1);
	if (ret != 0)
		cout << ret->value << endl;
	else
		cout << "cant find" << endl;

	ret = hash.Find(str2);
	if (ret != 0)
		cout << ret->value << endl;
	else
		cout << "cant find" << endl;

	ret = hash.Find(str3);
	if (ret != 0)
		cout << ret->value << endl;
	else
		cout << "cant find" << endl;

	char dummy1[20] = "fail";
	ret = hash.Find(dummy1);
	if (ret != 0)
		cout << ret->value << endl;
	else
		cout << "cant find" << endl;

	char dummy2[20] = "unknown";
	ret = hash.Find(dummy2);
	if (ret != 0)
		cout << ret->value << endl;
	else
		cout << "cant find" << endl;

	hash.Erase(str0);
	hash.Erase(str1);

	ret = hash.Find(str0);
	if (ret != 0)
		cout << ret->value << endl;
	else
		cout << "cant find" << endl;

	ret = hash.Find(str1);
	if (ret != 0)
		cout << ret->value << endl;
	else
		cout << "cant find" << endl;

	ret = hash.Find(str2);
	if (ret != 0)
		cout << ret->value << endl;
	else
		cout << "cant find" << endl;

	ret = hash.Find(str3);
	if (ret != 0)
		cout << ret->value << endl;
	else
		cout << "cant find" << endl;

	hash.Clear();
	
	return 0;
}
