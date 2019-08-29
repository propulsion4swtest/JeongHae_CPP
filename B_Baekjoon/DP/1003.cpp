#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int zeroCache[45];
int oneCache[45];


void Fibo(int arrSize, int &zero, int &one)
{
	if (arrSize == 0)
	{
		zero++;
		return;
	}

	if (arrSize == 1)
	{
		one++;
		return;
	}

	if (zeroCache[arrSize] != -1)
	{
		zero += zeroCache[arrSize];
		one += oneCache[arrSize];
		return;
	}

	Fibo(arrSize - 1, zero, one);
	Fibo(arrSize - 2, zero, one);
	
	zeroCache[arrSize] = zero;
	oneCache[arrSize] = one;

	return;
}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		memset(zeroCache, -1, sizeof(zeroCache));
		memset(oneCache, -1, sizeof(oneCache));

		int N;
		cin >> N;

		int zero= 0, one = 0;
		Fibo(N, zero, one);
		cout << zero << " " << one << endl;
	}

	return 0;
}
