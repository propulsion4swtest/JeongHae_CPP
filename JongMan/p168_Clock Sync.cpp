#include<iostream>
#include<vector>


using namespace std;


int n, m;
vector<vector<int>> sync;	//sync[i][j] : i번째 스위치에 연결된 시계
vector<int> clocks;
int minValue = 99999999;
int score = 0;
vector<int> command;

bool CheckSuccess()
{
	for(int i = 0; i<m; i++)
	{
		if(clocks[i] != 0)
			return false;

	}

	return true;
}

//num 버튼을 count번 누른다
void PushButton(int num, int count)
{
	int size = sync[num].size();

	for(int i=0; i<size; i++)
	{
		int clockNumber = sync[num][i];
		clocks[clockNumber] += count;
		clocks[clockNumber] %= 4;
	}
}


void RPerm(int arrSize)
{
	//모든 시계가 12를 가리킬 경우
	if(CheckSuccess() == true)
	{
		if(minValue > score)
			minValue = score;

		int size = command.size();

		for(int i=0;i<size; i++)
		{
			cout<<command[i]<<" ";
		}

		cout<<endl;

		return;
	}

	//해당 case 완전종료
	if(arrSize == n)
	{	
		return;
	}


	for(int i=0; i<4; i++)
	{		
		//arr[arrSize] = i;
		//arrSize번째 스위치를 i번 누른다.
		PushButton(arrSize, i);
		
		if(i>0)		//단순히 1을 더하고 빼는게 아닌 누른횟수인 i를 연산해주어야한다
			score += i;
		
		if(i != 0)
			for(int j = 0; j<i; j++)
				command.push_back(arrSize);

		RPerm(arrSize+1);

		PushButton(arrSize, 4-i);

		if(i>0)
			score -= i;

		if(i != 0)
			for(int j = 0; j<i; j++)
				command.pop_back();
	}

}



int main(void)
{
	cin>>n;
	sync.assign(n,vector<int>());

	int input;
	for(int i=0; i<n; i++)
	{
		while(1)
		{
			cin >> input;

			if(input == -1)
				break;

			sync[i].push_back(input);		
		}
	}

	cin>>m;	
	clocks.assign(m,0);
	for(int i=0; i<m; i++)
	{
		cin>>input;
		clocks[i] = input;
	}
	
	RPerm(0);
	//PushButton(8,2);

	cout << minValue <<endl;

	return 0;
}
