#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Node {
public:
	int x, y, s;

	Node() : Node(-1,-1,-1)
	{	}

	Node(int x_, int y_, int s_) : x(x_), y(y_), s(s_)
	{	}
};

int N, M, K;
int orgBoard[55][55];
int board[55][55];
vector<Node> spells;

void PrintBoard(int arr[][55]) {
	cout << "\n\n";
	for (int row = 0; row < N; row++) {
		for (int cul = 0; cul < M; cul++) {
			cout << arr[row][cul] << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";
}

void Rotate(int x, int y, int s) {
	int cY = y - s, cX = x - s;
	int tmp = board[cY][cX];
	int prevNum = board[cY][cX];
	for (cX++; cX <= x + s; cX++) {
		tmp = board[cY][cX];
		board[cY][cX] = prevNum;
		prevNum = tmp;
	}

	cY = y - s, cX = x + s;
	for (cY++; cY <= y + s; cY++) {
		tmp = board[cY][cX];
		board[cY][cX] = prevNum;
		prevNum = tmp;
	}

	cY = y + s, cX = x + s;
	for (cX--; cX >= x - s; cX--) {
		tmp = board[cY][cX];
		board[cY][cX] = prevNum;
		prevNum = tmp;
	}

	cY = y + s, cX = x - s;
	for (cY--; cY >= y - s; cY--) {
		tmp = board[cY][cX];
		board[cY][cX] = prevNum;
		prevNum = tmp;
	}
}

void Spell(int x, int y, int s) {
	for (int r = 1; r <= s; r++)
		Rotate(x, y, r);
}

void SwapArr(int *arr, int a, int b) {
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int mask[10];	//사용할 마법의 목록과 순서가 저장된다.
void CopyBoard() {
	for (int row = 0; row < N; row++)
		for (int cul = 0; cul < M; cul++)
			board[row][cul] = orgBoard[row][cul];
}

//board의 각 행의 값을 점검, 최소값을 반환
int GetLine(int row) {
	int value = 0;
	for (int cul = 0; cul < M; cul++)
		value += board[row][cul];
	return value;
}

int GetMinLine() {
	int ret= 200000000, tmp;
	for (int row = 0; row < N; row++) {
		tmp = GetLine(row);
		ret = min(ret, tmp);
	}
	return ret;
}

int Perm(int arrSize, int n) {	
	if (arrSize == n) {
		/*
		for (int i = 0; i < n; i++)
			cout << mask[i] << " ";
		cout << endl;
		*/
		//mask[0 ~ n - 1]까지의 주문을 시전한다.
		CopyBoard();
		int x, y, s, index;
		for (int i = 0; i < n; i++) {
			index = mask[i];
			x = spells[index].x;
			y = spells[index].y;
			s = spells[index].s;

			Spell(x, y, s);
		}
		//PrintBoard(board);
		int value = GetMinLine();
		return value;
	}

	int tmp, ret = 200000000;
	for (int i = arrSize; i < K; i++) {
		SwapArr(mask, i, arrSize);
		tmp = Perm(arrSize + 1, n);
		ret = min(ret, tmp);
		SwapArr(mask, i, arrSize);
	}
	return ret;
}

int main(void) {
	cin >> N >> M >> K;
	for (int row = 0; row < N; row++) {
		for (int cul = 0; cul < M; cul++) {
			cin >> orgBoard[row][cul];
			board[row][cul] = orgBoard[row][cul];
		}
	}

	int x, y, s;
	for (int i = 0; i < K; i++) {
		cin >> y >> x >> s;
		y--, x--;
		spells.push_back(Node(x, y, s));
		mask[i] = i;
	}

	int ret = 200000000;	
	ret = Perm(0, K);	

	cout << ret << endl;
	/*
	Rotate(3, 2, 2);
	PrintBoard(board);
	Rotate(3, 2, 1);
	PrintBoard(board);
	Rotate(1, 3, 1);
	PrintBoard(board);
	*/

	/*
	Spell(3, 2, 2);
	PrintBoard(board);
	Spell(1, 3, 1);
	PrintBoard(board);
	*/

	return 0;
}
