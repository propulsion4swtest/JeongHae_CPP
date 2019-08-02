#include<iostream>
#include<string.h>
#include<queue>

using namespace std;

int N, M, R, C, L;
int board[55][55];

int pipeType[8] = { 0b0000, 0b1111, 0b1010, 0b0101, 0b1001, 0b0011, 0b0110, 0b1100 };

class Node
{
public:
	int x, y, cnt;

	Node(int x_, int y_, int cnt_) : x(x_), y(y_), cnt(cnt_)
	{	}
};

bool flag[55][55];

int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };

int cnt = 0;

void BFS()
{
	queue<Node> qu;

	//flag에 칠하는 순간에 cnt++를 해준다.
	flag[R][C] = true;
	cnt++;

	if (L > 1)
	{
		qu.push(Node(C, R, 1));
	}
	int revDir;
	while (!qu.empty())
	{
		Node cNode = qu.front();
		qu.pop();

		int nextX, nextY;
		for (int dir = 0; dir < 4; dir++)
		{
			nextX = cNode.x + moveX[dir];
			nextY = cNode.y + moveY[dir];

			if (nextX < 0 || nextX >= M || nextY < 0 || nextY >= N)
				continue;

			if (flag[nextY][nextX] == true)
				continue;

			revDir = (dir + 2) % 4;

			//파이프를 통해 이동 가능한가?
			int outPipe = board[cNode.y][cNode.x];
			int inPipe = board[nextY][nextX];

			int canOut = pipeType[outPipe] & (1 << dir);
			int canIn = pipeType[inPipe] & (1 << revDir);

			if (canOut != 0 && canIn != 0)
			{
				flag[nextY][nextX] = true;
				cnt++;

				if (cNode.cnt < L - 1)
					qu.push(Node(nextX, nextY, cNode.cnt + 1));
			}
		}
	}
}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		memset(flag, false, sizeof(flag));
		cnt = 0;

		cin >> N >> M >> R >> C >> L;
		for (int row = 0; row < N; row++)
		{
			for (int cul = 0; cul < M; cul++)
			{
				cin >> board[row][cul];
			}
		}

		BFS();
		cout << "#" << testCase + 1 << " " << cnt << endl;

		
	}

	return 0;
}
