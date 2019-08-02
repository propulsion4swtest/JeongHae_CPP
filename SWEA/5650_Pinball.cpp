/*
#include<iostream>
#include<algorithm>
 
using namespace std;
 
bool warmHoleFlag[5];
int holeY[5] = { 0, };
int holeX[5] = { 0, };
 
 
class Tile
{
public:
    int type;
 
    int reflect[4];
 
    int warmHoleX;
    int warmHoleY;
     
    void SetReflect()
    {
        switch (type)
        {
        case 1:
            reflect[1] = 0;
            reflect[2] = 3;
            reflect[0] = 2;
            reflect[3] = 1;
            break;
 
        case 2:
            reflect[3] = 0;
            reflect[2] = 1;
            reflect[0] = 2;
            reflect[1] = 3;
            break;
 
        case 3:
            reflect[0] = 1;
            reflect[3] = 2;
            reflect[1] = 3;
            reflect[2] = 0;
            break;
 
        case 4:
            reflect[0] = 3;
            reflect[1] = 2;
            reflect[3] = 1;
            reflect[2] = 0;
            break;
 
        case 5:
            reflect[2] = 0;
            reflect[0] = 2;
            reflect[1] = 3;
            reflect[3] = 1;
            break;
        }
    }
 
    void SetWarmHole(int x, int y, Tile board[100][100])
    {
        int index = type - 6;
        if (warmHoleFlag[index] == false)
        {
            warmHoleFlag[index] = true;
            holeY[index] = y;
            holeX[index] = x;
        }
        else
        {
            int cX = holeX[index];
            int cY = holeY[index];
 
            warmHoleX = cX;
            warmHoleY = cY;
             
            board[cY][cX].warmHoleX = x;
            board[cY][cX].warmHoleY = y;
        }
    }
 
};
 
Tile board[100][100];
 
int N;
 
int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };
 
int path[4][100][100];
 
 
int Simulation(int x, int y, int dir)
{
    int startX = x;
    int startY = y;
    int startDir = dir;
 
    int nX, nY;
    int cnt = 0;
    while (1)
    {
        //PrintBoard(x, y);
 
        nX = x + moveX[dir];
        nY = y + moveY[dir];
 
        if (nX < 0 || nX >= N || nY < 0 || nY >= N)
        {
            //벽에 부딪힘
            dir = (dir + 2) % 4;
            cnt *= 2;
            cnt++;
            break;
        }
        else
        {
            if (board[nY][nX].type >= 1 && board[nY][nX].type <= 5)
            {
                //블록에 부딪힘
                int tmpDir = board[nY][nX].reflect[dir];
                 
                if (dir == (tmpDir + 2) % 4)
                {
                    cnt *= 2;
                    cnt++;
                    break;
                }
 
                dir = tmpDir;
                cnt++;
            }
            else if (board[nY][nX].type >= 6 && board[nY][nX].type <= 10)
            {
                //웜홀에 들어감
                int tmpX = board[nY][nX].warmHoleX;
                int tmpY = board[nY][nX].warmHoleY;
                nX = tmpX;
                nY = tmpY;
            }
            else if (board[nY][nX].type == -1)
            {
                //블랙홀에 들어감
                break;
            }
        }
 
        x = nX;
        y = nY;
 
        if (x == startX && y == startY)
            break;
    }
 
 
    return cnt;
}
 
 
 
int main(void)
{
    int T;
    cin >> T;
    for (int testCase = 0; testCase < T; testCase++)
    {
        cin >> N;
 
        for (int i = 0; i < 5; i++)
            warmHoleFlag[i] = false;
 
        int type;
        for (int row = 0; row < N; row++)
        {
            for (int cul = 0; cul < N; cul++)
            {
                cin >> type;
                board[row][cul].type = type;
 
                if (type >= 1 && type <= 5)
                    board[row][cul].SetReflect();
                else if (type >= 6 && type <= 10)
                    board[row][cul].SetWarmHole(cul, row, board);
            }
        }
         
        int ret = 0;
        int tmp = 0;
        for (int row = 0; row < N; row++)
        {
            for (int cul = 0; cul < N; cul++)
            {
                if (board[row][cul].type == 0)
                {
                    for (int dir = 0; dir < 4; dir++)
                    {
                        tmp = Simulation(cul, row, dir);
                        ret = max(tmp, ret);
                    }
                }
            }
        }       
 
        //int ret = Simulation(4, 0, 0);
         
        cout << "#" << testCase + 1 << " " << ret << endl;
 
    }
 
}
*/


