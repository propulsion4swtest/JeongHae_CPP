#include<iostream>

using namespace std;

int paths[100100];

int Min(int lhs, int rhs) {
	if (lhs < rhs)
		return lhs;
	else
		return rhs;
}


int Max(int lhs, int rhs) {
	if (lhs < rhs)
		return rhs;
	else
		return lhs;
}


class SegmentTreeNode {
public:
	int minHeight, maxHeight;
	int from, to;
	SegmentTreeNode *left, *right;

	void GetValue(int start, int end, int &minValue, int &maxValue) {
		if (to < start || from > end) {
			minValue = 200000000;
			maxValue = -1;
			return;
		}

		if (start <= from && to <= end) {
			minValue = minHeight;
			maxValue = maxHeight;
			return;
		}

		int min1, max1;
		int min2, max2;
		left->GetValue(start, end, min1, max1);
		right->GetValue(start, end, min2, max2);
		minValue = Min(min1, min2);
		maxValue = Max(max1, max2);
	}
};

SegmentTreeNode segmentTreeNodePool[10000000];
int segmentTreeNodeIndex;

void InitSegMentTreeNodePool() {
	segmentTreeNodeIndex = 0;
}

SegmentTreeNode* NewSegmentTreeNode() {
	int tmp = segmentTreeNodeIndex;
	segmentTreeNodeIndex++;
	segmentTreeNodePool[tmp].minHeight = 2000000000;
	segmentTreeNodePool[tmp].maxHeight = -1;
	segmentTreeNodePool[tmp].from = -1;
	segmentTreeNodePool[tmp].to = -1;
	segmentTreeNodePool[tmp].left = 0;
	segmentTreeNodePool[tmp].right = 0;

	return &segmentTreeNodePool[tmp];
}

class SegmentTree {
public:
	SegmentTreeNode *root;

	//배열 정보를 바탕으로 세그먼트 트리를 초기화 한다.
	void Init(int from, int to) {
		root = Create(from, to);
	}

	SegmentTreeNode* Create(int from, int to) {
		SegmentTreeNode *ret = NewSegmentTreeNode();
		ret->from = from;
		ret->to = to;
		
		if (from == to) {
			ret->minHeight = paths[from];
			ret->maxHeight = paths[to];
			return ret;
		}
				
		if (from > to)
			return 0;
				
		int mid = (from + to) / 2;

		ret->left = Create(from, mid);
		ret->right = Create(mid + 1, to);

		int minHeight = Min(ret->left->minHeight, ret->right->minHeight);
		int maxHeight = Max(ret->left->maxHeight, ret->right->maxHeight);
		ret->minHeight = minHeight;
		ret->maxHeight = maxHeight;

		return ret;
	}

	int GetValue(int from, int to) {
		int minHeight, maxHeight;
		root->GetValue(from, to, minHeight, maxHeight);
		int diff = maxHeight - minHeight;
		return diff;
	}

};

SegmentTree tree;

int main(void) {
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++) {
		InitSegMentTreeNodePool();

		int N, Q;
		cin >> N >> Q;
		for (int i = 0; i < N; i++)
			cin >> paths[i];

		tree.Init(0, N - 1);

		int from, to;
		for (int i = 0; i < Q; i++) {
			cin >> from >> to;
			cout << tree.GetValue(from, to) << "\n";
		}
	}
}
