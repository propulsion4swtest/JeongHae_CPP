#include<iostream>
#include<vector>

using namespace std;

vector<int> Normalize(vector<vector<int>> &num)
{
	int index = 0;
	vector<int> result;

	for(int row = 0; row < num[0].size(); row++)
	{
		int sum=0;	
		
		int x,y;
		x = row;
		y = 0;
		while(1)
		{
			sum += num[y][x];

			x--;
			y++;

			if(x <0 || y >= num.size())
				break;
		}
		result.push_back(sum);
	}

	for(int cul = 1; cul < num.size(); cul++)
	{
		int sum=0;

		int x,y;
		x = num[0].size() - 1;
		y = cul;

		while(1)
		{
			sum += num[y][x];

			x--;
			y++;

			if(x < 0 || y >= num.size())
				break;
		}
		result.push_back(sum);
	}

	for(int i = 0; i< result.size() - 1; i++)
	{		
		result[i + 1] += result[i] / 10;
		result[i] %= 10;	
	
	}

	if(result[result.size()-1] >= 10)
	{
		int over = result[result.size() - 1] / 10;
		result[result.size() -1] %= 10;
		result.push_back(over);
	}

	return result;
}


vector<int> Time(vector<int> &lhs, vector<int> &rhs)
{
	vector<vector<int>> result;
	result.assign(rhs.size(), vector<int>(lhs.size(),0));	

	for(int i=0; i<rhs.size(); i++)
		for(int j=0; j<lhs.size(); j++)
			result[i][j] = lhs[j] * rhs[i];	

	vector<int> normal;
	normal = Normalize(result);

	return normal;
}

int main(void)
{
	vector<int> result;

	vector<int> lhs;
	lhs.push_back(4);
	lhs.push_back(3);
	lhs.push_back(2);
	lhs.push_back(1);

	vector<int> rhs;
	rhs.push_back(8);
	rhs.push_back(7);
	rhs.push_back(6);
	rhs.push_back(5);

	result = Time(lhs, rhs);

	return 0;
}
