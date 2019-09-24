#include<iostream>
#include <string>
#include <vector>

using namespace std;

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

void StrCpy(char *lhs, char *rhs) {
	int index = 0;
	while (1) {
		if (rhs[index] == '\0')
			break;
		lhs[index] = rhs[index];
		index++;
	}
	lhs[index] = '\0';
}

void String2Char(char *lhs, string &rhs) {
	int len = rhs.size();
	int i = 0;
	for (i = 0; i < len; i++)
		lhs[i] = rhs[i];
	lhs[i] = '\0';
}

//genresCnt를 기준으로 indexes에 내림차순으로 간접정렬 되어야 한다.
int genresCnt[10000] = { 0, };
int indexes[10000];

int genresIndex[100] = { 0, };


class Node {
public:
	int genre, cnt, num;

	bool operator<(const Node &rhs) {
		if (genre != rhs.genre)
			return genresCnt[genre] < genresCnt[rhs.genre];
		else if (cnt != rhs.cnt)
			return cnt < rhs.cnt;
		else
			return num > rhs.num;
	}
};

Node nodes[10000];

class Vector {
public:
	int size, reserved;
	int *arr;

	Vector() {
		size = 0;
		reserved = 0;
		arr = 0;
	}

	void Init() {
		if (arr != 0)
			delete[] arr;

		size = 0;
		reserved = 8;
		arr = new int[reserved];
	}

	void Resize() {
		reserved *= 2;
		int *tmp = new int[reserved];
		for (int i = 0; i < size; i++)
			tmp[i] = arr[i];
		delete[] arr;
		arr = tmp;
	}

	void PushBack(int value) {
		if (size == reserved) {
			Resize();
		}

		arr[size] = value;
		size++;
	}

	void GetValue(int &arg1, int &arg2) {
		if (size == 1) {
			arg1 = arr[0];
			arg2 = -1;
		}
		else {
			int maxIndex = arr[0];
			int index_ = 0;
			for (int i = 1; i < size; i++) {
				if (nodes[maxIndex] < nodes[arr[i]]) {
					maxIndex = arr[i];
					index_ = i;
				}
			}

			arg1 = maxIndex;

			int tmp = arr[index_];
			arr[index_] = arr[0];
			arr[0] = tmp;

			maxIndex = arr[1];
			index_;
			for (int i = 2; i < size; i++) {
				if (nodes[maxIndex] < nodes[arr[i]]) {
					maxIndex = arr[i];
					index_ = i;
				}
			}
			arg2 = maxIndex;

			tmp = arr[index_];
			arr[index_] = arr[1];
			arr[1] = tmp;
		}
	}
};


class HashListNode {
public:
	int value;
	char name[25];
	HashListNode *prev, *next;
};

HashListNode hashListNodePool[1000000];
int hashListNodePoolIndex;

int genreNum;
Vector songs[100];

void InitHashListNodePool() {
	hashListNodePoolIndex = 0;
}

HashListNode* NewHashListNode() {
	int tmp = hashListNodePoolIndex;
	hashListNodePoolIndex++;

	hashListNodePool[tmp].value = -1;
	hashListNodePool[tmp].prev = 0;
	hashListNodePool[tmp].next = 0;
	return &hashListNodePool[tmp];
}

class HashList {
public:
	HashListNode * front, *back;

	void Init() {
		front = NewHashListNode();
		back = NewHashListNode();
		front->next = back;
		back->prev = front;
	}

	int GetValue(char *name) {
		//이미 name이 존재하면 value를 반환한다.
		HashListNode *it;
		for (it = front->next; it != back; it = it->next) {
			if (StrCmp(it->name, name))
				return it->value;
		}

		//없다면 새로 추가하고 그값을 반환한다.
		HashListNode *newNode = NewHashListNode();
		HashListNode *before = back->prev;

		before->next = newNode;
		back->prev = newNode;
		newNode->prev = before;
		newNode->next = back;

		StrCpy(newNode->name, name);
		newNode->value = genreNum;
		genreNum++;
		return newNode->value;
	}
};

class Hash {
public:
	HashList table[10000];

	void Init() {
		for (int i = 0; i < 10000; i++)
			table[i].Init();
	}

	int GetValue(char *name) {
		int address = Hashing(name);
		int ret = table[address].GetValue(name);
		return ret;
	}

	int Hashing(char *name) {
		int index = 0, ret = 0;
		while (1) {
			if (name[index] == '\0')
				break;
			ret = ((ret * 26) + name[index] - 'a') % 10000;
			index++;
		}
		return ret;
	}

};

Hash db;
int tmpArr[10000];

//nodes를 간접정렬한다
void MergeSort(int start, int end) {
	if (start == end)
		return;

	int mid = (start + end) / 2;
	MergeSort(start, mid);
	MergeSort(mid + 1, end);

	int i = start, j = mid + 1, index = start;

	//start~mid , mid + 1 ~ end 까지 정렬한다.
	while (1) {
		if (i > mid || j > end)
			break;

		if (genresCnt[indexes[i]] < genresCnt[indexes[j]]) {
			tmpArr[index] = indexes[j];
			j++;
		}
		else {
			tmpArr[index] = indexes[i];
			i++;
		}
		index++;
	}

	while (i <= mid) {
		tmpArr[index] = indexes[i];
		i++;
		index++;
	}

	while (j <= end) {
		tmpArr[index] = indexes[j];
		j++;
		index++;
	}

	for (int k = start; k <= end; k++) {
		indexes[k] = tmpArr[k];
	}
}



void Init() {
	InitHashListNodePool();
	genreNum = 0;
	db.Init();
	for (int i = 0; i < 10000; i++) {
		genresCnt[i] = 0;
		indexes[i] = i;
	}

	for (int i = 0; i < 100; i++) {
		genresIndex[i] = i;
		songs[i].Init();
	}
}


vector<int> solution(vector<string> genres, vector<int> plays) {
	vector<int> answer;
	Init();
	//모든 genres를 hash에 등록한다.
	char name[25]; int value;
	for (int i = 0; i < genres.size(); i++) {
		String2Char(name, genres[i]);
		value = db.GetValue(name);
		genresCnt[value] += plays[i];
		nodes[i].genre = value;
		nodes[i].num = i;
		nodes[i].cnt = plays[i];
		songs[value].PushBack(i);
	}

	//MergeSort(0, genres.size() - 1);
	MergeSort(0, genreNum - 1);
	int a, b;
	for (int i = 0; i < genreNum; i++) {
		songs[indexes[i]].GetValue(a, b);
		answer.push_back(a);
		if (b != -1)
			answer.push_back(b);
	}


	return answer;
}


int main(void) {
	vector<string> genres;
	vector<int> plays;

	int N;
	cin >> N;
	string genre;
	int play;
	for (int i = 0; i < N; i++) {
		cin >> genre >> play;
		genres.push_back(genre);
		plays.push_back(play);
	}

	solution(genres, plays);

	return 0;
}
