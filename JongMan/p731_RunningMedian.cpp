#include<iostream>

#define FIRST 1983
#define MOD 20090711

using namespace std;

//오름차순
class MinHeap {
public:
	int arr[120000];
	int cnt;

	void Init() {
		cnt = 0;
	}

	void Insert(int arg) {
		cnt++;
		int index = cnt;
		while (index != 1 && arg < arr[index / 2]) {
			arr[index] = arr[index / 2];
			index /= 2;
		}
		arr[index] = arg;
	}

	void Erase() {
		int tmp = arr[cnt];
		cnt--;

		int parent = 1;
		int child = 2;

		while (child <= cnt) {
			if (child + 1 <= cnt && arr[child] > arr[child + 1])
				child++;

			if (tmp < arr[child])
				break;

			arr[parent] = arr[child];
			parent = child;
			child *= 2;
		}
		arr[parent] = tmp;
	}

};

//내림차순
class MaxHeap {
public:
	int arr[120000];
	int cnt;

	void Init() {
		cnt = 0;
	}

	void Insert(int arg) {
		cnt++;
		int index = cnt;
		while (index != 1 && arg > arr[index / 2]) {
			arr[index] = arr[index / 2];
			index /= 2;
		}
		arr[index] = arg;
	}

	void Erase() {
		int tmp = arr[cnt];
		cnt--;

		int parent = 1;
		int child = 2;

		while (child <= cnt) {
			if (child + 1 <= cnt && arr[child] < arr[child + 1])
				child++;

			if (tmp > arr[child])
				break;

			arr[parent] = arr[child];
			parent = child;
			child *= 2;
		}
		arr[parent] = tmp;
	}

};

int value = 1983;
int N;
int A, B;
int GetValue() {
	int tmp = value;
	value = (value * (long long)A + B) % MOD;
	return tmp;
}

MinHeap minHeap;
MaxHeap maxHeap;

int Solve() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		int newValue = GetValue();
		if (minHeap.cnt == maxHeap.cnt)
			maxHeap.Insert(newValue);
		else
			minHeap.Insert(newValue);

		if ((minHeap.cnt != 0 && maxHeap.cnt != 0) && (maxHeap.arr[1] > minHeap.arr[1])) {
			int a = maxHeap.arr[1], b = minHeap.arr[1];
			maxHeap.Erase(); minHeap.Erase();
			maxHeap.Insert(b);
			minHeap.Insert(a);
		}
		ret = (ret + maxHeap.arr[1]) % MOD;
	}

	return ret;
}

int main(void) {
	
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++) {
		cin >> N >> A >> B;
		minHeap.Init();
		maxHeap.Init();
		value = FIRST;
		int ret = Solve();
		cout << ret << "\n";
	}
	
	

	/*
	MinHeap minHeap;
	MaxHeap maxHeap;

	minHeap.Init();
	maxHeap.Init();
	for (int i = 10; i >= 0; i--) {
		minHeap.Insert(i);
		maxHeap.Insert(10 - i);
	}

	for (int i = 10; i >= 0; i--) {
		cout << minHeap.arr[1] << " ";
		minHeap.Erase();
	}
	cout << endl;

	for (int i = 10; i >= 0; i--) {
		cout << maxHeap.arr[1] << " ";
		maxHeap.Erase();
	}
	*/

	return 0;
}
