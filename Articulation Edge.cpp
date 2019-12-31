//https://jason9319.tistory.com/119

#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

class Edge {
public:
	int from, to;
	Edge(int from_, int to_) : from(from_), to(to_) {}
	Edge() : Edge(-1, -1) {}

	bool operator <(const Edge& rhs) const {
		if (from != rhs.from)
			return from < rhs.from;
		else
			return to < rhs.to;
	}
};

vector<vector<int>> edges;	//edges[i] : i번 노드에서 이동가능한 노드들의 목록
vector<int> disc;
vector<bool> node_flag;	//node_flag[i] : i번 노드는 단절점이다
vector<Edge> articulation_edge;
int cDisc;
int DFS(int here, int par) {
	disc[here] = cDisc;
	int ret = disc[here];
	cDisc++;
	for (int i = 0; i < edges[here].size(); i++) {
		int there = edges[here][i];
		if (par == there)
			continue;		
		if (disc[there] == -1) {
			int tmp = DFS(there, here);
			if (disc[here] < tmp) {
				//here -> there는 단절선이 된다.
				articulation_edge.push_back(Edge(min(here, there), max(here, there)));
			}
			ret = min(ret, tmp);
		}
		else {
			ret = min(ret, disc[there]);
		}
	}
	return ret;
}

int main(void) {
	int N, K;
	scanf("%d %d", &N, &K);
	edges.assign(N, vector<int>());
	disc.assign(N, -1);
	node_flag.assign(N, false);
	cDisc = 0;
	int from, to;
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &from, &to);
		from--, to--;
		edges[from].push_back(to);
		edges[to].push_back(from);
	}

	for (int i = 0; i < N; i++) {
		if (disc[i] == -1)
			DFS(i, -1);
	}

	sort(articulation_edge.begin(), articulation_edge.end());
	printf("%d\n", articulation_edge.size());
	for (int i = 0; i < articulation_edge.size(); i++) 
		printf("%d %d\n", articulation_edge[i].from + 1, articulation_edge[i].to + 1);

	return 0;
}
