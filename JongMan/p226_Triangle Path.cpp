#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> Triangle;
vector<vector<int>> Cache;
int N;

/*
5
6
1 2
3 7 4
9 4 1 7
2 7 5 9 4
*/

int maxValue = -1;
void Solve(int x, int y, int score)
{
	if(y == N - 1)
	{
		Cache[y][x] = max(Cache[y][x], score);
		maxValue = max(maxValue, Cache[y][x]);
		return;
	}

	if(Cache[y][x] >= score)
		return;
	else
		Cache[y][x] = score;	

	Solve(x, y + 1, Triangle[y + 1][x] + score);

	Solve(x + 1, y + 1, Triangle[y + 1][x + 1] + score);
}



int main(void)
{
	cin >> N;
	Triangle.assign(N, vector<int>(N, -1));
	Cache.assign(N, vector<int>(N, -1));
	int input;
	for(int row = 0; row<N; row++)
	{
		for(int cul = 0; cul < row + 1; cul++)
		{
			cin >> input;
			Triangle[row][cul] = input;
		}
	}

	Solve(0,0,Triangle[0][0]);
	cout<<maxValue<<endl;

	return 0;
}
