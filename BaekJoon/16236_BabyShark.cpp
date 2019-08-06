#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

int board[25][25];
int N;

class Node
{
public:
	int x, y, cnt;
	Node(int x_, int y_, int cnt_) : x(x_), y(y_), cnt(cnt_)
	{	}

	Node() :Node(-1, -1, -1)
	{	}

	bool operator < (const Node & rhs) const
	{
		if (cnt != rhs.cnt)
			return cnt < rhs.cnt;
		else if (y != rhs.y)
			return y < rhs.y;
		else
			return x < rhs.x;
	}

};

int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };

class Shark
{
public:
	int x, y, size, exp;


	void Eat()
	{
		exp++;
		if (exp == size)
		{
			exp = 0;
			size++;
		}
	}


	//조건을 만족하는, 먹을 수 있는 물고기를 찾는다.
	int FindFish()
	{
		bool isFindFood = false;
		bool flag[25][25] = { false, };

		vector<Node> canEat;
		queue<Node> qu;
		qu.push(Node(x, y, 0));
		flag[y][x] = true;
		Node cNode;
		int nextX, nextY;
		while (!qu.empty())
		{
			cNode = qu.front();
			qu.pop();

			for (int dir = 0; dir < 4; dir++)
			{
				nextX = cNode.x + moveX[dir];
				nextY = cNode.y + moveY[dir];

				if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N)
					continue;

				if (flag[nextY][nextX] == true)
					continue;

				int otherFish = board[nextY][nextX];

				if (otherFish > size)
					continue;

				if (otherFish < size && otherFish != 0)
				{
					canEat.push_back(Node(nextX, nextY, cNode.cnt + 1));
					isFindFood = true;
				}

				if (otherFish <= size)
				{
					flag[nextY][nextX] = true;
					if (isFindFood == false)
					{
						qu.push(Node(nextX, nextY, cNode.cnt + 1));
					}
				}
			}
		}

		if (canEat.empty() == false)
		{
			sort(canEat.begin(), canEat.end());
			int cX, cY;
			cX = canEat[0].x;
			cY = canEat[0].y;
			board[cY][cX] = 0;	
			Eat();
			x = cX;
			y = cY;
		}

		if (isFindFood == true)
			return canEat[0].cnt;
		else
			return -1;
	}
};

Shark shark;


void PrintBoard()
{
	cout << "\n\n";
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			if (shark.x == cul && shark.y == row)
				cout << "★";
			else
			{
				switch (board[row][cul])
				{
				case 0:
					cout << " .";
					break;

				default:
					cout << " " << board[row][cul];
					break;
				}
			}
		}
		cout << "\n";
	}
}

int Solve()
{
	int time = 0;
	//PrintBoard();
	int cnt;
	while (1)
	{
		cnt = shark.FindFish();

		if (cnt == -1)
			return time;

		time += cnt;

		//PrintBoard();
	}
}


int main(void)
{
	int T = 1;
	//cin >> T;

	for (int testCase = 0; testCase < T; testCase++)
	{
		shark.size = 2;
		shark.exp = 0;

		cin >> N;
		for (int row = 0; row < N; row++)
		{
			for (int cul = 0; cul < N; cul++)
			{
				cin >> board[row][cul];
			
				if (board[row][cul] == 9)
				{
					shark.x = cul;
					shark.y = row;

					board[row][cul] = 0;
				}
			}
		}

		int cnt = Solve();
		cout << cnt << endl;
	}
}
