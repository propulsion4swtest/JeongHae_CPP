#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int Triangle[110][110];
int Cache[110][110];
int N;

/*
5
6
1 2
3 7 4
9 4 1 7
2 7 5 9 4
*/


int Solve(int x, int y, int score)
{
	if(y == N - 1)
	{
		Cache[y][x] = score;
		return score;
	}

	if(Cache[y][x] >= 0)
		return score + Cache[y][x];

	int ret = -1;
	int tmp1, tmp2;

	tmp1 = Solve(x, y + 1, Triangle[y + 1][x] + score);
	tmp2 = Solve(x + 1, y + 1, Triangle[y + 1][x + 1] + score);

	ret = max(tmp1, tmp2);

	Cache[y][x] = ret - score;

	return ret;
}





int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> N;
		memset(Cache, -1, sizeof(Cache));
		int input;
		for (int row = 0; row < N; row++)
		{
			for (int cul = 0; cul < row + 1; cul++)
			{
				cin >> input;
				Triangle[row][cul] = input;
			}
		}

		int value = Solve(0, 0, Triangle[0][0]);
		cout << value << endl;
	}

	return 0;
}
