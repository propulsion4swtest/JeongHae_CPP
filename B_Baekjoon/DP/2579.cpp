#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int cache[2][305];

int stairs[305];
int N;

int DFS(int arrSize, bool canOne, int score)
{
	if (arrSize == N - 1)
	{
		score += stairs[arrSize];
		return score;
	}

	if (cache[canOne][arrSize] != -1)
		return score + cache[canOne][arrSize];

	int tmp, ret = 0;

	//한칸 이동
	if (canOne == true && arrSize + 1 <= N - 1)
	{
		tmp = DFS(arrSize + 1, false, score + stairs[arrSize]);
		ret = max(ret, tmp);
	}

	//두칸 이동
	if (arrSize + 2 <= N - 1)
	{
		tmp = DFS(arrSize + 2, true, score + stairs[arrSize]);
		ret = max(ret, tmp);
	}

	cache[canOne][arrSize] = ret - score;

	return ret;
}


int main(void)
{
	memset(cache, -1, sizeof(cache));

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> stairs[i];
	}

	int value1 = DFS(0, true, 0);
	int value2 = DFS(1, true, 0);
	int value = max(value1, value2);
	cout << value << endl;

	return 0;
}
