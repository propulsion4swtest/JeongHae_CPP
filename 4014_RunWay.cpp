#include<iostream>
#include<vector>

using namespace std;

int board[25][25];
int N, X;

bool CheckCanPath(vector<int> &path)
{
	bool flag[25] = { false, };
	int cNum;
	int nNum;
	for (int i = 0; i < N - 1; i++)
	{
		cNum = path[i];
		nNum = path[i + 1];

		if (cNum != nNum)
		{
			if (cNum + 1 == nNum)	//1만큼 오르락일경우
			{
				//cNum 부터 왼쪽으로 x만큼 높이가 같아야 한다.
				for (int j = 0; j < X; j++)
				{
					if (i - j < 0)
						return false;

					if (path[i] != path[i - j])
						return false;

					if (flag[i - j] == true)
						return false;

					flag[i - j] = true;
				}

			}
			else if (cNum - 1 == nNum)	//1만큼 내리락일 경우
			{
				//nNum 부터 오른쪽으로 x만큼 높이가 같아야 한다.
				for (int j = 0; j < X; j++)
				{
					if (i + 1 + j >= N)
						return false;

					if (path[i + 1] != path[i + 1 + j])
						return false;

					if (flag[i + 1 + j] == true)
						return false;

					flag[i + 1 + j] = true;
				}
			}
			else	//2이상 높이차가 날 경우
				return false;
		}
	}

	return true;
}


int Solve()
{
	bool result;
	vector<int> path;
	int cnt = 0;
	//열 방향으로 우선 점검한다
	for (int row = 0; row < N; row++)
	{
		path.clear();

		for (int cul = 0; cul < N; cul++)
		{
			path.push_back(board[row][cul]);
		}
		result = CheckCanPath(path);
	
		if (result == true)
			cnt++;
	}

	for (int cul = 0; cul < N; cul++)
	{
		path.clear();

		for (int row = 0; row < N; row++)
		{
			path.push_back(board[row][cul]);
		}
		result = CheckCanPath(path);

		if (result == true)
			cnt++;
	}

	return cnt;
}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> N >> X;

		for (int row = 0; row < N; row++)
		{
			for (int cul = 0; cul < N; cul++)
			{
				cin >> board[row][cul];
			}
		}

		int value = Solve();

		cout << "#" << testCase + 1 << " " << value << endl;

		/*
		vector<int> path;
		path.push_back(2);
		path.push_back(3);
		path.push_back(3);
		path.push_back(3);
		path.push_back(3);
		path.push_back(3);

		bool result = CheckCanPath(path);
		*/
	}



	return 0;
}
