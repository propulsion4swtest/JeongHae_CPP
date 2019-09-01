#include<iostream>
//#include<stdio.h>
#include<string.h>

using namespace std;

int N, D, P;
int O, Q[55];
bool paths[55][55];
double town[55];	//각 마을에서 다른 마을로 갈 확률
//double totalProb[50];	//최종적으로 각 마을에 도착할 확률
double cache[105][55][55];
bool flag[105][55];

void DFS(int arrSize, int cPosition, double prob, double ret[])
{
	if (arrSize == D)
	{
		ret[cPosition] += prob;
		return;
	}	

	if (flag[arrSize][cPosition] == true)
	{
		//cout << "zzz" << endl;
		for (int i = 0; i < N; i++)
		{
			if (cache[arrSize][cPosition][i] >= 0)
				ret[i] += ((cache[arrSize][cPosition][i]) * prob);
		}
	}
	else
	{
		for (int nPosition = 0; nPosition < N; nPosition++)
		{
			double tmpRet[55] = { 0, };
			if (paths[cPosition][nPosition] == true)
			{
				DFS(arrSize + 1, nPosition, prob * town[cPosition], tmpRet);

				for (int i = 0; i < N; i++)
				{
					cache[arrSize][cPosition][i] += (tmpRet[i] / prob);
					ret[i] += tmpRet[i];
				}
			}
		}

		flag[arrSize][cPosition] = true;
	}
}

int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		memset(cache, 0, sizeof(cache));
		memset(flag, false, sizeof(flag));
		memset(town, 0, sizeof(town));
		cin >> N >> D >> P;
		//scanf("%d %d %d", &N, &D, &P);

		for (int row = 0; row < N; row++)
		{
			for (int cul = 0; cul < N; cul++) 
			{
				//scanf("%d", &paths[row][cul]);
				cin >> paths[row][cul];
			}
		}

		for (int from = 0; from < N; from++)
		{
			int cnt = 0;
			for (int to = 0; to < N; to++)
			{
				if (paths[from][to] == true)
					cnt++;

				town[from] = 1.0 / cnt;
			}
		}

		//scanf("%d", &O);
		cin >> O;
		for (int i = 0; i < O; i++)
		{
			cin >> Q[i];
			//scanf("%d", &Q[i]);
		}

		double ret[55] = { 0, };
		DFS(0, P, 1, ret);


		for (int i = 0; i < O; i++)
		{
			cout << fixed;
			cout.precision(8);
			cout << ret[Q[i]] << " ";
		}
		cout << endl;
	}
}

/*
1
10 5 4
0 1 1 0 1 0 1 0 1 1
1 0 1 1 1 1 0 1 0 1
1 1 0 1 0 1 1 0 1 1
0 1 1 0 1 1 1 0 1 0
1 1 0 1 0 1 0 1 1 1
0 1 1 1 1 0 1 0 1 0
1 0 1 1 0 1 0 1 1 1
0 1 0 0 1 0 1 0 1 1
1 0 1 1 1 1 1 1 0 1
1 1 1 0 1 0 1 1 1 0
4
0 1 2 3

*/
