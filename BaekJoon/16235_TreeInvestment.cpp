#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int moveX[8] = { 1,1,0,-1,-1,-1,0,1 };
int moveY[8] = { 0,1,1,1,0,-1,-1,-1 };

int N, M, K;
class Tile
{
public:
	int x, y;
	vector<int> trees;
	vector<int> deathTrees;
	int food;

	//봄에 모든 나무들이 양분을 먹고 양분 부족시 죽인다
	void Spring()
	{
		int i = 0;
		for (; i < trees.size(); i++)
		{
			if (food >= trees[i])
			{
				food -= trees[i];
				trees[i]++;
			}
			else break;
		}

		for (int j = i; j < trees.size(); j++)
		{
			if (trees[j] / 2 > 0)
				deathTrees.push_back(trees[j] / 2);
		}

		trees.erase(trees.begin() + i, trees.end());
	}


	void Summer()
	{
		if (deathTrees.empty())
			return;

		for (int i = 0; i < deathTrees.size(); i++)
		{
			food += deathTrees[i];
		}

		deathTrees.clear();
	}


	void Autumn(Tile board[12][12])
	{
		int nextX, nextY;

		for (int i = 0; i < trees.size(); i++)
		{
			if (trees[i] % 5 == 0)
			{
				for (int dir = 0; dir < 8; dir++)
				{
					nextX = x + moveX[dir];
					nextY = y + moveY[dir];

					if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N)
						continue;

					board[nextY][nextX].trees.insert(board[nextY][nextX].trees.begin(), 1);
				}
			}

		}

	}

};


Tile board[12][12];
int S2D2[12][12];


void Spring()
{
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			board[row][cul].Spring();
		}
	}
}



void Summer()
{
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			board[row][cul].Summer();
		}
	}
}


void Autumn()
{
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			board[row][cul].Autumn(board);
		}
	}
}


void Winter()
{
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			board[row][cul].food += S2D2[row][cul];
		}
	}
}

int GetCount()
{
	int cnt = 0;
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			cnt += board[row][cul].trees.size();
		}
	}
	return cnt;
}


int Simulation()
{
	for (int time = 0; time < K; time++)
	{
		Spring();
		Summer();
		Autumn();
		Winter();
	}

	int cnt = GetCount();
	return cnt;
}

int main(void)
{
	cin >> N >> M >> K;

	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			cin >> S2D2[row][cul];
			board[row][cul].food = 5;
			board[row][cul].x = cul;
			board[row][cul].y = row;
		}
	}

	int r, c, age;
	for (int i = 0; i < M; i++)
	{
		cin >> r >> c >> age;
		r--;
		c--;

		board[r][c].trees.push_back(age);
	}

	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			sort(board[r][c].trees.begin(), board[r][c].trees.end());
		}
	}

	int cnt = Simulation();
	cout << cnt << endl;

	return 0;
}
