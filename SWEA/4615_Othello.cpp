#include<iostream>
#include<vector>

#define EMPTY 0
#define BLACK 1
#define WHITE 2

using namespace std;

int N, M;

class Coord
{
public:
	int x, y;

	Coord(int x_, int y_) : x(x_), y(y_)
	{	}
	
	Coord() : Coord(-1, -1)
	{	}

};


vector<vector<int>> board;

int moveX[8] = { 1,1,0,-1,-1,-1,0,1 };
int moveY[8] = { 0,1,1,1,0,-1,-1,-1 };


void Printboard()
{
	cout << endl;
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			switch (board[row][cul])
			{
			case 0:
				cout << " .";
				break;

			case BLACK:
				cout << "●";
				break;

			case WHITE:
				cout << "○";
				break;

			}
		}
		cout << endl;
	}
	cout << endl;
}


void SetStone(int x, int y, int playerColor)
{
	board[y][x] = playerColor;

	int enemyColor = (playerColor % 2) + 1;

	vector<Coord> command;
	for (int dir = 0; dir < 8; dir++)
	{
		int nextX = x;
		int nextY = y;
		bool isConnect = false;

		while (1)
		{
			nextX += moveX[dir];
			nextY += moveY[dir];

			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N)
				break;

			if (board[nextY][nextX] == playerColor)
			{
				isConnect = true;
				break;
			}

			if (board[nextY][nextX] == EMPTY)
				break;

			if (board[nextY][nextX] == enemyColor)
			{
				command.push_back(Coord(nextX, nextY));
			}
		}

		if (isConnect == true)
		{
			int nowX, nowY;
			for (int i = 0; i < command.size(); i++)
			{
				nowX = command[i].x;
				nowY = command[i].y;

				board[nowY][nowX] = playerColor;
			}
		}

		command.clear();
	}

}

void GetCount(int &whiteCount, int &blackCount)
{
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			if (board[row][cul] == BLACK)
				blackCount++;
			else if (board[row][cul] == WHITE)
				whiteCount++;
		}
	}
}

int main(void)
{
	int T;
	cin >> T;
	int x, y, color;
	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> N >> M;

		board.assign(N, vector<int>(N, EMPTY));

		int mid = N / 2;

		board[mid - 1][mid - 1] = WHITE;
		board[mid - 1][mid] = BLACK;
		board[mid][mid - 1] = BLACK;
		board[mid][mid] = WHITE;

		//Printboard();

		for (int i = 0; i < M; i++)
		{
			cin >> x >> y >> color;
			x--;
			y--;

			SetStone(x, y, color);
			//Printboard();
		}

		int blackCount = 0, whiteCount = 0;
		GetCount(whiteCount, blackCount);

		cout << "#" << testCase + 1 << " " << blackCount << " " << whiteCount << endl;
	}
}


