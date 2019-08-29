#include<iostream>
#include<string.h>

using namespace std;

int N;

long long cache[2][100];
//arrSize는 1부터 시작한다(맨처음에 올 수는 1으로 고정 되 있으므로)
long long DFS(int arrSize, int prev)
{
	if (arrSize == N)
		return 1;
	
	
	if (cache[prev][arrSize] != -1)
		return cache[prev][arrSize];	
		
	long long ret = 0;
	//0이 올 경우
	ret += DFS(arrSize + 1, 0);	

	//1이 올 경우
	if (prev == 0)
		ret += DFS(arrSize + 1, 1);
			
	cache[prev][arrSize] = ret;

	return ret;
}

int main(void)
{
	memset(cache, -1, sizeof(cache));
	cin >> N;

	long long value = DFS(1, 1);

	cout << value << endl;

	return 0;
}
