#include<iostream>
#include<string.h>

#define RIGHT	0
#define DOWN	1
#define LEFT	2
#define UP		3

using namespace std;

int board[20][20];

int *lineX[20][20];
int *lineY[20][20];

int N;
char str[10];

void SetLine()
{
	//x방향 라인
	for (int row = 0; row < 20; row++)
	{
		for (int cul = 0; cul < 20; cul++)
		{
			lineX[row][cul] = &board[row][cul];
			lineY[cul][row] = &board[row][cul];
		}
	}
}


void PrintBoard()
{
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			cout << board[row][cul] << " ";
		}
		cout << "\n";
	}
}


void SlideLine(int *line[20])
{
	bool flag[20] = { false, };

	for (int i = N - 1; i >= 0; i--)
	{
		if (*line[i] != 0)
		{
			for (int j = i + 1; j <= N; j++)
			{
				if (j == N)
				{
					int value = *line[i];
					*line[i] = 0;
					*line[j - 1] = value;
					break;
				}

				if (*line[j] != 0)
				{
					if (*line[j] == *line[i] && flag[j] != true)
					{
						flag[j] = true;
						*line[i] = 0;
						*line[j] *= 2;
						break;
					}
					else
					{
						int value = *line[i];
						*line[i] = 0;
						*line[j - 1] = value;
						break;
					}
				}
			}
		}
	}
}


void ReverseSlideLine(int *line[20])
{
	bool flag[20] = { false, };

	for (int i = 0; i <= N - 1; i++)
	{
		if (*line[i] != 0)
		{
			for (int j = i - 1; j >= -1; j--)
			{
				if (j == -1)
				{
					int value = *line[i];
					*line[i] = 0;
					*line[j + 1] = value;
					break;
				}

				if (*line[j] != 0)
				{
					if (*line[j] == *line[i] && flag[j] != true)
					{
						flag[j] = true;
						*line[i] = 0;
						*line[j] *= 2;
						break;
					}
					else
					{
						int value = *line[i];
						*line[i] = 0;
						*line[j + 1] = value;
						break;
					}
				}
			}
		}
	}
}



void MoveRight()
{
	for (int row = 0; row < N; row++)
	{
		SlideLine(lineX[row]);
	}
}

void MoveLeft()
{
	for (int row = 0; row < N; row++)
	{
		ReverseSlideLine(lineX[row]);
	}
}


void MoveDown()
{
	for (int cul = 0; cul < N; cul++)
	{
		SlideLine(lineY[cul]);
	}
}

void MoveUp()
{
	for (int cul = 0; cul < N; cul++)
	{
		ReverseSlideLine(lineY[cul]);
	}

}


void Move(int dir)
{
	switch (dir)
	{
	case RIGHT:
		MoveRight();
		break;

	case DOWN:
		MoveDown();
		break;

	case LEFT:
		MoveLeft();
		break;

	case UP:
		MoveUp();
		break;
	}
}

int GetDir()
{
	char *ptr = strstr(str, "up");
	if (ptr != NULL)
		return UP;

	ptr = strstr(str, "right");
	if (ptr != NULL)
		return RIGHT;

	ptr = strstr(str, "down");
	if (ptr != NULL)
		return DOWN;

	ptr = strstr(str, "left");
	if (ptr != NULL)
		return LEFT;

}

int main(void)
{
	SetLine();
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> N >> str;

		for (int row = 0; row < N; row++)
		{
			for (int cul = 0; cul < N; cul++)
			{
				cin >> board[row][cul];
			}
		}

		int dir = GetDir();

		Move(dir);
		cout << "#" << testCase + 1 << endl;
		PrintBoard();


		/*
		int input;
		while (1)
		{
			cin >> input;

			Move(input);
			PrintBoard();
			
		}
		*/

	}

	return 0;
}
