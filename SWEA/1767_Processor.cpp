#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };

int N;

int board[14][14];

bool chkDir[20][4] = { false, };

class Node
{
public:
	int x, y;
	Node(int x_, int y_): x(x_), y(y_)
	{	}
};


//x,y 위치의 index 코어가 4방향중 어디로 갈 수 있는가를 체크 한다.
void CheckDir(int index, int x, int y)
{
	int nextX, nextY;
	for (int dir = 0; dir < 4; dir++)
	{
		nextX = x;
		nextY = y;

		while (1)
		{
			nextX += moveX[dir];
			nextY += moveY[dir];

			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N)
			{
				chkDir[index][dir] = true;
				break;
			}

			if (board[nextY][nextX] != 0)
				break;
		}
	}
}


void PrintBoard()
{
	cout << "\n\n";

	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			cout << " " << board[row][cul];
		}
		cout << endl;
	}
}


bool MakeWire(int x, int y, int dir, vector<Node> &vc, int &length)
{
	int nextX = x, nextY = y;
	length = 0;

	while (1)
	{
		nextX += moveX[dir];
		nextY += moveY[dir];

		if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N)
			return true;

		if (board[nextY][nextX] != 0)
			return false;

		vc.push_back(Node(nextX, nextY));
		length++;
	}

	return true;
}

vector<Node> chips;
int chipCount;

int maxCore = 0;
int minLength = 99999;

//4 PI (칩의 갯수)
void RPerm(int arrSize, int length, int core)
{
	if (arrSize == chipCount)
	{
		if (core > maxCore)
		{
			maxCore = core;
			minLength = length;
		}
		else if (core == maxCore)
			minLength = min(minLength, length);

		return;
	}

	int leftCore = maxCore - core;
	int leftIndex = chipCount - arrSize + 1;

	if (leftCore > leftIndex)
		return;

	vector<Node> vc;
	int cnt = 0;
	bool result;

	//arrSize 번째 칩에 전선 연결 안한경우
	RPerm(arrSize + 1, length, core);

	for (int dir = 0; dir < 4; dir++)
	{
		
		if (chkDir[arrSize][dir] == false)
			continue;
		

		cnt = 0;
		vc.clear();

		//arrSize 번째의 칩을 dir 방향으로 선을 연결한다.
		//false가 반환되어 연결이 불가능 한 경우에는 재귀호출 X
		
		result = MakeWire(chips[arrSize].x, chips[arrSize].y, dir, vc, cnt);

		if (result == true)
		{
			for (int i = 0; i < vc.size(); i++)
			{
				int cX = vc[i].x;
				int cY = vc[i].y;
				board[cY][cX] = 1;
			}

			RPerm(arrSize + 1, length + cnt, core + 1);
		
			for (int i = 0; i < vc.size(); i++)
			{
				int cX = vc[i].x;
				int cY = vc[i].y;
				board[cY][cX] = 0;
			}
		}		
	}
}


int main(void)
{
	int T;
	cin >> T;
	int input;
	for (int testCase = 0; testCase < T; testCase++)
	{
		maxCore = 0;
		minLength = 99999;

		chips.clear();
		cin >> N;

		for (int row = 0; row < N; row++)
		{
			for (int cul = 0; cul < N; cul++)
			{
				cin >> input;
				board[row][cul] = input;

				if (input == 1)
				{
					if(row != 0 && row != N - 1&& cul != 0 && cul != N - 1)	
						chips.push_back(Node(cul, row));
				}
			}
		}

		chipCount = chips.size();

		for (int i = 0; i < chipCount; i++)
		{
			for (int dir = 0; dir < 4; dir++)
			{
				chkDir[i][dir] = false;
			}
		
			CheckDir(i, chips[i].x, chips[i].y);
		}

		RPerm(0, 0, 0);
		
		cout << "#" << testCase + 1 << " " << minLength << endl;
	}
}