#include<iostream>
#include<vector>
#include<algorithm>

#define RAIL 0
#define CYCLE 1
#define BLACKHOLE 2


using namespace std;

bool warmHoleFlag[5];
int holeY[5] = { 0, };
int holeX[5] = { 0, };

class Node
{
public:
	int x, y, dir, value;

	Node(int x_, int y_, int dir_, int value_) : x(x_), y(y_), dir(dir_), value(value_)
	{	}
};

class Tile
{
public:
	int type;

	int reflect[4];

	int warmHoleX;
	int warmHoleY;
	
	void SetReflect()
	{
		switch (type)
		{
		case 1:
			reflect[1] = 0;
			reflect[2] = 3;
			reflect[0] = 2;
			reflect[3] = 1;
			break;

		case 2:
			reflect[3] = 0;
			reflect[2] = 1;
			reflect[0] = 2;
			reflect[1] = 3;
			break;

		case 3:
			reflect[0] = 1;
			reflect[3] = 2;
			reflect[1] = 3;
			reflect[2] = 0;
			break;

		case 4:
			reflect[0] = 3;
			reflect[1] = 2;
			reflect[3] = 1;
			reflect[2] = 0;
			break;

		case 5:
			reflect[2] = 0;
			reflect[0] = 2;
			reflect[1] = 3;
			reflect[3] = 1;
			break;
		}
	}

	void SetWarmHole(int x, int y, Tile board[100][100])
	{
		int index = type - 6;
		if (warmHoleFlag[index] == false)
		{
			warmHoleFlag[index] = true;
			holeY[index] = y;
			holeX[index] = x;
		}
		else
		{
			int cX = holeX[index];
			int cY = holeY[index];

			warmHoleX = cX;
			warmHoleY = cY;
			
			board[cY][cX].warmHoleX = x;
			board[cY][cX].warmHoleY = y;
		}
	}

};

Tile board[100][100];

int N;

int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };

int railCache[4][100][100];
int cycleCache[4][100][100];
int blackHoleCache[4][100][100];

void PrintBoard(int x, int y)
{
	cout << "\n\n";
	for (int row = 0; row < N; row++)
	{
		for (int cul = 0; cul < N; cul++)
		{
			if (row == y && cul == x)
				cout <<  "●";
			else
			{
				switch (board[row][cul].type)
				{
				case 0:
					cout << " .";
					break;

				case 1:
					cout << "↗";
					break;

				case 2:
					cout << "↘";
					break;

				case 3:
					cout << "↙";
					break;

				case 4:
					cout <<  "↖";
					break;

				case 5:
					cout << "♬";
					break;

				case -1:
					cout << "♣";
					break;

				default :
					cout << " " << board[row][cul].type;
					break;
				}
			}
		}
		cout << endl;
	}
}

vector<Node> nodes;

