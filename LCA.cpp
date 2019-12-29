#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> tree;	//0이 무조건 root이다.
							//tree[i] : i번 노드가 가지는 자식노드의 수

vector<vector<int>> par;		//par[node][i] : node의 2^i 번째 조상, par[node][i] = par[par[node][i-1]][i-1]
vector<int> depths;	//depth[i] : i번 노드가 가지는 깊이.

void DFS(int node, int dep) {
	depths[node] = dep;
	
	int cDepth = 1;	//dep - cDep 가 새로 설정하는 노드의 깊이가 되며 이는 0이상 이어야 한다.
	int tmp, i = 1, cNode = node;
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

//a와 b번 노드의 최소 공통 조상을 구한다.
int LCA(int a, int b) {
	DFS(0, 0);

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
	
	//deep 번호의 index번째 조상의 번호를 구한다.
	int val = 0;
	while (1) {
		if ((diff & 1) != 0) {
			deep = par[deep][val];			
		}

		diff = diff >> 1;
		if (diff == 0)
			break;

		val++;
	}

	if (deep == low)
		return deep;

	//이제 깊이가 같아진 low와 deep의 공통조상을 구하면 된다.
	//par[node][i]로 접근결과 값이 제일 다른 경우 중에 node 중에 i가 제일 높은쪽으로 이동해 나간다
	//직계부모가 같다면 그 노드가 LCA이다.
	int index = 1;
	while (1) {
		if (par[deep][0] == par[low][0])
			return par[deep][0];
		index = 1;
		while (1) {
			if (par[deep][index] == par[low][index]) {
				index--;
				break;
			}
			index++;			
		}

		deep = par[deep][index];
		low = par[low][index];
	}

	return -1;
}

int main(void) {
	int N, L;
	cin >> N;
	tree.assign(N, vector<int>());
	par.assign(N, vector<int>(N, -1));
	depths.assign(N, 0);
	for (int i = 1; i < N; i++) {
		//i번 노드의 직계 조상은 L이 된다.
		cin >> L;
		tree[L].push_back(i);
		par[i][0] = L;
	}

	LCA(7, 13);
	
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
