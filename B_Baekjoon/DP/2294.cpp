#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
int N, K;
int coins[105];
int cache[10005];
int DFS(int arrSize, int score)
{
	if (score == K)
		return arrSize;
	if (score > K)
		return 2000000000;
	if (cache[score] != -1)
		return cache[score] + arrSize;
	int tmp, ret;
	ret = 2000000000;
	for (int i = 0; i < N; i++)
	{		
		tmp = DFS(arrSize + 1, score + coins[i]);
		ret = min(ret, tmp);
	}
	cache[score] = ret - arrSize;
	return ret;
}
int main(void)
{
	memset(cache, -1, sizeof(cache));
	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> coins[i];
	int value = DFS(0, 0);
	if (value < 10006)
		cout << value << endl;
	else
		cout << -1 << endl;
	return 0;
}

/*
이 방법의 문제는 순서를 신경 안쓰는 경우도 연산한다는점이다.
1 1 1 2
1 1 2 1
1 2 1 1
2 1 1 1
*/

