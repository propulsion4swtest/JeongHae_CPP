#include<iostream>
#include<queue>
#include<string.h>
#include<algorithm>

using namespace std;

class Node {
public:
	int x, y;
	Node(int x_, int y_) : x(x_), y(y_)
	{	}

	Node() : Node(-1,-1)
	{	}
};

int N;
int board[105][105];
bool water[105][105];
bool flag[105][105];
int minHeight, maxHeight;
int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };

void BFS(int x, int y) {
	queue<Node> qu;
	qu.push(Node(x, y));
	flag[y][x] = true;
	int nx, ny;
	while (!qu.empty()) {
		Node cNode = qu.front();
		qu.pop();
		for (int dir = 0; dir < 4; dir++) {
			nx = cNode.x + moveX[dir];
			ny = cNode.y + moveY[dir];

			if (nx < 0 || nx >= N || ny < 0 || ny >= N)
				continue;

			if (water[ny][nx] == true || flag[ny][nx] == true)
				continue;

			flag[ny][nx] = true;
			qu.push(Node(nx, ny));
		}
	}
}

//water와 board 정보를 바탕으로 땅의 갯수를 파악한다.
int GetLand() {
	int cnt = 0;
	memset(flag, false, sizeof(flag));
	for (int row = 0; row < N; row++) {
		for (int cul = 0; cul < N; cul++) {
			if (water[row][cul] == false && flag[row][cul] == false) {
				BFS(cul, row);
				cnt++;
			}
		}
	}
	return cnt;
}


void PrintBool(bool arr[][105]) {
	cout << "\n\n";
	for (int row = 0; row < N; row++) {
		for (int cul = 0; cul < N; cul++) {
			if (arr[row][cul] == 0)
				cout << " .";
			else
				cout << "■";
		}
		cout << "\n";
	}
	cout << "\n\n";
}


//rain 이하의 땅을 전부다 물로 뒤덮는다.
void Flood(int rain) {
	memset(water, false, sizeof(water));

	for (int row = 0; row < N; row++)
		for (int cul = 0; cul < N; cul++)
			if (board[row][cul] <= rain)
				water[row][cul] = true;
}


int Solve() {
	int cnt = -1, tmp;
	for (int rain = minHeight; rain <= maxHeight; rain++) {
		Flood(rain);
		//PrintBool(water);
		tmp = GetLand();
		//PrintBool(flag);
		cnt = max(cnt, tmp);
	}

	return cnt;
}


int main(void) {
	minHeight = 2000000000, maxHeight = -1;
	cin >> N;
	for (int row = 0; row < N; row++) 
		for (int cul = 0; cul < N; cul++) {
			cin >> board[row][cul];
			minHeight = min(minHeight, board[row][cul]);
			maxHeight = max(maxHeight, board[row][cul]);
		}

	minHeight--;
	maxHeight++;
	int ret = Solve();
	cout << ret << endl;
	/*
	Flood(4);
	PrintBool(water);
	
	BFS(0, 4);
	PrintBool(flag);
	*/


	return 0;
}
