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
		tmp = DFS(arrSize + 1, score + coins[i], index);
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
