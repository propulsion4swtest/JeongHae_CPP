#include<iostream>

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

//true : rhs 가 더 크다, false : lhs가 더 크다.
bool StrCmp2(char *lhs, char *rhs) {
	int index = 0;
	while (1) {
		if (lhs[index] == '\0' || rhs[index] == '\0')
			break;
		
		if (lhs[index] < rhs[index])
			return true;
		else if(lhs[index] > rhs[index])
			return false;

		index++;
	}
	
	if (lhs[index] == '\0')
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

int StrLen(char *str) {
	int index = 0;
	while (1) {
		if (str[index] == '\0')
			break;
		index++;
	}
	return index;
}

class GoalNode {
public:
	char str[15];
};

class TrieNode {
public:
	TrieNode *nodes[26];
	int score;
	GoalNode *goal;
	bool isEnd;
};


TrieNode trieNodePool[1500000];
int trieNodePoolIndex;
GoalNode goalNodePool[100000];
int goalNodePoolIndex;


TrieNode* NewTrieNode() {
	int tmp = trieNodePoolIndex;
	trieNodePoolIndex++;
	trieNodePool[tmp].goal = 0;
	trieNodePool[tmp].isEnd = false;
	trieNodePool[tmp].score = 0;
	for (int i = 0; i < 26; i++) 
		trieNodePool[tmp].nodes[i] = 0;	
	return &trieNodePool[tmp];
}

GoalNode* NewGoalNode() {
	int tmp = goalNodePoolIndex;
	goalNodePoolIndex++;

	return &goalNodePool[tmp];
}


class Trie {
public:
	TrieNode *root[26];

	Trie() {
		Init();
	}

	void Init() {
		for (int i = 0; i < 26; i++)
			root[i] = 0;
	}

	//str문자열을 score번 호출하였다.
	/*
	void Insert(char str[15], int score) {
		int index = 0;
		TrieNode **cNode = &root[str[index] - 'A'];		
		index++;

		while (1) {
			if (*cNode == 0)
				*cNode = NewTrieNode();

			if (str[index] == '\0')
				break;

			//cNode->score[str[index] - 'A'] += score;
			cout << &((*cNode)->nodes[str[index] - 'A']) << "\n";
			cNode = &((*cNode)->nodes[str[index] - 'A']);
			cout << cNode << "\n";
			index++;
		}
		(*cNode)->isEnd = true;
	}
	*/

	void Insert(char str[15], int score) {
		int index = 0;
		TrieNode *cNode;

		if (root[str[index] - 'A'] == 0)
			root[str[index] - 'A'] = NewTrieNode();
		cNode = root[str[index] - 'A'];
		index++;
		GoalNode *newGoalNode = NewGoalNode();
		StrCpy(newGoalNode->str, str);
		while (1) {
			if (cNode->score < score || (cNode->score == score && StrCmp2(str, cNode->goal->str))) {
				cNode->score = score;
				cNode->goal = newGoalNode;
			}
			
			if (str[index] == '\0')
				break;

			if (cNode->nodes[str[index] - 'A'] == 0)
				cNode->nodes[str[index] - 'A'] = NewTrieNode();

			cNode = cNode->nodes[str[index] - 'A'];
			index++;
		}
		cNode->isEnd = true;
	}

	//사전에 등록안된 문자에 대해서도 처리 할 수 있어야 한다.
	int Find(char *str) {
		int len = StrLen(str);
		int index = 0;
		TrieNode *cNode;
		cNode = root[str[index] - 'A'];
		//if(StrCmp(cNode->goal->str, str))
		
		index++;

		while (1) {
			if (str[index] == '\0')
				break;

			if (cNode == 0)
				return len;

			if (StrCmp(cNode->goal->str, str)) {
				index++;
				break;
			}

			cNode = cNode->nodes[str[index] - 'A'];
			index++;
		}

		return index;
	}

};

Trie trie;


void Init() {
	trieNodePoolIndex = 0;
	goalNodePoolIndex = 0;
	trie.Init();
}


int main(void) {
	
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++) {
		Init();

		int N, M;	//N : 사전에 포함된 단어의 수, M : 입력할 단어의 수
		cin >> N >> M;
		char str[25];
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			cin >> str >> cnt;
			trie.Insert(str, cnt);
		}
		int ret = 0;
		for (int i = 0; i < M; i++) {
			cin >> str;
			ret += trie.Find(str);
			ret++;
		}
		ret--;
		cout << ret << "\n";
	}
	

	/*
	char str1[20] = "aaaaaaaa";
	char str2[20] = "aaaaaa";

	cout << StrCmp2(str1, str2) << "\n";
	*/
	return 0;
}
