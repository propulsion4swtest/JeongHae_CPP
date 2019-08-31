#include<iostream>
#include<string.h>

#define MOD 10000000

using namespace std;

long long N;

long long cache[105][105];

long long DFS(long long arrSize, long long prevSize)
{
	if (arrSize == N)
		return 1;

	if (cache[prevSize][arrSize] != -1)
		return cache[prevSize][arrSize];

	long long time;
	long long tmp, ret = 0;
	for (long long i = 1; arrSize + i <= N ; i++)
	{
		time = prevSize + i - 1;
		tmp = DFS(arrSize + i, i);
		tmp *= time;
		tmp %= MOD;
		ret += tmp;
		ret %= MOD;
	}
	cache[prevSize][arrSize] = ret;

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
		long long value = 0;
		for (int i = 1; i <= N; i++)
		{
			value += DFS(i, i);
			value %= MOD;
		}
		cout << value << endl;
	}

	return 0;
}
