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

int genresCnt[10000] = { 0, };
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


class HashListNode {
public:
	int value;
	char name[25];
	HashListNode *prev, *next;
};

HashListNode hashListNodePool[1000000];
int hashListNodePoolIndex;

int genreNum;

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
	HashListNode *front, *back;

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
Node nodes[10000];
int indexes[10000];
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
		
		if (nodes[indexes[i]] < nodes[indexes[j]]) {
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

	for (int i = 0; i < 100; i++)
		genresIndex[i] = i;
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
	}

	MergeSort(0, genres.size() - 1);
	//같은 장르는 최대 2번까지 나오도록 해야한다.
	//nodes[indexes[i]] : i번째로 앞에 있는 수
	int prevGenres = -1;
	int sameCnt = 0;
	for (int i = 0; i < genres.size(); i++) {
		if (prevGenres == nodes[indexes[i]].genre) {
			if (sameCnt > 0) {
				continue;
			}
			else {
				answer.push_back(nodes[indexes[i]].num);
				sameCnt++;
			}
		}
		else {
			prevGenres = nodes[indexes[i]].genre;
			sameCnt = 0;
			answer.push_back(nodes[indexes[i]].num);
		}
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
