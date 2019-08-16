#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> fence;
int n;
vector<bool> flag;
//처음에는 최대 index를 전달한다.
int maxArea = -1;

/*
void FindMax(int x)
{
	int half = x/2;
	
	if(flag[half] == false)
	{
		int gap = 0;

		if(maxArea < fence[half])
			maxArea = fence[half];

		int height = fence[half];
		int width = 1;
		bool leftEnd =false;
		bool rightEnd = false;
		while(1)
		{
			gap++;

			if(leftEnd == false)
			{
				if(fence[half - gap] == 0)
					leftEnd == true;
			}
				
			if(leftEnd ==false)
			{
				width++;

				if(fence[half - gap] == height)
					flag[half - gap] = true;

				if(fence[half - gap] < height)
					height = fence[half - gap];

				int area = width * height;

				if(maxArea < area)
					maxArea = area;
			}

			if(rightEnd == false)
			{
				if(fence[half + gap] == 0)
					rightEnd == true;
			}				

			if(leftEnd ==false)
			{
				width++;

				if(fence[half + gap] == height)
					flag[half + gap] = true;

				if(fence[half + gap] < height)
					height = fence[half + gap];

				int area = width * height;

				if(maxArea < area)
					maxArea = area;
			}
		}
	}

	FindMax()
}
*/


int FindMax(int left, int right)
{
	//기저사례
	if(left == right)
		return fence[left];

	int half = (left + right) / 2;

	int ret = max(FindMax(left, half), FindMax(half + 1, right));

	int lo = half;
	int hi = half + 1;

	int height = min(fence[lo], fence[hi]);
	ret = max(ret, 2*height);

	while(left < lo || right > hi)
	{
		//더 높은곳을 우선적으로 탐험하도록 한다.
		if(hi < right && (lo == left || fence[lo - 1] < fence[hi + 1]))
		{
			hi++;
			height = min(height, fence[hi]);
		}
		else
		{
			lo--;
			height = min(height, fence[lo]);
			
		}
		ret = max(ret, (hi - lo + 1) * height);
	}
	return ret;
}


int main(void)
{
	//7
	//8 1 6 10 7 8 5
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> n;
		fence.assign(n, -1);
		flag.assign(n, false);
		int input;
		for (int i = 0; i < n; i++)
		{
			cin >> input;
			fence[i] = input;
		}

		int result = FindMax(0, n - 1);

		cout << result << endl;
	}
}
