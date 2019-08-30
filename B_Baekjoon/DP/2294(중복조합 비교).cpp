#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int N, K;
int coins[105];
int cache[105][10005];

int cnt = 0;

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


int DFS2(int arrSize, int score, int index)
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
		
			tmp = DFS2(arrSize + 1, score + coins[i], i);
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
	cout << value << endl;

	cnt = 0;
	
	memset(cache, -1, sizeof(cache));

	value = DFS2(0, 0, 0);
	cout << value << endl;

	return 0;
}
