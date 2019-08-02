#include<iostream>
#include<algorithm>

using namespace std;

int cmds[55][10];
int N;

//1개의 이닝의 시작과 끝을 시뮬한다.
//order번째 플레이어부터 게임을 시작한다.
int order;
int score;
bool seat[4] = { false, };
int arr[9];

//한번 전진시킨다.
void Run(int cnt)
{
	seat[0] = true;

	for (int j = 0; j < cnt; j++)
	{
		if (seat[3] == true)
			score++;

		for (int i = 3; i >= 1; i--)
		{			
			seat[i] = seat[i - 1];
		}

		seat[0] = false;
	}
}


void  SwapArr(int *arr, int a, int b)
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}


void PrintArr(int *arr)
{
	for (int i = 0; i < 9; i++)
		cout << arr[i] << " ";

	cout << endl;
}


void PlayGame(int inning)
{
	int out = 0;

	while (1)
	{
		int num = arr[order];
		int cmd = cmds[inning][num];

		switch (cmd)
		{
		case 1:
			Run(1);
			break;

		case 2:
			Run(2);
			break;

		case 3:
			Run(3);
			break;

		case 4:
			Run(4);
			break;

		case 0:
			out++;
			break;

		}

		if (out == 3)
			break;

		order++;
		if (order >= 9)
			order = 0;
	}
}

int maxScore = 0;

void StartGame()
{
	//PrintArr(arr);
	score = 0;
	order = 0;
	for (int i = 0; i < 4; i++)
		seat[i] = false;

	for (int inning = 0; inning < N; inning++)
	{
		PlayGame(inning);

		order++;
		if (order >= 9)
			order = 0;

		for (int i = 0; i < 4; i++)
			seat[i] = false;
	}

	maxScore = max(score, maxScore);
}




void Perm(int arrSize)
{
	if (arrSize == 8)
	{
		//PrintArr(arr);
		StartGame();

		return;
	}

	int a, b;
	for (int i = arrSize; i < 8; i++)
	{
		a = arrSize;
		b = i;

		if (a >= 3)
			a++;

		if (b >= 3)
			b++;

		SwapArr(arr, a, b);
		Perm(arrSize + 1);
		SwapArr(arr, a, b);
	}
}
 

int main(void)
{	
	for (int i = 0; i < 9; i++)
		arr[i] = i;

	SwapArr(arr, 0, 3);
	cin >> N;
	for (int inning = 0; inning < N; inning++)
		for (int num = 0; num < 9; num++)
			cin >> cmds[inning][num];	

	
	Perm(0);
	cout << maxScore << endl;
	

	/*
	arr[0] = 3;
	arr[1] = 1;
	arr[2] = 2;
	arr[3] = 0;
	arr[4] = 4;
	arr[5] = 5;
	arr[6] = 6;
	arr[7] = 8;
	arr[8] = 7;
	N = 2;
	
	//PlayGame();
	StartGame();
	*/


	/*
	seat[3] = false;
	seat[2] = true;
	seat[1] = false;

	Run(4);

	cout << endl;
	*/
	return 0;
}
