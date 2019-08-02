#include<iostream>
#include<list>
#include<stdio.h>

#define UP		0
#define DOWN	1
#define LEFT	2
#define RIGHT	3

#define LENGTH 2001

#define DEATH 0
#define ALIVE 1
#define SLEEP 2

using namespace std;


class Atom
{
public:
	int x, y, dir, k;
	int state;
	int index;
	Atom(int x_, int y_, int dir_, int k_) : x(x_), y(y_), dir(dir_), k(k_)
	{
		state = ALIVE;
	}

	Atom() : Atom(-1, -1, -1, -1)
	{	}

};

//Atom atoms[1200];
list<Atom> atoms;
int N;

int moveX[4] = { 0,0,-1,1 };
int moveY[4] = { 1,-1,0,0 };

Atom *prevBoard[2200][2200] = { NULL, };
Atom *nextBoard[2200][2200] = { NULL, };


int GetOppoDir(int dir)
{
	switch (dir)
	{
	case UP:
		return DOWN;
		break;

	case DOWN:
		return UP;
		break;

	case LEFT:
		return RIGHT;
		break;

	case RIGHT:
		return LEFT;
		break;
	}
}

//1초 동안 일어나는 일을 시뮬레이션 한다.
int score;

void Simulation()
{
	int prevX, prevY;
	int nextX, nextY;
	for (list<Atom>::iterator it = atoms.begin(); it != atoms.end(); it++)
	{
		prevX = it->x;
		prevY = it->y;

		prevBoard[prevY][prevX] = &(*it);

		it->x += moveX[it->dir];
		it->y += moveY[it->dir];
	}
	//이 시점에서 atoms의 x,y 좌표는 이동 후 좌표이다.

	for (list<Atom>::iterator it = atoms.begin(); it != atoms.end(); it++)
	{
		if (it->state == DEATH || it->state == SLEEP)
			continue;

		//0.5초 점검
		nextX = it->x;
		nextY = it->y;

		if (nextX < 0 || nextX > LENGTH || nextY <0 || nextY > LENGTH)
		{
			it->state = SLEEP;
			continue;
		}

		Atom *crashWith = prevBoard[nextY][nextX];
		if (crashWith != NULL)
		{
			int oppoDir = GetOppoDir(it->dir);
			if (crashWith->dir == oppoDir)//서로 마주보고 있으면
			{
				it->state = DEATH;
				crashWith->state = DEATH;

				continue;
			}
		}

		//1초 후 점검
		crashWith = nextBoard[nextY][nextX];
		if (crashWith != NULL)	//다른 atom이 이동후 좌표에 있다면 자신과 상대를 죽인다.
		{
			it->state = DEATH;
			crashWith->state = DEATH;
		}
		else	//다른 atom이 없으면 자기자신을 afterBoard의 해당 위치에 배치시킨다
		{
			nextBoard[nextY][nextX] = &(*it);
		}

	}
}

void StartSimulation()
{
	while (!atoms.empty())
	{
		Simulation();

		int prevX, prevY;
		for (list<Atom>::iterator it = atoms.begin(); it != atoms.end();)
		{
			prevX = it->x - moveX[it->dir];
			prevY = it->y - moveY[it->dir];

			prevBoard[prevY][prevX] = NULL;
			nextBoard[it->y][it->x] = NULL;

			if (it->state == DEATH)
			{
				score += it->k;
				it = atoms.erase(it);
			}
			else if (it->state == SLEEP)
			{
				it = atoms.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}


int main(void)
{
	int T;
	cin >> T;
	int x, y, dir, k;
	for (int testCase = 0; testCase < T; testCase++)
	{
		score = 0;
		cin >> N;

		for (int i = 0; i < N; i++)
		{
			cin >> x >> y >> dir >> k;
			x += 1000;
			y += 1000;
			atoms.push_back(Atom(x, y, dir, k));
			atoms.back().index = i;
		}

		StartSimulation();

		cout << "#" << testCase + 1 << " " << score << endl;
	}

	return 0;
}
