#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;

bool synergy[110][110];
map<string, int> maps;

int K;
int N;

//DFS(0, -1, false, false)
bool isClear = false;
/*
void DFS(int index, int leftNum, int rightNum, bool isLeft, bool isRight)
{
	if (isClear == true)
		return;

	if (isLeft && isRight)
	{
		isClear = true;
		return;
	}

	if (index == N)
	{
		return;
	}

	//왼쪽팀에 playerNum을 소속시킨다.
	if (isLeft == false)
	{
		if (isRight != false)
		{
			if(synergy[index][rightNum] == false)
				DFS(index + 1, index, rightNum, true, isRight);
		}
		else
		{
			DFS(index + 1, index, rightNum, true, isRight);
		}
	}

	//오른쪽팀에 playerNum을 소속시킨다.
	if (isRight == false)
	{
		if (isLeft != false)
		{
			if (synergy[leftNum][index] == false)
				DFS(index + 1, leftNum, index, isLeft, true);
		}
		else
		{
			DFS(index + 1, leftNum, index, isLeft, true);
		}
	}

	//소속 안시킨다
	DFS(index + 1, leftNum, rightNum, isLeft, isRight);
}
*/

vector<int> leftTeam;
vector<int> rightTeam;

bool IsSynergy(vector<int> &team, int player)
{
	for (int i = 0; i < team.size(); i++)
	{
		if (synergy[team[i]][player] == true)
			return false;
	}

	return true;
}

void DFS(int index)
{
	if (isClear == true)
		return;

	if (index == N)
	{
		isClear = true;
		return;
	}

	//index번 선수를 left팀에 추가한다.
	if (IsSynergy(leftTeam, index))
	{
		leftTeam.push_back(index);
		DFS(index + 1);
		leftTeam.pop_back();
	}


	if (IsSynergy(rightTeam, index))
	{
		rightTeam.push_back(index);
		DFS(index + 1);
		rightTeam.pop_back();
	}

}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		isClear = false;

		maps.clear();
		for (int i = 0; i < 110; i++)
		{
			for (int j = 0; j < 110; j++)
			{
				synergy[i][j] = false;
			}
		}

		cin >> K;

		string a, b;
		int index = 0;
		int lhs, rhs;
		for (int i = 0; i < K; i++)
		{
			cin >> a >> b;

			if (maps.find(a) == maps.end())
			{
				maps[a] = index;
				lhs = index;
				index++;
			}
			else
				lhs = maps[a];


			if (maps.find(b) == maps.end())
			{
				maps[b] = index;
				rhs = index;
				index++;
			}
			else
				rhs = maps[b];

			synergy[lhs][rhs] = true;
			synergy[rhs][lhs] = true;
		}

		N = maps.size();

		//DFS(0, -1, -1, false, false);
		DFS(0);

		if (isClear == true)
			cout << "#" << testCase + 1 << " " << "Yes" << endl;
		else
			cout << "#" << testCase + 1 << " " << "No" << endl;

	}


}
