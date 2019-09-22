#include<iostream>

using namespace std;

class HeapNode {
public:
	int value;
	int key1, key2, key3;

	bool operator < (const HeapNode &rhs) {
		if (key1 != rhs.key1)
			return key1 < rhs.key1;
		else if (key2 != rhs.key2)
			return key2 < rhs.key2;
		else
			return key3 < rhs.key3;
	}

	bool operator > (const HeapNode &rhs) {
		if (key1 != rhs.key1)
			return key1 > rhs.key1;
		else if (key2 != rhs.key2)
			return key2 > rhs.key2;
		else
			return key3 > rhs.key3;
	}

};

class Heap {
public:
	int cnt;
	HeapNode nodes[10000];

	void Init() {
		cnt = 0;
	}

	Heap() {
		Init();
	}

	void Insert(HeapNode *newNode) {
		cnt++;
		int index = cnt;
		while (index != 1) {
			if (*newNode > nodes[index / 2])
				break;

			nodes[index] = nodes[index / 2];
			index /= 2;
		}
		nodes[index] = *newNode;
	}

	void Erase() {
		HeapNode tmpNode = nodes[cnt];
		cnt--;

		int parent = 1;
		int child = 2;
		while (child <= cnt) {
			//nodes[child]와 nodes[child + 1] 중 더 위로 올라갈 쪽을 선택해야한다.
			if (child + 1 <= cnt && (nodes[child] > nodes[child + 1]))
				child++;

			if (tmpNode < nodes[child])
				break;

			nodes[parent] = nodes[child];
			parent = child;
			child *= 2;
		}
		nodes[parent] = tmpNode;
	}

};

int main(void) {
	Heap heap;

	HeapNode node;
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> node.value >> node.key1 >> node.key2 >> node.key3;
		heap.Insert(&node);
	}

	for (int i = 0; i < N; i++) {
		cout << i << "\n";
		cout << "value : " << heap.nodes[1].value << "\n";
		cout << "key1 : " << heap.nodes[1].key1 << "\n";
		cout << "key2 : " << heap.nodes[1].key2 << "\n";
		cout << "key3 : " << heap.nodes[1].key3 << "\n\n";
		heap.Erase();
	}


	return 0;
}

/*

15
7 5 1 6
8 4 6 8
1 2 3 4
5 9 8 1
2 4 8 5
1 5 8 4
6 5 8 2
2 6  8 9
1 2 4 8
5 4 8 2
1 2 6 8
5 7 8 2
5 9 8 5
2 4 5 2
8 5 6 2

*/
