#include<iostream>

using namespace std;

class Vector {
public:
	int cnt;
	int arr[30];

	Vector() {
		Init();
	}

	void Init() {
		cnt = 0;
	}

	void PushBack(int value) {
		arr[cnt] = value;
		cnt++;
	}

	void Reverse() {
		int tmp[30];
		for (int i = 0; i < cnt; i++) 
			tmp[cnt - 1 - i] = arr[i];

		for (int i = 0; i < cnt; i++)
			arr[i] = tmp[i];
	}
};

int N;
bool flag[26];
char words[1050][30];
bool graph[30][30];
bool isNode[26];
bool cycleFlag[26];

int Min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
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

void GetEdge() {
	int a, b;
	for (int i = 0; i < N - 1; i++) {
		//i와 i+1번째 단어에서
		int len = Min(StrLen(words[i]), StrLen(words[i + 1]));

		for (int j = 0; j < len; j++) {
			if (words[i][j] != words[i + 1][j]) {
				//words[i][j] -> words[i + 1][j]
				a = words[i][j] - 'a';
				b = words[i + 1][j] - 'a';
				graph[a][b] = true;
				isNode[a] = true;
				isNode[b] = true;
				break;
			}
		}
	}
}

Vector orgPath;
Vector path;
Vector answer;
bool isCycle;

void DFS(int value) {
	if (isCycle == true)
		return; 
	if (cycleFlag[value] == true) {
		isCycle = true;
		return;
	}
	if (flag[value] == true)
		return;
	

	flag[value] = true;
	cycleFlag[value] = true;

	for (int i = 0; i < 26; i++) {
		if (graph[value][i] == true) {
			DFS(i);
			
		}
	}
	cycleFlag[value] = false;
	path.PushBack(value);
}


//위상정렬을 통해 그래프를 나열한다.
bool Solve() {
	for (int i = 0; i < 26; i++) {
		if (isNode[i] == true) {
			orgPath.PushBack(i);
			DFS(i);
			if (isCycle == true)
				return false;
		}
	}
	path.Reverse();

	int index = 0;
	for (int i = 0; i < 26; i++) {
		if (isNode[i] == false)
			answer.PushBack(i);
		else {
			answer.PushBack(path.arr[index]);
			index++;
		}
	}

	return true;
}


void Init() {
	for (int i = 0; i < 26; i++) {
		flag[i] = false;
		isNode[i] = false;
		cycleFlag[i] = false;
		for (int j = 0; j < 26; j++)
			graph[i][j] = false;
	}
	path.Init();
	orgPath.Init();
	answer.Init();
	isCycle = false;
}

int main(void) {
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++) {
		Init();

		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> words[i];

		GetEdge();
		bool ret = Solve();

		if (ret == true) {
			for (int i = 0; i < 26; i++) {
				cout << (char)(answer.arr[i] + 'a');
			}
			cout << endl;
		}
		else
			cout << "INVALID HYPOTHESIS" << endl;
	}


	return 0;
}
