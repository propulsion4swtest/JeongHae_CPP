#include<iostream>
#include<string.h>
#include<algorithm>

using namespace std;

int DFS(int arrSize, int bitMask, int cnt, int season);

int N, K, M, L;
int R[15], Rs[15];	//i번 수업의 선수과목
int Q[15], Qs[15];	//i번 학기에 열리는 수업

int cache[1 << 15][15];

//2 PI N
int RPerm(int arrSize,  int bitMask, int orgMask, int cnt, int arrSize_, int bitMask_, int cnt_, int season_)
{
	if (arrSize == N)
	{		
		/*
		for (int i = N - 1; i >= 0; i--)
		{
			if ((bitMask & (1 << i)) != 0)
				cout << "1 ";
			else
				cout << "0 ";

		}
		cout << endl;
	
		return 0;
		*/
	
		//bitMask에서 수업 들을 내용을 bitMask_에 옮긴다.
		bitMask_ |= bitMask;

		int value = DFS(arrSize_ + 1, bitMask_, cnt_ + cnt, season_ + 1);
		return value;
	}

	int tmp, ret = 2000000000;

	//arrSize번째 수업을 들을 경우
	if ((orgMask & (1 << arrSize)) != 0 && cnt < L)
	{
		tmp = RPerm(arrSize + 1, bitMask | (1 << arrSize), orgMask, cnt + 1, arrSize_, bitMask_, cnt_, season_);
		ret = min(tmp, ret);
	}

	//arrSize번째 수업을 안들을 경우
	tmp = RPerm(arrSize + 1, bitMask, orgMask, cnt, arrSize_, bitMask_, cnt_, season_);
	ret = min(tmp, ret);

	return ret;
}


int DFS(int arrSize, int bitMask, int cnt, int season)
{
	if (cnt >= K)
		return season;

	if (arrSize >= M)
		return 2000000000;

	
	if (cache[bitMask][arrSize] != -1)
		return cache[bitMask][arrSize] + season;
	

	int tmp = ~bitMask;
	tmp &= Qs[arrSize];		//이번학기에 열린 과목중 아직 안들은 수업 목록
	int canStudy = 0;		//이번 학기에 들을 수 있는 수업 목록

	for (int i = 0; i < N; i++)
	{
		if ((tmp & (1 << i)) != 0)	//i번 수업을 아직 안들었다면
		{
			if ((bitMask & Rs[i]) == Rs[i])
			{
				canStudy |= (1 << i);
			}
		}
	}

	
	int value, ret = 2000000000;

	//하나도 안들을 경우
	value = DFS(arrSize + 1, bitMask, cnt, season);
	ret = min(value, ret);
	

	value = RPerm(0, 0, canStudy, 0, arrSize, bitMask, cnt, season);
	ret = min(value, ret);

	cache[bitMask][arrSize] = ret - season;


	return ret;
}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		memset(cache, -1, sizeof(cache));
		cin >> N >> K >> M >> L;
		int input;
		for (int i = 0; i < N; i++)
		{
			cin >> R[i];
			Rs[i] = 0;
			for (int j = 0; j < R[i]; j++)
			{
				cin >> input;
				Rs[i] |= (1 << input);
			}
		}


		for (int i = 0; i < M; i++)
		{
			cin >> Q[i];
			Qs[i] = 0;

			for (int j = 0; j < Q[i]; j++)
			{
				cin >> input;
				Qs[i] |= (1 << input);
			}
		}

		int value = DFS(0, 0, 0, 0);
		if (value < 1900000000)
			cout << value << endl;
		else
			cout << "IMPOSSIBLE" << endl;

		//RPerm(0, 0, 0b001110, 0);
	}

	return 0;
}


/*
1
6 6 7 1
0
1 0
2 0 1
3 0 1 2
4 0 1 2 3
5 0 1 2 3 4

0
6 0 1 2 3 4 5
6 0 1 2 3 4 5
6 0 1 2 3 4 5
6 0 1 2 3 4 5
6 0 1 2 3 4 5
6 0 1 2 3 4 5

*/
