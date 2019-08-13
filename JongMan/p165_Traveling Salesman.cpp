#include<iostream>
#include<vector>

using namespace std;


vector<vector<int>> dist;
int n;
vector<bool> flag;
int moveCount = 0;
int length = 0;
int minScore = 99999999;
vector<int> path;

void RPerm(int position)
{
	//모든행선지를 다 방문했으면(n - 1번 이동했으면)
	if(moveCount == n - 1)
	{
		length += dist[position][0];

		if(minScore > length)
			minScore = length;

		length -= dist[position][0];

		for(int i = 0; i<n; i++)
		{
			cout<<path[i]<<" ";
		}

		cout<<endl;

		return;
	}



	for(int i=0; i<n; i++)
	{
		//arr[arrSize] = i;
		//arrSize 번째 행선지는 i가 된다.
		//flag를 조사해서 i가 이미 이동한 곳인지 점검한다.
		//이동거리를 더하고 재귀호출이 끝나면 다시뺀다, flag도 수정한다.
		if(flag[i] == true)
			continue;

		flag[i] = true;	
		length += dist[position][i];
		moveCount++;
		path.push_back(i);

		RPerm(i);
		
		flag[i] = false;
		length -= dist[position][i];
		moveCount--;
		path.pop_back();
	}

}


int main(void)
{
	cin >> n;
	dist.assign(n,vector<int>(n, -1));
	flag.assign(n,false);

	for(int row = 0; row < n; row++)
	{
		for(int cul = 0; cul<n; cul++)
		{
			if(row != cul)
			{
				dist[row][cul] = (2*row + 3*cul) % 8;
				dist[cul][row] = dist[row][cul];
			}		
		}
	}
	
	flag[0]=true;
	path.push_back(0);
	RPerm(0);

	cout<<minScore<<endl;

	return 0;
}
