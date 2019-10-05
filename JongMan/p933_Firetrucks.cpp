#include<iostream>
#include<queue>
#include<vector>

#define FIRE 1
#define CENTER 2
#define INF 2000000000

using namespace std;

class Node {
public:
	int node, weight;

	Node() : Node(-1, -1)
	{	}

	Node(int node_, int weight_) : node(node_), weight(weight_)
	{	}
};

class Cmp {
public:
	bool operator()(Node lhs, Node rhs) {
		return lhs.weight > rhs.weight;
	}
};

int V, E, N, M;
//노드수, 간선수, 화재장소 수, 소방서 수
vector<Node> nodes[1005];	//각 node와 연결된 간선의 정보

int nodeType[1005];
int flag[1005];
vector<int> fires;

int BFS() {
	priority_queue<Node, vector<Node>, Cmp> pq;
	int ret = 0;
	for (int i = 0; i <= V; i++)
		flag[i] = INF;
	flag[0] = 0;
	pq.push(Node(0, 0));
	int from, to, weight;
	while (!pq.empty()) {
		Node cNode = pq.top();
		pq.pop();
		from = cNode.node;		
		if (flag[from] < cNode.weight)
			continue;
		for (int i = 0; i < nodes[from].size(); i++) {
			to = nodes[from][i].node;
			weight = nodes[from][i].weight;
			weight += cNode.weight;			
			if (flag[to] > weight) {
				flag[to] = weight;
				pq.push(Node(to, weight));
			}
		}
	}
	int index;
	for (int i = 0; i < N; i++) {
		index = fires[i];
		ret += flag[index];
	}

	return ret;
}


int main(void) {
	int T;
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase++) {
		scanf("%d %d %d %d", &V, &E, &N, &M);
		int a, b, weight;
		
		for (int i = 0; i <= V; i++) {
			nodes[i].clear();
			nodeType[i] = 0;
		}
		fires.clear();

		for (int i = 0; i < E; i++) {
			scanf("%d %d %d", &a, &b, &weight);
			nodes[a].push_back(Node(b, weight));
			nodes[b].push_back(Node(a, weight));
		}

		int input;
		for (int i = 0; i < N; i++) {
			scanf("%d", &input);
			nodeType[input] = FIRE;
			fires.push_back(input);
		}

		for (int i = 0; i < M; i++) {
			scanf("%d", &input);
			nodeType[input] = CENTER;
			nodes[0].push_back(Node(input, 0));
		}

		int value = BFS();
		printf("%d\n", value);
	}

	return 0;
}
