#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
int N, K;
int coins[105];
int cache[105][10005];
int DFS(int arrSize, int score, int index)
{
	if (score == K)
		return arrSize;
	if (score > K)
		return 2000000000;
	if (cache[index][score] != -1)
		return cache[index][score] + arrSize;
	if (index == N)
		return 2000000000;
	int tmp, ret;
	ret = 2000000000;
	tmp = DFS(arrSize + 1, score + coins[index], index);
	ret = min(ret, tmp);
	tmp = DFS(arrSize, score, index + 1);
	ret = min(ret, tmp);
	cache[index][score] = ret - arrSize;
	return ret;
}
int main(void)
{
	memset(cache, -1, sizeof(cache));
	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> coins[i];
	int value = DFS(0, 0, 0);
	if (value < 10006)
		cout << value << endl;
	else
		cout << -1 << endl;
	return 0;
}


/*
중복조합을 베이스로 하여
순서에 따른 중복 연산을 막는 연산이다
가령
1.1.1.2
1.1.2.1
1.2.1.1
2.1.1.1

4가지 케이스를 다 찾는 이전의 방식에 비해

1.1.1.2

딱 한번만 찾는다
*/
