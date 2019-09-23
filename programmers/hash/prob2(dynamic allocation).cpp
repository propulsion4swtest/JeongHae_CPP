#include<iostream>
#include<vector>
#include<string>


using namespace std;


void String2Char(char *lhs, string &rhs) {
	int len = rhs.size();
	int index = 0;
	for (index = 0; index < len; index++)
		lhs[index] = rhs[index];
	lhs[index] = '\0';
}


class TrieNode {
public:
	TrieNode *nodes[10];
	bool isEnd;

	TrieNode() {
		for (int i = 0; i < 10; i++)
			nodes[i] = 0;
		isEnd = false;
	}
	

	~TrieNode() {
		for (int i = 0; i < 10; i++) {
			if (nodes[i] != 0)
				delete nodes[i];
		}
	}
};


class Trie {
public:
	TrieNode * root;

	void Init() {
		root = new TrieNode();
	}

	~Trie() {
		Clear();
	}

	void Clear() {
		//root = NewTrieNode();
		//후위 순회를 하면서 모든 메모리를 해제시킨다.
		if(root != 0)
			delete root;
		root = 0;
	}


	bool Insert(char str[25]) {
		int index = 0;

		TrieNode *finder = root;
		while (1) {
			if (finder->nodes[str[index] - '0'] == 0)
				finder->nodes[str[index] - '0'] = new TrieNode();

			finder = finder->nodes[str[index] - '0'];
			index++;

			if (finder->isEnd == true)
				return false;

			if (str[index] == '\0')
				break;
		}

		for (int i = 0; i < 10; i++) {
			if (finder->nodes[i] != 0)
				return false;
		}

		if (finder->isEnd == true)
			return false;

		finder->isEnd = true;
		return true;
	}
};

Trie trie;


bool solution(vector<string> phone_book) {
	bool answer = true;
	trie.Init();
	int N = phone_book.size();
	char str[25];
	for (int i = 0; i < N; i++) {
		String2Char(str, phone_book[i]);
		answer = trie.Insert(str);
		if (answer == false)
			break;
	}
	cout << answer << "\n";
	trie.Clear();
	return answer;
}

int main(void) {
	int N;
	cin >> N;
	string str;
	vector<string> strings;
	for (int i = 0; i < N; i++) {
		cin >> str;
		strings.push_back(str);
	}

	solution(strings);

	return 0;
}
