#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, M, D;
bool board[20][20];
bool orgBoard[20][20];

class Coord
{
public:
	int x, y;
	Coord(int x_, int y_) : x(x_), y(y_)
	{	}


	Coord() :Coord(-1, -1)
	{	}


	bool operator < (const Coord &rhs) const
	{
		int dist, rhsDist;
		dist = abs(x) + abs(y);
		rhsDist = abs(rhs.x) + abs(rhs.y);

		if (dist != rhsDist)
			return dist < rhsDist;
		else
			return x < rhs.x;
	}

};


class Archer
{
public:
	int x, y;
	vector<Coord> range;

	//변수 D범위만큼 range에 유효한 좌표를 넣는다
	void SetRange(int D)
	{
		for (int row = 0; row <= D; row++)
			range.push_back(Coord(0, -1 * row));		

		for (int cul = 1; cul <= D; cul++)
		{
			for (int row = 0; row <= D - cul; row++)
			{
				range.push_back(Coord(cul, -1 * row));
				range.push_back(Coord(-1 * cul, -1 * row));
			}
		}

		sort(range.begin(), range.end());
	}


	//궁수의 위치에 맞추어서 조건에 맞는 타겟의 좌표를 반환한다.
	//false : 사격 가능한 타겟이 없다
	bool GetTarget(Coord &target)
	{
		int cX, cY;
		for (int i = 0; i < range.size(); i++)
		{
			cX = x + range[i].x;
			cY = y + range[i].y;
			if (cX < 0 || cX >= M || cY < 0 || cY >= N)
				continue;

			if (board[cY][cX] == true)
			{
				target.x = cX;
				target.y = cY;
				return true;
			}
		}
		target.x = -1;
		target.y = -1;
		return false;
	}
};

Archer archers[3];
int orgCnt = 0;
int cnt;
int killCnt = 0;
int maxCnt = 0;
int arr[20];

//궁수의 위치가 정해지면 

//1초 동안의 시뮬을 담당한다.
void Simulation()
{
	//궁수가 타겟을 잡는다.
	Coord targets[3];
	for (int i = 0; i < 3; i++)
		archers[i].GetTarget(targets[i]);
	

	//각 궁수의 타겟에 사격을 한다
	for (int i = 0; i < 3; i++)
	{
		int cX, cY;
		cX = targets[i].x;
		cY = targets[i].y;

		if (cX != -1 && cY != -1)
		{
			if (board[targets[i].y][targets[i].x] == true)
			{
				killCnt++;
				cnt--;
			}
		board[targets[i].y][targets[i].x] = false;
		}
	}



	//적을 한칸씩 아래로 내린다.
	for (int cul = 0; cul < M; cul++)
	{
		if (board[N - 1][cul] == true)
			cnt--;

		board[N - 1][cul] = false;

		for (int row = N - 1; row >= 1; row--)
			board[row][cul] = board[row - 1][cul];

		board[0][cul] = false;
	}
}

void PrintBoard()
{
	cout << "\n\n";
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < M; cul++)
		{
			if (board[row][cul] == true)
				cout << "■";
			else
				cout << " .";

		}
		cout << endl;
	}
}

void StartSimulation()
{
	//PrintBoard();
	cnt = orgCnt;
	killCnt = 0;

	while (cnt > 0)
	{
		Simulation();
		//PrintBoard();
	}

	maxCnt = max(maxCnt, killCnt);
}

//m = M , n = 3
void Comb(int arrSize, int index)
{
	if (arrSize == 3)
	{
		for (int i = 0; i < 3; i++)
			archers[i].x = arr[i];

		for (int row = 0; row < N; row++)
			for (int cul = 0; cul < M; cul++)
				board[row][cul] = orgBoard[row][cul];
		
		StartSimulation();

		return;
	}


	if (index == M)
		return;

	arr[arrSize] = index;
	Comb(arrSize + 1, index + 1);
	Comb(arrSize, index + 1);
}


int main(void)
{
	cin >> N >> M >> D;

	for (int i = 0; i < 3; i++)
	{
		archers[i].y = N;
		archers[i].SetRange(D);
	}

	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < M; cul++)
		{
			cin >> orgBoard[row][cul];

			if (orgBoard[row][cul] == true)
				orgCnt++;
		}
	}

	Comb(0, 0);
	cout << maxCnt << endl;

	/*
	archers[0].x = 0;
	archers[1].x = 2;
	archers[2].x = 4;

	StartSimulation();
	*/
}
