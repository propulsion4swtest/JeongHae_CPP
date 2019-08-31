#include<iostream>
#include<string.h>

#define MOD 1000000007

using namespace std;

int N;

int cache[101];

int DFS(int arrSize, int cnt)
{
	if (arrSize == 0)
		return 1;
		
	if (cache[arrSize] != -1)
		return cache[arrSize];
	

	int ret = 0;

	//세로로 놓을 경우
	if (arrSize - 1 >= 0)
	{
		ret += DFS(arrSize - 1, cnt + 1);
		ret %= MOD;
	}

	//가로로 놓을 경우
	if (arrSize - 2 >= 0)
	{
		ret += DFS(arrSize - 2, cnt + 1);
		ret %= MOD;
	}

	cache[arrSize] = ret;

	return ret;
}


int Solve()
{
	int orgN = N;

	if (N % 2 == 1)
	{
		return (DFS(N, 0) - DFS(N / 2, 0) + MOD) % MOD;
	}
	else
	{
		int ret = DFS(N, 0);
		ret = (ret - DFS(N / 2, 0) + MOD) % MOD;
		ret = (ret - DFS(N / 2 - 1, 0) + MOD) % MOD;
		return ret;
	}
}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		memset(cache, -1, sizeof(cache));

		cin >> N;
		int value = Solve();
		cout << value << endl;

	}


	return 0;
}
