#include<iostream>
#include<string.h>

#define MOD 9901

using namespace std;

int DFS(int arrSize, int bitMask);

int N, M;
int board[14][14];
int cache[1 << 14][14];

int RPerm(int arrSize, int bitMask, int orgBitMask,int arrSize_)
{
	if (arrSize == M)
	{
		int value = DFS(arrSize_ + 1, bitMask);
		return value;
	}

	int tmp = 0;

	//못쌓는 위치라서 넘어갈 경우
	if ((orgBitMask & (1 << arrSize)) != 0)
	{
		tmp += RPerm(arrSize + 1, bitMask, orgBitMask, arrSize_);
		tmp %= MOD;
	}
	else
	{
		//세로로 쌓을경우
		tmp += RPerm(arrSize + 1, bitMask | (1 << arrSize), orgBitMask, arrSize_);
		tmp %= MOD;

		//가로로 쌓을 경우
		if ((arrSize < M - 1) && ((orgBitMask & (1 << (arrSize + 1))) == 0))
		{
			tmp += RPerm(arrSize + 2, bitMask, orgBitMask, arrSize_);
			tmp %= MOD;
		}
	}

	return tmp;
}


int DFS(int arrSize, int bitMask)
{
	if (arrSize == N && bitMask == 0)
		return 1;
	
	if (arrSize >= N)
		return 0;

	if (cache[bitMask][arrSize] != -1)
		return cache[bitMask][arrSize];

	int ret = RPerm(0, 0, bitMask, arrSize);

	cache[bitMask][arrSize] = ret;

	return ret;
}


int main(void)
{
	memset(cache, -1, sizeof(cache));
	cin >> N >> M;

	int value = DFS(0, 0);
	cout << value << endl;

}