int Simulation(int argX, int argY, int argDir)
{
	nodes.clear();

	int x = argX, y = argY, dir = argDir;

	int startX = x;
	int startY = y;
	int startDir = dir;

	int nX, nY;
	int cnt = 0;
	int maxLength;
	
	int endType = -1;

	while (1)
	{
		//PrintBoard(x, y);
	
		
		if (railCache[dir][y][x] != -1)
		{
			endType = RAIL;
			cnt = railCache[dir][y][x] + cnt;
			maxLength = 2 * cnt + 1;
			break;
		}

		if (cycleCache[dir][y][x] != -1)
		{
			return (cycleCache[dir][y][x] * 2) + 1;
		}

		if (blackHoleCache[dir][y][x] != -1)
		{
			endType = BLACKHOLE;
			cnt = blackHoleCache[dir][y][x] + cnt;
			maxLength = cnt;
			break;
		}

		if (board[y][x].type == 0)
			nodes.push_back(Node(x, y, dir, cnt));



		nX = x + moveX[dir];
		nY = y + moveY[dir];
		
		if (nX < 0 || nX >= N || nY < 0 || nY >= N)
		{
			//벽에 부딪힘(rail로 끝난다.)
			endType = RAIL;
			maxLength = cnt * 2 + 1;
			break;
		}
		else
		{
			if (board[nY][nX].type >= 1 && board[nY][nX].type <= 5)
			{
				//블록에 부딪힘
				int tmpDir = board[nY][nX].reflect[dir];

				if (dir == (tmpDir + 2) % 4)
				{
					//rail로 끝남
					endType = RAIL;
					maxLength = cnt * 2 + 1;
					break;
				}

				dir = tmpDir;
				cnt++;
			}
			else if (board[nY][nX].type >= 6 && board[nY][nX].type <= 10)
			{
				//웜홀에 들어감
				int tmpX = board[nY][nX].warmHoleX;
				int tmpY = board[nY][nX].warmHoleY;
				nX = tmpX;
				nY = tmpY;
			}
			else if (board[nY][nX].type == -1)
			{
				//블랙홀에 들어감
				endType = BLACKHOLE;
				maxLength = cnt;
				break;
			}
		}

		x = nX;
		y = nY;

		if (x == startX && y == startY)
		{
			endType = CYCLE;
			break;
		}
	}

	int cX, cY, cDir, cValue;

	for (int i = 0; i < nodes.size(); i++)
	{
		cX = nodes[i].x;
		cY = nodes[i].y;
		cDir = nodes[i].dir;
		cValue = nodes[i].value;

		switch (endType)
		{
		case RAIL:
			railCache[cDir][cY][cX] = cnt - cValue;
			break;

		case CYCLE:
			cycleCache[cDir][cY][cX] = cnt;
			break;

		case BLACKHOLE:
			blackHoleCache[cDir][cY][cX] = cnt - cValue;
			break;
		}
	}


	return maxLength;
}



int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> N;

		for (int dir = 0; dir < 4; dir++)
		{
			for (int row = 0; row < N; row++)
			{
				for (int cul = 0; cul < N; cul++)
				{
					railCache[dir][row][cul] = -1;
					cycleCache[dir][row][cul] = -1;
					blackHoleCache[dir][row][cul] = -1;
				}
			}
		}

		for (int i = 0; i < 5; i++)
			warmHoleFlag[i] = false;

		int type;
		for (int row = 0; row < N; row++)
		{
			for (int cul = 0; cul < N; cul++)
			{
				cin >> type;
				board[row][cul].type = type;

				if (type >= 1 && type <= 5)
					board[row][cul].SetReflect();
				else if (type >= 6 && type <= 10)
					board[row][cul].SetWarmHole(cul, row, board);
			}
		}
		
		int ret = 0;
		int tmp = 0;
		for (int row = 0; row < N; row++)
		{
			for (int cul = 0; cul < N; cul++)
			{
				if (board[row][cul].type == 0)
				{
					for (int dir = 0; dir < 4; dir++)
					{
						tmp = Simulation(cul, row, dir);
						ret = max(tmp, ret);					
					}
				}
			}
		}		

		//int ret = Simulation(4, 0, 0);
		
		cout << "#" << testCase + 1 << " " << ret << endl;

	}

}
