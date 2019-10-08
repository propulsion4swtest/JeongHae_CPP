#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int N;
int score[15];
vector<int> arr[15];
vector<int> leftTeam, rightTeam;

//team 벡터에 num 노드가 포함 되어 있는가?
bool IsContain(vector<int> &team, int num) {
	for (int i = 0; i < team.size(); i++)
		if (team[i] == num)
			return true;

	return false;
}

int BFS(vector<int> &team) {
	queue<int> qu;
	int flag[15] = { false, };
	int cnt = 1;
	qu.push(team[0]);
	flag[team[0]] = true;
	while (!qu.empty()) {
		int cIndex = qu.front(), nIndex;
		qu.pop();
		for (int i = 0; i < arr[cIndex].size(); i++) {
			nIndex = arr[cIndex][i];
			if (flag[nIndex] == true)
				continue;

			if (IsContain(team, nIndex) == false)
				continue;

			flag[nIndex] = true;
			cnt++;
			qu.push(nIndex);
		}
	}
	return cnt;	
}

int Sum(vector<int> &team) {
	int value = 0;
	for (int i = 0; i < team.size(); i++)
		value += score[team[i]];
	return value;
}

int Diff(int a, int b) {
	int ret = a - b;
	if (ret < 0)
		ret = -ret;
	return ret;
}

int RPerm(int arrSize) {
	if (arrSize == N) {
		int value = 2000000000;

		int cnt, value1, value2;
		if (leftTeam.size() != 0 && rightTeam.size() != 0) {
			//leftTeam[0]과 rightTeam[0]에 대해  bfs를 실시한다.
			cnt = BFS(leftTeam);
			if (cnt != leftTeam.size())
				return 2000000000;

			cnt = BFS(rightTeam);
			if (cnt != rightTeam.size())
				return 2000000000;

			value1 = Sum(leftTeam);
			value2 = Sum(rightTeam);
			value = Diff(value1, value2);
		}

		return value;
	}

	int tmp, ret = 2000000000;

	leftTeam.push_back(arrSize);
	tmp = RPerm(arrSize + 1);
	ret = min(ret, tmp);
	leftTeam.pop_back();

	rightTeam.push_back(arrSize);
	tmp = RPerm(arrSize + 1);
	ret = min(ret, tmp);
	rightTeam.pop_back();	

	return ret;
}





int main(void) {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> score[i];

	int n, input;
	for (int i = 0; i < N; i++) {
		cin >> n;
		for (int j = 0; j < n; j++) {
			cin >> input;
			input--;
			arr[i].push_back(input);
		}
	}
	int ret = RPerm(0);

	if (ret < 1000000000)
		cout << ret << endl;
	else
		cout << -1 << endl;

	/*
	leftTeam.push_back(0);
	leftTeam.push_back(2);
	leftTeam.push_back(3);
	leftTeam.push_back(1);

	rightTeam.push_back(4);
	rightTeam.push_back(5);

	int cnt = BFS(leftTeam);
	cnt = BFS(rightTeam);
	*/


	return 0;
}
