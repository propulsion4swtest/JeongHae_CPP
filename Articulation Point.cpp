#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> edges; //edges[i] : i번 노드와 연결된 노드들의 번호 목록
vector<int> disc;
vector<bool> articulation_flag;
vector<int> articulation_points;
int cDisc;
int cnt = 0;

int DFS(int here, bool isStart) {
	int child = 0;
	disc[here] = cDisc;
	cDisc++;
	int ret = disc[here];
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i];
		if (disc[there] == -1) {
			child++;
			int tmp = DFS(there, false);
			if (!isStart && (disc[here] <= tmp)) {
				if (articulation_flag[here] == false) {
					articulation_flag[here] = true;
					articulation_points.push_back(here);
				}			
			}
			ret = min(ret, tmp);
		}
		else {
			ret = min(ret, disc[there]);
		}

	}

	if (isStart && child >= 2) {
		if (articulation_flag[here] == false) {
			articulation_flag[here] = true;
			articulation_points.push_back(here);
		}
	}
	return ret;
}


int main(void) {
	int N, K;
	scanf("%d %d", &N, &K);
	edges.assign(N, vector<int>());
	disc.assign(N, -1);
	articulation_flag.assign(N, false);
	int from, to;
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &from, &to);
		from--; to--;
		edges[from].push_back(to);
		edges[to].push_back(from);
	}

	cDisc = 0;

	for (int i = 0; i < N; i++) {
		if (disc[i] == -1)
			DFS(i, true);
	}
	
	sort(articulation_points.begin(), articulation_points.end());

	printf("%d\n", articulation_points.size());
	for (int i = 0; i < articulation_points.size(); i++)
		printf("%d ", articulation_points[i] + 1);
	printf("\n");

	return 0;
}
