#include<iostream>
#include<algorithm>
#include<string.h>

#define RED		0
#define GREEN	1
#define BLUE	2

using namespace std;

int N;
int costs[1005][3];	//costs[a][b]  : a번 집을 b 색깔로 바꾸는 데 드는 비용

int houses[1005];
int cache[1005][3];

int RPerm(int arrSize, int cost)
{
	if (arrSize == N)
		return cost;
	
	int pColor = houses[arrSize - 1];

	if (cache[arrSize][pColor] != -1)
		return cost + cache[arrSize][pColor];

	int tmp;
	int ret = 2000000000;

	int cCost;
	for (int color = 0; color < 3; color++)
	{
		if (houses[arrSize - 1] != color)
		{
			houses[arrSize] = color;
			cCost = costs[arrSize][color];

			
			tmp = RPerm(arrSize + 1, cost + cCost);
			ret = min(tmp, ret);			
		}
	}

	cache[arrSize][pColor] = ret - cost;
	return ret;
}


int main(void)
{
	memset(cache, -1, sizeof(cache));
	cin >> N;
	for (int row = 0; row < N; row++)
	{
		for (int color = 0; color < 3; color++)
		{
			cin >> costs[row][color];
		}
	}

	int tmp, ret;
	ret = 2000000000;
	for (int color = 0; color < 3; color++)
	{
		houses[0] = color;
		tmp  =RPerm(1, costs[0][color]);
		ret = min(tmp, ret);
	}

	cout << ret << endl;

	return 0;
}

