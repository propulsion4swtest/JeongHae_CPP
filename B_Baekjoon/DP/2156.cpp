#include<iostream>
#include<string.h>

#define MOD 10007

using namespace std;

int N;

int cache[10][1010];

int DFS(int arrSize, int prevNum)
{
	if (arrSize == N - 1)
		return 1;


	if (cache[prevNum][arrSize] != -1)
		return cache[prevNum][arrSize];

	int tmp = 0;

	for (int i = prevNum; i <= 9; i++)
	{
		tmp += DFS(arrSize + 1, i);
		tmp %= MOD;
	}

	cache[prevNum][arrSize] = tmp;

	return tmp;
}


int main(void)
{
	memset(cache, -1, sizeof(cache));
	cin >> N;
	int value = 0;

	for (int i = 0; i <= 9; i++)
	{
		value += DFS(0, i);
		value %= MOD;
	}
	cout << value << endl;

	return 0;
}
