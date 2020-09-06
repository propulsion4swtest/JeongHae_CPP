//https://www.acmicpc.net/problem/1197

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Edge {
public:
	int from, to, weight;

	Edge(int from_, int to_, int weight_) : from(from_), to(to_), weight(weight_) {}
	Edge() : Edge(-1, -1, -1) {}

	bool operator <(const Edge& rhs)const {
		return weight < rhs.weight;
	}

};

vector<Edge> edges;
vector<int> union_set;
vector<int> union_level;

int UnionFind(int index) {
	if (union_set[index] != -1)
		return union_set[index] = UnionFind(union_set[index]);
	else
		return index;
}

void UnionMerge(int a, int b) {
	a = UnionFind(a);
	b = UnionFind(b);

	if (a == b)
		return;

	//a의 레벨이 b보다 항상 낮아야한다.
	//a를 b에 포함시켜야 한다.

	if (union_level[a] > union_level[b])
		swap(a, b);

	union_set[a] = b;

	if (union_level[a] == union_level[b])
		union_level[b]++;
}

//edges의 정보를 순회하면서 최소 신장 트리를 구한다.
int MST() {
	sort(edges.begin(), edges.end());
	int ret = 0;
	for (int i = 0; i < edges.size(); i++) {
		//간선의 시작점과 끝점의 root가 같으면 사이클을 형성하는것이다.
		int a, b;
		a = UnionFind(edges[i].from);
		b = UnionFind(edges[i].to);

		if (a == b)
			continue;

		//i번 간선은 최소 신장 트리에 포함 될 수 있다.
		ret += edges[i].weight;

		//UnionMerge(a, edges[i].from);
		//UnionMerge(b, edges[i].to);
		UnionMerge(edges[i].from, edges[i].to);
	}

	return ret;
}


int main(void) {
	int V, E;
	scanf("%d %d", &V, &E);
	int from, to, weight;
	union_set.assign(V, -1);
	union_level.assign(V, 1);
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &from, &to, &weight);
		from--, to--;
		edges.push_back(Edge(from, to, weight));
	}
	
	int ret = MST();
	printf("%d\n", ret);

	return 0;
}
