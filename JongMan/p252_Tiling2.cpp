#include<iostream>
#include<algorithm>
#include<string.h>

#define DIV 1000000007

using namespace std;

int N;

int cache[2][100];

//100 - N을 전달받는다.
/*
int GetValue(int index)
{
	int tmp = cache[0][index] + cache[1][index];
	return tmp;
}
*/

int DFS(int arrSize)
{
	if (arrSize == N)
		return 1;

	int ret = 0;
	int tmp1 = 0, tmp2 = 0;
	//세로로 놓을 경우
	if (arrSize + 1 <= N) {
		if (cache[0][arrSize] == -1) {
			tmp1 = DFS(arrSize + 1);
			cache[0][arrSize] = tmp1;
		}
		else
			tmp1 = cache[0][arrSize];
	}
	tmp1 %= DIV;
	ret += tmp1;


	//가로로 놓을 경우
	if (arrSize + 2 <= N) {
		if (cache[1][arrSize] == -1) {
			tmp2 = DFS(arrSize + 2);
			cache[1][arrSize] = tmp2;
		}
		else
			tmp2 = cache[1][arrSize];
	}
	tmp2 %= DIV;
	ret += tmp2;

	ret %= DIV;
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

		//int value = GetValue(100 - N);
		int value = DFS(0);		
		cout << value << endl;
	}


	return 0;
}
