
#include<iostream>
#include<algorithm>

using namespace std;



bool path[10][10];

//방향성을 주기 위해 2차 배열을 사용하였다.
int cache[10][10];
int startCache[10][10];


bool flag[10];

int N, M;

/*
int DFS2(int node, int length)
{

	flag[node] = true;

	int ret = 0;

	for (int i = 0; i < N; i++)
	{
		if (path[node][i] == true && flag[i] == false)
		{
			int tmp = DFS2(i, length + 1);
			ret = max(ret, tmp);
		}
	}

	if (ret == 0)
		ret = length;

	
	flag[node] = false;
	ret = max(ret, length);
	return ret;
}

*/

//0~N 번의 시작점을 일일이 호출해주어야한다.
//더이상 갈곳이 없다 : length 반환
//이동할 곳이 있다 : 이동할 경로중 최대 이동거리 반환
int DFS(int node, int prevNode, int length)
{
	if (prevNode != -1)
	{
		if (length <= startCache[prevNode][node])
		{
			return length + cache[prevNode][node];
		}

		startCache[prevNode][node] = length;
	}


	flag[node] = true;

	int ret = 0;

	for (int i = 0; i < N; i++)
	{
		if (path[node][i] == true && flag[i] == false)
		{
			int tmp = DFS(i, node,length + 1);
			ret = max(ret, tmp);
		}
	}

	if (ret == 0)
		ret = length;

	//더이상 갈곳이 없으면 지금까지 이동한 값을 반환한다.
	if(prevNode != -1)
		cache[prevNode][node] = ret - length;
	flag[node] = false;
	ret = max(ret, length);
	return ret;
}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> N >> M;


		for (int row = 0; row < N; row++)
		{
			for (int cul = 0; cul < N; cul++)
			{
				path[row][cul] = false;
			}
		}

		int a, b;
		for (int i = 0; i < M; i++)
		{
			cin >> a >> b;
			path[a - 1][b - 1] = true;
			path[b - 1][a - 1] = true;
		}

		int ret = 0;

		for (int i = 0; i < N; i++)
		{
			for (int row = 0; row < N; row++)
			{
				for (int cul = 0; cul < N; cul++)
				{
					startCache[row][cul] = -1;
					cache[row][cul] = -1;
				}

				flag[row] = false;
			}

			int tmp = DFS(i, -1 ,0);
			ret = max(ret, tmp);
		}

		cout << "#" << testCase + 1 << " " << ret + 1 << "     " << endl;
	}

	return 0;
}



/*
1
10 12
1 2
2 3
3 4
4 1
1 5
5 6
6 7
7 1
1 8
8 9
9 10
10 1
*/
