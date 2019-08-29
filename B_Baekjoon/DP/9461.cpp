#include<iostream>
#include<string.h>

using namespace std;

long long cache[100];

long long GetCache(int index)
{
	if (cache[index] != -1)
		return cache[index];

	long long lhs, rhs;

	if (cache[index - 1] != -1)
		lhs = cache[index - 1];
	else
		lhs = GetCache(index - 1);
	

	if (cache[index - 5] != -1)
		rhs = cache[index - 5];
	else
		rhs = GetCache(index - 5);
		
	long long tmp = lhs + rhs;
	cache[index] = tmp;
	return tmp;
}


int main(void)
{
	memset(cache, -1, sizeof(cache));

	cache[0] = 1;
	cache[1] = 1;
	cache[2] = 1;
	cache[3] = 2;
	cache[4] = 2;
	cache[5] = 3;
	cache[6] = 4;
	cache[7] = 5;
	cache[8] = 7;
	cache[9] = 9;
	cache[10] = 12;

	GetCache(99);

	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		int N;
		cin >> N;

		cout << cache[N - 1] << endl;
	}


	return 0;
}
