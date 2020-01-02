//https://www.acmicpc.net/problem/1238

#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>

#define INF 2000000000

using namespace std;

class Node {
public:
	int index, time;
	Node(int index_, int time_) : index(index_), time(time_){}
	Node() : Node(-1, -1) {}

	bool operator <(const Node& rhs) const {
		return time > rhs.time;
	}
};

int N, M, X;
vector<vector<int>> edges; //edges[i] : i번 노드에서 이동가능한 노드들의 목록
vector<vector<int>> graph; //graph[a][b] : a에서 b로 이동하는 가중치
vector<int> dist;	//dist[i] :  다익스트라의 특정 시작점에서 다른점으로 이동하는 최소 비용

int Dijkstra(int start, int goal) {
	dist.assign(N, INF);
	dist[start] = 0;

	priority_queue<Node> pq;
	pq.push(Node(start, 0));
	int ret = INF;
	while (!pq.empty()) {
		Node cNode = pq.top();
		pq.pop();

		int here = cNode.index;

		if (cNode.index == goal) {
			ret = min(ret, cNode.time);
			continue;
		}

		if (cNode.time > dist[here])
			continue;

		int there, cWeight;
		for (int i = 0; i < edges[cNode.index].size(); i++) {
			there = edges[cNode.index][i];
			cWeight = cNode.time + graph[here][there];

			if (dist[there] <= cWeight)
				continue;

			dist[there] = cNode.time + graph[here][there];
			pq.push(Node(there, cWeight));
		}
	}

	return ret;
}

int main(void) {
	scanf("%d %d %d", &N, &M, &X);
	X--;
	edges.assign(N, vector<int>());
	graph.assign(N, vector<int>(N, -1));
	int from, to, weight;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &from, &to, &weight);
		from--, to--;
		edges[from].push_back(to);
		graph[from][to] = weight;
	}

	//Dijkstra(4);
	int ret = -1, tmp1,tmp2;
	for (int i = 0; i < N; i++) {
		tmp1 = Dijkstra(i, X);
		tmp2 = Dijkstra(X, i);
		ret = max(ret, tmp1 + tmp2);
	}

	printf("%d\n", ret);


	return 0;
}
