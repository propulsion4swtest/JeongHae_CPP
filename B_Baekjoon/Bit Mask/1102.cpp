#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int N, P;
int path[16][16];
char str[20];

int cache[1 << 16];

//arrSize = 회복된 발전기 갯수
int DFS(int arrSize, int bitMask, int score)
{
	if (arrSize >= P)
		return score;

	if (cache[bitMask] != -1)
		return cache[bitMask] + score;

	int tmp, ret = 2000000000;
	int tmpMask;
	for (int i = 0; i < N; i++)	//꺼진 발전기를 고른다
	{
		if ((bitMask & (1 << i)) == 0)
		{
			for (int j = 0; j < N; j++)	//켜진 발젼기를 고른다
			{
				if ((i != j) && ((bitMask & (1 << j)) != 0))
				{
					//j번 발전기로 i번 발전기를 킨다.
					tmpMask = bitMask | (1 << i);
					
					tmp = DFS(arrSize + 1, tmpMask, score + path[j][i]);
					ret = min(tmp, ret);					
				}
			}
		}
	}

	cache[bitMask] = ret - score;
	return ret;
}

//가동된 발전기의 갯수 반환
int Awaken(int &bitMask)
{
	int cnt = 0;
	for(int i=0; i<N; i++)
	{
		if (str[i] == 'Y')
		{
			bitMask = bitMask | (1 << i);
			cnt++;
		}
	}

	return cnt;
}


int main(void)
{
	memset(cache, -1, sizeof(cache));
	cin >> N;
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			cin >> path[row][cul];
		}
	}
	cin >> str;
	cin >> P;

	int bitMask = 0, cnt = 0;
	cnt = Awaken(bitMask);

	int value = DFS(cnt, bitMask, 0);
	if (value < 200000000)
		cout << value << endl;
	else
		cout << -1 << endl;

	return 0;
}
