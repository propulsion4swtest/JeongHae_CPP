#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int arr[11];
int players[11][11];	//players[a][b] : a번 플레이어가 b필드에서 뛸때의 점수
int cache[1 << 11][11];

void SwapArr(int *arr, int a, int b)
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}


int Perm(int arrSize, int score, int bitMask)
{
	if (arrSize == 11)
		return score;
	
	if (cache[bitMask][arrSize] != -1)
		return cache[bitMask][arrSize] + score;

	int tmp, ret = 0;
	int cPlayer;
	int value;
	for (int i = arrSize; i < 11; i++)
	{
		SwapArr(arr, i, arrSize);
		cPlayer = arr[arrSize];
		value = players[cPlayer][arrSize];
		if (value != 0)
		{
			tmp = Perm(arrSize + 1, score + value, bitMask | (1 << cPlayer));
			ret = max(ret, tmp);
		}

		SwapArr(arr, i, arrSize);
	}

	cache[bitMask][arrSize] = ret - score;

	return ret;
}



int main(void)
{
	for (int i = 0; i < 11; i++)
		arr[i] = i;

	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		memset(cache, -1, sizeof(cache));

		for (int row = 0; row < 11; row++)
		{
			for (int cul = 0; cul < 11; cul++)
			{
				cin >> players[row][cul];
			}
		}

		int value = Perm(0, 0, 0);
		cout << value << endl;
	}

	return 0;
}
