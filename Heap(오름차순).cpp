#include<iostream>

using namespace std;

class Node {
public:
	int key, value;
};

class Heap {
public:
	int cnt;
	Node nodes[1000];

	void Init() {
		cnt = 0;
	}

	//이미 정렬된 배열에 대해선 한번에 넣으면 시간이 크게 감소된다.
	void Init(Node *arr, int n) {
		cnt = n;
		for (int i = 1; i <= n; i++) {
			nodes[i] = arr[i - 1];
		}
	}

	void Insert(Node *arg) {
		cnt++;
		int i = cnt;

		while (i != 1 && (arg->key < nodes[i / 2].key))
		{
			nodes[i] = nodes[i / 2];
			i /= 2;
		}

		nodes[i] = *arg;
	}

	void Erase() {
		Node tmpNode = nodes[cnt];
		cnt--;
		int parent = 1;
		int child = 2;
		while (child <= cnt) {
			if (child + 1 <= cnt && (nodes[child].key > nodes[child + 1].key))
				child++;

			if (tmpNode.key < nodes[child].key)
				break;

			nodes[parent] = nodes[child];
			parent = child;
			child *= 2;
		}

		nodes[parent] = tmpNode;
	}
};



int main(void)
{
	Node nodes[6];
	for (int i = 0; i < 6; i++) {
		nodes[i].value = i;
		nodes[i].key = i;
	}

	
	Heap heap;
	heap.Init(nodes, 6);
	

	
	heap.Erase();
	cout << heap.nodes[1].value << " ";

	heap.Erase();
	cout << heap.nodes[1].value << " ";
	
	heap.Erase();
	cout << heap.nodes[1].value << " ";

	Node tmpNode;
	
	tmpNode.key = 0;
	tmpNode.value = 0;
	heap.Insert(&tmpNode);
	cout << heap.nodes[1].value << " ";

	
	tmpNode.key = 2;
	tmpNode.value = 2;
	heap.Insert(&tmpNode);
	cout << heap.nodes[1].value << " ";


	tmpNode.key = 1;
	tmpNode.value = 1;
	heap.Insert(&tmpNode);
	cout << heap.nodes[1].value << " ";


	tmpNode.key = 8;
	tmpNode.value = 8;
	heap.Insert(&tmpNode);
	cout << heap.nodes[1].value << " ";


	tmpNode.key = 9;
	tmpNode.value = 9;
	heap.Insert(&tmpNode);
	cout << heap.nodes[1].value << " ";

	int n = heap.cnt;
	for (int i = 0; i < n; i++)	{
		cout << heap.nodes[1].value << " ";
		heap.Erase();
	}

	return 0;

}
