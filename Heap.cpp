#include<iostream>

using namespace std;

class Node {
public:
	int key, value;
};


class Heap {
public:
	int cnt;
	Node nodes[100000];

	void Init() {
		cnt = 0;
	}

	void Insert(Node *arg) {
		cnt++;
		int i = cnt;

		while (i != 1 && (arg->key > nodes[i / 2].key))
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
			if (child + 1 <= cnt && (nodes[child].key < nodes[child + 1].key))
				child++;

			if (tmpNode.key > nodes[child].key)
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
		nodes[i].key = i;
		nodes[i].value = i;
	}

	Heap heap;
	heap.Init();

	for (int i = 0; i < 6; i++) {
		heap.Insert(&nodes[i]);
	}


	cout << heap.nodes[1].value << " ";
	heap.Erase();
	
	cout << heap.nodes[1].value << " ";
	heap.Erase();

	cout << heap.nodes[1].value << " ";
	heap.Erase();

	Node tmpNode;
	
	tmpNode.key = 0;
	tmpNode.value = 999;

	heap.Insert(&tmpNode);

	tmpNode.key = 7;
	tmpNode.value = 7;

	heap.Insert(&tmpNode);


	tmpNode.key = -1;
	tmpNode.value = -1;

	heap.Insert(&tmpNode);

	int n = heap.cnt;
	for (int i = 0; i < n; i++)
	{
		cout << heap.nodes[1].value << " ";
		heap.Erase();
	}


	cout << endl;

	cout << endl;
	return 0;
}
