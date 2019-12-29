#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> tree;	//tree[i] : i 번 노드가 가지는 자식들의 목록
vector<vector<int>> par;	//par[node][i] : node의 2^i번째 부모의 번호		par[node][i] = par[par[node][i - 1]][i - 1]
vector<int> depths;

void DFS(int node, int dep) {
	depths[node] = dep;
	int cDepth = 1;
	int tmp, i = 1;
	while (dep - cDepth >= 0) {
		tmp = par[node][i - 1];
		par[node][i] = par[tmp][i - 1];

		i++;
		cDepth *= 2;
	}

	for (int i = 0; i < tree[node].size(); i++) {
		DFS(tree[node][i], dep + 1);
	}
}


int LCA(int a, int b) {
	DFS(0, 0);

	//a와 b를 같은 위치로 만들어야 한다.

	int low, deep;
	if (depths[a] < depths[b]) {
		low = a;
		deep = b;
	}
	else {
		low = b;
		deep = a;
	}

	int diff = depths[deep] - depths[low];

	//deep의 위치를 low가 있는곳 까지 끌어올린다.
	int i = 0;
	while (1) {
		if (diff == 0)
			break;

		if ((diff & 1) != 0) {
			deep = par[deep][i];
		}

		diff = diff >> 1;
		i++;
	}


	//low와 deep 번 node의 최소 공통조상을 구한다.
	if (low == deep)
		return low;

	int index = 1;

	while (1) {
		if (par[low][0] == par[deep][0])
			return par[low][0];

		index = 1;

		while (1) {
			if (par[low][index] == par[deep][index]) {
				index--;
				break;
			}
			index++;
		}

		low = par[low][index];
		deep = par[deep][index];

	}

	return -1;
}

int main(void) {
	int N;
	cin >> N;

	tree.assign(N, vector<int>());
	par.assign(N, vector<int>(N, -1));
	depths.assign(N, -1);
	int input;

	for (int i = 1; i < N; i++) {
		cin >> input;
		//i의 직계 부모는 input 이다.
		par[i][0] = input;
		tree[input].push_back(i);
	}


	int ret = LCA(5, 10);
	ret = LCA(1, 13);
	ret = LCA(7, 10);
	ret = LCA(13, 6);
	ret = LCA(1, 1);
	ret - LCA(2, 27);

	return 0;
}


/*
19
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17

31
0 0
1 1 2 2
3 3 4 4 5 5 6 6
7 7 8 8 9 9 10 10 11 11 12 12 13 13 14 14
*/
