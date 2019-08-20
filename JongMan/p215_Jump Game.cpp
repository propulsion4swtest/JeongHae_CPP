#include<iostream>
#include<vector>

using namespace std;


/*
7
2 5 1 6 1 4 1
6 1 1 2 2 9 3
7 2 3 2 1 3 1
1 1 3 1 7 1 2
4 1 2 3 4 1 2
3 3 1 2 3 4 1
1 5 2 9 4 7 0
*/

vector<vector<int>> board;
vector<vector<bool>> flag;

int n;

bool isClear = false;
void Solve(int x, int y)
{
	if (isClear == true)
		return;

	if(flag[y][x] == true)
		return;

	if (x == n - 1 && y == n - 1)
	{
		//clear;
		isClear = true;
		return;
	}

	flag[y][x] = true;

	int value = board[y][x];

	if(x + value < n)
		Solve(x + value, y);

	if(y + value < n)
		Solve(x, y + value);
}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		isClear = false;

		cin >> n;
		board.assign(n, vector<int>(n, -1));
		flag.assign(n, vector<bool>(n, false));
		int input;
		for (int row = 0; row < n; row++)
		{
			for (int cul = 0; cul < n; cul++)
			{
				cin >> input;
				board[row][cul] = input;
			}
		}

		Solve(0, 0);

		if (isClear == true)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

}
