#include<stdio.h>

using namespace std;

class Vector {
public:
	int cnt, reserved;
	int *arr;

	Vector() {
		cnt = 0;
		reserved = 8;
		arr = 0;
	}

	void Init() {
		cnt = 0;
		reserved = 8;
		arr = new int[reserved];
	}
	
	void PushBack(int i) {
		if (cnt == reserved) {
			reserved *= 2;
			int *newArr = new int[reserved];
			for (int i = 0; i < cnt; i++) {
				newArr[i] = arr[i];
			}

			delete[] arr;
			arr = newArr;
		}
		arr[cnt] = i;
		cnt++;
	}

	void Clear() {
		delete[] arr;
		Init();
	}

	~Vector() {
		if(arr != 0)
			delete[] arr;
	}

};

int N, Q;
Vector nodes[100100];
Vector str;
int depth[100100];
int newNode[100100];

int position[100100];	//position[index] = index번 사람의 str 내에서의 첫 위치;
int newIndex = 0;

int segmentTree[600400];	//구간내에서의 최소값을 저장한다.

int Min(int lhs, int rhs) {
	if (lhs < rhs)
		return lhs;
	else
		return rhs;
}

//0, str.cnt - 1, 1
int SegmentTreeInit(int from, int to, int index) {

	if (from >= to) {
		segmentTree[index] = str.arr[from];
		return str.arr[from];
	}

	int tmp1, tmp2;
	int mid = (from + to) / 2;

	tmp1 = SegmentTreeInit(from, mid, 2 * index);
	tmp2 = SegmentTreeInit(mid + 1, to, 2 * index + 1);

	int ret = Min(tmp1, tmp2);

	segmentTree[index] = ret;

	return ret;
}

//from, to : 찾고자 하는 구역
//from, to : 고정 , start, end : mid 값을 기준으로 반씩 나눈다, index : 접근 첨자
int GetValue(int from, int to, int start, int end, int index) {
	if (end < from || to < start)
		return 200000;

	if (from <= start && end <= to)
		return segmentTree[index];

	int mid = (start + end) / 2;
	int tmp1 = GetValue(from, to, start, mid, index * 2);
	int tmp2 = GetValue(from, to, mid + 1, end, index * 2 + 1);
	int ret = Min(tmp1, tmp2);
	return ret;
}


//0을 전달받고 시작한다
void Search(int index, int dep) {
	//printf("%d ", index);
	int tmp = newIndex;
	newIndex++;
	newNode[index] = tmp;
	position[index] = str.cnt;
	str.PushBack(tmp);
	depth[tmp] = dep;

	for (int i = 0; i < nodes[index].cnt; i++) {
		Search(nodes[index].arr[i], dep + 1);
		//printf("%d ", index);
		str.PushBack(tmp);
	}
}


int main(void) {
	str.Init();
	for (int i = 0; i < 100000; i++)
		nodes[i].Init();

	int T;
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase++) {
		scanf("%d %d", &N, &Q);
		newIndex = 0;
		for (int i = 0; i < N + 5; i++) {
			nodes[i].Clear();
		}
		str.Clear();

		int input;
		for (int i = 1; i < N; i++) {
			scanf("%d", &input);
			nodes[input].PushBack(i);
		}

		Search(0, 0);
		
		/*
		printf("\n\n");
		for (int i = 0; i < str.cnt; i++)
			printf("%d ", str.arr[i]);
		printf("end \n");
		*/
		
		SegmentTreeInit(0, str.cnt - 1, 1);

		int from, to;
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &from, &to);
			if (position[from] > position[to]) {
				int tmp = from;
				from = to;
				to = tmp;
			}
			
			int tmp = GetValue(position[from], position[to], 0, str.cnt - 1, 1);
			int ret = depth[newNode[from]] + depth[newNode[to]] - 2 * depth[tmp];
			printf("%d\n", ret);
		}		
	}


	return 0;
}
