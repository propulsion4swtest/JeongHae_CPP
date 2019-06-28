
#include<iostream>
#include<vector>

using namespace std;

int N;

vector<vector<vector<int>>> cache;


int DFS(int start, int length, int num)
{
	if (length == N)
	{
		if (num == 0b1111111111)
			return 1;
		
		else
			return 0;		
	}


	if (cache[start][length][num] != -1)
		return cache[start][length][num];

	int count = 0;
	cache[start][length][num] = 0;


	if (start - 1 >= 0)
	{
		int nextNum = num | (1 << (start - 1));
		count += DFS(start - 1, length + 1, nextNum);
		cache[start][length][num] = count;
	}
	
	count %= 1000000000;
	cache[start][length][num] %= 1000000000;

	if (start + 1 <= 9)
	{
		int nextNum = num | (1 << (start + 1));
		count += DFS(start + 1, length + 1, nextNum);
		cache[start][length][num] = count;
	}
	count %= 1000000000;
	cache[start][length][num] %= 1000000000;

	

	return count;
}

// a = cache[start][length][num] : length에 start숫자가 있으며
//numbit의 정수들이 포함되어 있을 경우 a개의 삐끗수를 가진다.

int main(void)
{
	int T;
	cin >> T;

	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> N;

		cache.assign(10, vector<vector<int>>(N, (vector<int>(0b1111111111 + 1, -1))));
		int result = 0;
		for (int start = 1; start <= 9; start++)
		{
			result += DFS(start, 1, 1 << start);
			result %= 1000000000;
		}

		cout << "#" << testCase + 1 << " " << result << endl;
	}


	return 0;
}
