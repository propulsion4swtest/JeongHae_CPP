#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int N;
int paths[20][20];
int start;
int cache[1 << 16][16];
int cnt = 0;
int DFS(int arrSize, int bitMask, int cPosition, int score)
{
	if (start == cPosition && arrSize == N)
		return score;
		
	if (cache[bitMask][cPosition] != -1)	
		return score + cache[bitMask][cPosition];
	
	
	int tmpMask = bitMask | (1 << cPosition);
	bool canPath = false;
	int pathMask;
	int tmp, ret = 2000000000;
	for (int nPosition = 0; nPosition < N; nPosition++)
	{
		pathMask = tmpMask & (1 << nPosition);
		if (pathMask == 0)
			canPath = true;	//이동 해본적 없는곳
		else
			canPath = false;//이미 이동 해본곳

		if (paths[cPosition][nPosition] > 0)
			if ((canPath == true) || (start == nPosition && arrSize + 1 == N))
			{
				tmp = DFS(arrSize + 1, tmpMask, nPosition, score + paths[cPosition][nPosition]);
				ret = min(ret, tmp);
			}
	}

	cache[bitMask][cPosition] = ret - score;

	//bitMask = bitMask ^ (1 << cPosition);
	return ret;
}


int main(void)
{
	memset(cache, -1, sizeof(cache));

	cin >> N;
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			cin >> paths[row][cul];	
		}
	}

	/*
	int tmp, value = 2000000000;
	for (int i = 0; i < N; i++)
	{
		start = i;
		tmp = DFS(0, 0, i, 0);
		value = min(tmp, value);
	}
	*/

	start = 0;
	int value = DFS(0, 0, 0, 0);

	cout << value << endl;

	return 0;
}
