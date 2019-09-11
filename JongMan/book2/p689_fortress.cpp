#include<iostream>

using namespace std;


class Node {
public:
	int x, y, r;
};

Node tmp[150];
void PartSort(Node *arr, int start, int end, int mid) {
	int i = start, j = mid + 1;
	int index = start;
	while (i <= mid && j <= end) {
		if (arr[i].r > arr[j].r) {
			tmp[index] = arr[i];
			i++;
		}
		else {
			tmp[index] = arr[j];
			j++;
		}
		index++;
	}

	while (i <= mid) {
		tmp[index] = arr[i];
		i++;
		index++;
	}

	while (j <= end) {
		tmp[index] = arr[j];
		j++;
		index++;
	}
}

void MergeSort(Node *arr, int start, int end) {
	if (start >= end)
		return;

	int mid = (end - start) / 2 + start;

	MergeSort(arr, start, mid);
	MergeSort(arr, mid + 1, end);

	PartSort(arr, start, end, mid);

	for (int i = start; i <= end; i++)
		arr[i] = tmp[i];

}

int N;
Node gates[150];

class TreeNode;

class VectorNode {
public:
	TreeNode *treeNode;
};


int Max(int lhs, int rhs) {
	if (lhs < rhs)
		return rhs;
	else
		return lhs;
}

class Vector {
public:
	int cnt, reserved;
	VectorNode *nodes;


	void Resize() {
		reserved *= 2;
		VectorNode *tmp = new VectorNode[reserved];

		for (int i = 0; i < reserved / 2; i++)
			tmp[i] = nodes[i];

		delete nodes;
		nodes = tmp;
	}

	Vector() {
		cnt = 0;
		reserved = 4;
		nodes = new VectorNode[reserved];
	}

	~Vector() {
		delete nodes;
	}

	void PushBack(TreeNode *newNode) {
		if (cnt >= reserved)
			Resize();

		nodes[cnt].treeNode = newNode;
		cnt++;
	}

	void Clear() {
		delete nodes;
		cnt = 0;
		reserved = 4;
		nodes = new VectorNode[reserved];
	}
};



int tmpArr[150];
void PartSort(int *arr, int start, int end, int mid) {
	int i = start, j = mid + 1;
	int index = start;
	while (i <= mid && j <= end) {
		if (arr[i] > arr[j]) {
			tmpArr[index] = arr[i];
			i++;
		}
		else {
			tmpArr[index] = arr[j];
			j++;
		}
		index++;
	}

	while (i <= mid) {
		tmpArr[index] = arr[i];
		i++;
		index++;
	}

	while (j <= end) {
		tmpArr[index] = arr[j];
		j++;
		index++;
	}
}

void MergeSort(int *arr, int start, int end) {
	if (start >= end)
		return;

	int mid = (end - start) / 2 + start;

	MergeSort(arr, start, mid);
	MergeSort(arr, mid + 1, end);

	PartSort(arr, start, end, mid);

	for (int i = start; i <= end; i++)
		arr[i] = tmpArr[i];
}

int longest;
class TreeNode {
public:
	float x, y, r;
	Vector vector;

	void Init() {
		vector.Clear();
	}

	bool CanContain(TreeNode &other) {
		int lhs = (r - other.r) * (r - other.r);
		int rhs = ((other.x - x)*(other.x - x)) + ((other.y - y)*(other.y - y));

		if (lhs > rhs)
			return true;
		else
			return false;
	}


	void Insert(TreeNode *newNode) {
		//list에 있는 성 외곽 중에서 매개변수를 포함 가능한곳으로 이동한다.
		//그런 성이 list에 없으면 새로 만들어서 list에 포함시킨다.
		int i = 0;
		for (; i < vector.cnt; i++) {
			/*
			if (CanContain(*vector.nodes[i].treeNode))
				break;
			*/
			if (vector.nodes[i].treeNode->CanContain(*newNode))
				break;
		}

		if (i != vector.cnt)
			vector.nodes[i].treeNode->Insert(newNode);
		else
			vector.PushBack(newNode);
	}

	void Travel() {
		cout << x << " " << y << " " << r << endl;

		for (int i = 0; i < vector.cnt; i++)
			vector.nodes[i].treeNode->Travel();
	}


	int GetLength() {
		int ret = 0, tmp;

		if (vector.cnt == 0)
			return 1;

		int arr[100];
		for (int i = 0; i < vector.cnt; i++) {
			tmp = vector.nodes[i].treeNode->GetLength();
			ret = Max(tmp, ret);
			arr[i] = tmp;
		}

		MergeSort(arr, 0, vector.cnt - 1);

		if (vector.cnt >= 2) {
			int value = arr[0] + arr[1];
			longest = Max(value, longest);
		}

		return ret + 1;
	}


};

TreeNode treeNodePool[1000];
int treeNodeIndex = 0;

void InitTreeNodePool() {
	treeNodeIndex = 0;
}



TreeNode* NewTreeNode() {
	int tmp = treeNodeIndex;
	treeNodeIndex++;
	treeNodePool[tmp].x = 0;
	treeNodePool[tmp].y = 0;
	treeNodePool[tmp].r = 0;
	treeNodePool[tmp].Init();
	return &treeNodePool[tmp];
}


class Tree {
public:
	TreeNode *root;

	void Insert(int x, int y, int r) {
		TreeNode *newNode = NewTreeNode();
		newNode->x = x;
		newNode->y = y;
		newNode->r = r;

		root->Insert(newNode);
	}

	void Travel() {
		root->Travel();
	}

	int GetLength() {
		int value = root->GetLength() - 1;
		return value;
	}	
};


int main(void) {
	int T;
	cin >> T;
	int x, y, r;
	for (int testCase = 0; testCase < T; testCase++) {
		longest = 0;
		InitTreeNodePool();
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> x >> y >> r;
			gates[i].x = x;
			gates[i].y = y;
			gates[i].r = r;
		}

		MergeSort(gates, 0, N - 1);


		Tree tree;
		tree.root = NewTreeNode();
		tree.root->x = gates[0].x;
		tree.root->y = gates[0].y;
		tree.root->r = gates[0].r;

		for (int i = 1; i < N; i++) {
			tree.Insert(gates[i].x, gates[i].y, gates[i].r);
		}
		
		/*
		cout << "\n\n";
		tree.Travel();
		*/

		int value = tree.GetLength();
		int maxValue = Max(value, longest);
		cout << maxValue << endl;
	}


	return 0;
}
