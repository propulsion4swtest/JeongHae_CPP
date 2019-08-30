#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int N, M;

int cache[1005][1005];
int board[1005][1005];
int moveX[3] = { 1,1,0 };
int moveY[3] = { 0,1,1 };

int DFS(int x, int y, int score)
{
	if (x == M - 1 && y == N - 1)
		return score + board[y][x];

	if (cache[y][x] != -1)
		return cache[y][x] + score;

	int nX, nY;

	int tmp, ret = 0;

	for (int dir = 0; dir < 3; dir++)
	{
		nX = x + moveX[dir];
		nY = y + moveY[dir];

		if (nX < 0 || nX >= M || nY < 0 || nY >= N)
			continue;

		tmp = DFS(nX, nY, score + board[y][x]);
		ret = max(ret, tmp);
	}

	cache[y][x] = ret - score;

	return ret;
}


int main(void)
{
	memset(cache, -1, sizeof(cache));
	cin >> N >> M;
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < M; cul++)
		{
			cin >> board[row][cul];
		}
	}

	int value = DFS(0, 0, 0);
	cout << value << endl;

}
