#include<iostream>
#include<string.h>

using namespace std;

int DFS(int arrSize, int bitMask);

int N;
int cache[1000][1 << 4];

int RPerm(int cul, int cBitMask, int nBitMask, int arrSize)
{
	if (cBitMask == 0b1111)
	{
		//DFS 재귀호출(DFS에서 반환된 값을 그대로 반환)
		int value = DFS(arrSize + 1, nBitMask);
		return value;
	}

	int ret = 0;
	//이미 블록이 있을경우
	if ((cBitMask & (1 << cul)) != 0)
	{
		ret += RPerm(cul + 1, cBitMask, nBitMask, arrSize);
	}
	else //블록이 없을 경우
	{
		//세로로 놓을 경우		
		ret += RPerm(cul + 1, cBitMask | (1 << cul), nBitMask | (1 << cul), arrSize);

		//가로로 놓을 경우
		if (cul <= 2)
		{
			if ((cBitMask & (1 << (cul + 1))) == 0)
				ret += RPerm(cul + 1, cBitMask | (1 << cul) | (1 << (cul + 1)), nBitMask, arrSize);
		}
	}
	return ret;
}


//bitMask : 현재 층의 상태
int DFS(int arrSize, int bitMask)
{
	if (arrSize == N && bitMask == 0b0000)
		return 1;

	if (arrSize > N)
		return 0;

	if (cache[bitMask][arrSize] != -1)
		return cache[bitMask][arrSize];

	int ret = RPerm(0, bitMask, 0, arrSize);
	cache[bitMask][arrSize] = ret;
	return ret;
}

int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> N;

		memset(cache, -1, sizeof(cache));
		int value = DFS(0, 0);
		cout << value << endl;
		//int value = RPerm(0, 0b0100, 0, 0, 0);
		//cout << value;
	}



	return 0;
}
