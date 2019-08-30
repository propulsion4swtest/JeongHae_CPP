#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int triangle[510][510];

int N;

int cache[510][510];
int DFS(int x, int y, int score)
{
	if (y == N)
		return score;

	if (cache[y][x] != -1)
		return score + cache[y][x];

	int ret = 0;
	int tmp;
	//아래로 이동
	tmp = DFS(x, y + 1, score + triangle[y][x]);
	ret = max(ret, tmp);

	//오른쪽으로 이동
	tmp = DFS(x + 1, y + 1, score + triangle[y][x]);
	ret = max(ret, tmp);

	cache[y][x] = ret - score;

	return ret;
}

int main(void)
{
	memset(cache, -1, sizeof(cache));

	cin >> N;

	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul <= row; cul++)
		{
			cin >> triangle[row][cul];
		}
	}

	int value = DFS(0, 0, 0);
	cout << value << endl;

	return 0;
}
