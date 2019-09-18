#include<iostream>

using namespace std;

class VectorNode {
public:
	int value, key;
};


class Vector {
public:
	int cnt, reserved;
	VectorNode *nodes;


	void Resize() {
		reserved *= 2;
		VectorNode *tmp = new VectorNode[reserved];

		for (int i = 0; i < reserved / 2; i++)
			tmp[i] = nodes[i];

		delete[] nodes;
		nodes = tmp;
	}

	Vector() {
		cnt = 0;
		reserved = 4;
		nodes = new VectorNode[reserved];		
	}

	~Vector() {
		delete[] nodes;
	}

	void PushBack(int key, int value) {
		if (cnt >= reserved)
			Resize();

		nodes[cnt].key = key;
		nodes[cnt].value = value;
		cnt++;
	}

	void Clear() {
		delete[] nodes;
		cnt = 0;
		reserved = 4;
		nodes = new VectorNode[reserved];
	}
};

int main(void) {
	Vector vector;
	for (int i = 0; i < 20; i++) {
		vector.PushBack(i, i);
	}


	for (int i = 0; i < 20; i++) {
		cout << vector.nodes[i].value << " ";
	}

	return 0;
}
