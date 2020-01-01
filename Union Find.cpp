#include<iostream>
#include<vector>

using namespace std;

vector<int> union_set;
vector<int> union_level;

int UnionFind(int index) {
	if (union_set[index] != -1) {
		union_set[index] = UnionFind(union_set[index]);
		return union_set[index];
	}
	else
		return index;
}

void UnionMerge(int a, int b) {
	a = UnionFind(a);
	b = UnionFind(b);

	if (a == b)
		return;

	//a가 b보다 무조건 낮아야 하며
	//a를 b에 무조건 합처야 한다.

	if (union_level[a] > union_level[b])
		swap(a, b);

	union_set[a] = b;

	if (union_level[a] == union_level[b])
		union_level[b]++;
}

int main(void) {
	int N, M;
	scanf("%d %d", &N, &M);
	union_set.assign(N + 1, -1);
	union_level.assign(N + 1, 1);

	int op, a, b;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &op, &a, &b);
		if (op == 0) {
			//a와 b 집합을 합친다.
			UnionMerge(a, b);
		}
		else if (op == 1) {
			//a와 b가 같은지 구한다.
			if (UnionFind(a) == UnionFind(b))
				printf("YES\n");
			else
				printf("NO\n");
		}
	}

	return 0;
}
