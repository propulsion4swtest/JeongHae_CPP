#include<iostream>
#include<string.h>

using namespace std;

int N;

int cache[3][11];

int DFS(int arrSize)
{
	if (arrSize == N)
		return 1;

	int ret = 0;
	int tmp = 0;
	for (int i = 1; i <= 3; i++)
	{
		if (arrSize + i <= N)
		{
			if (cache[i - 1][arrSize] == -1)
			{
				tmp = DFS(arrSize + i);
				cache[i - 1][arrSize] = tmp;
			}
			else
				tmp = cache[i - 1][arrSize];

			ret += tmp;
		}
	}

	return ret;
}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		memset(cache, -1, sizeof(cache));

		cin >> N;

		int value = DFS(0);
		cout << value << endl;
	}
}
