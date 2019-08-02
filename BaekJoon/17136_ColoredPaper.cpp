#include<iostream>
#include<algorithm>

using namespace std;

const int N = 10;
bool board[12][12];


//x,y 위치에 올 수 있는 색종이의 최대 크기를 구한다

int paperCnt[5];


//범위를 벗어날 경우의 조건에 신경 써야 한다.
int GetSize(int x, int y)
{
	for (int cul = 0; cul < N; cul++)
	{
		if (x + cul >= N || y + cul >= N)
			return cul;

		if (board[y + cul][x + cul] == true)
			return cul;

		for (int row = 0; row < cul; row++)
		{
			if (y + row >= N || x + cul >= N || y + cul >= N || x + row >= N)
				return cul;

			if (board[y + row][x + cul] == true)
				return cul;

			if (board[y + cul][x + row] == true)
				return cul;
		}
	}
}


//현재 좌표에 설치 가능하면 그 좌표를 반환한다.
void GetNext(int &x, int &y)
{
	while (1)
	{
		if (board[y][x] == false)
			return;

		x++;
		if (x == N)
		{
			x = 0;
			y++;

			if (y == N)
			{
				y = -1;
				x = -1;
				return;
			}
		}
	}
}


void PaintBoard(int x, int y, int size, bool type)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < i; j++)
		{
			board[y + j][x + i] = type;
			board[y + i][x + j] = type;
		}
		board[y + i][x + i] = type;
	}
}


void PrintBoard()
{
	cout << "\n\n";
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			if (board[row][cul] == true)
				cout << "■";
			else
				cout << " .";
		}
		cout << endl;
	}
}


int minCnt = 2000000;
//(해당구역의 크기 + 1) PI (모든 좌표)
void RPerm(int arrSize, int x, int y)
{
	GetNext(x, y);

	if (x == -1 || y == -1)
	{
		minCnt = min(minCnt, arrSize);
		return;
	}

	if (arrSize >= minCnt)
		return;

	int maxSize = GetSize(x, y);
	maxSize = min(maxSize, 5);

	for (int i = maxSize; i >= 1; i--)
	{
		//arr[arrSize] = i;
		//x,y좌표에 i 크기의 색종이를 덮는다.
		if (paperCnt[i - 1] > 0)
		{
			PaintBoard(x, y, i, true);
			paperCnt[i - 1]--;
			RPerm(arrSize + 1, x, y);
			paperCnt[i - 1]++;
			PaintBoard(x, y, i, false);
		}
		//x,y좌표에서 i크기의 색종이를 제거한다.
	}
}



int main(void)
{
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			cin >> board[row][cul];
			board[row][cul] = !board[row][cul];
		}
	}

	for (int i = 0; i < 5; i++)
		paperCnt[i] = 5;

	
	RPerm(0, 0, 0);
	if (minCnt < 200000)
		cout << minCnt << endl;
	else
		cout << -1 << endl;
	
	
	/*
	int value = GetSize(8, 7);
	cout << value << endl;
	*/

	/*
	PaintBoard(3, 3, 5);
	PrintBoard();
	*/
}
