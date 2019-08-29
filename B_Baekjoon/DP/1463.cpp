#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int N;

int cache[1000005];
int DFS(int number, int cnt)
{
	if (number == 1)
		return cnt;

	if (cache[number] != -1)
		return cnt + cache[number];

	int tmp, ret = 2000000000;

	//3으로 만들기
	if (number % 3 == 0)
	{
		tmp = DFS(number / 3, cnt + 1);
		ret = min(ret, tmp);
	}

	if (number % 2 == 0)
	{
		tmp = DFS(number / 2, cnt + 1);
		ret = min(ret, tmp);
	}

	tmp = DFS(number - 1, cnt + 1);
	ret = min(ret, tmp);

	cache[number] = ret - cnt;

	return ret;
}

int main(void)
{
	cin >> N;
	memset(cache, -1, sizeof(cache));

	int value = DFS(N, 0);
	cout << value << endl;

	return 0;
}
