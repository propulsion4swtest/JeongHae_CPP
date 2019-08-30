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
		
	int tmp, ret;
	ret = 2000000000;
	for (int i = index; i < N; i++)
	{		
		tmp = DFS(arrSize + 1, score + coins[i], i);
		ret = min(ret, tmp);
	}
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
이 방법은 느리고, 메모리를 많이 차지하지만
1.1.1.2
1.1.2.1
1.2.1.1
2.1.1.1
이 4가지를

1.1.1.2

한가지로 줄여서 탐색한다는 점에 있다.
*/
