#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N;
vector<int> numbers;

vector<int> cache;

int DFS(int arrSize, int length, int prevNum)
{
	if (arrSize == N)
		return length;


	//arrSize 번째 numbers 값을 LIS에 추가시킨다.
	int tmp1 = 0, tmp2 = 0;
	
	if (numbers[arrSize] > prevNum)
	{
		if (cache[arrSize] == -1)
			tmp1 = DFS(arrSize + 1, length + 1, numbers[arrSize]);
		else
			tmp1 = cache[arrSize] + length;
	}

	tmp2 = DFS(arrSize + 1, length, prevNum);
	int tmp = max(tmp1, tmp2);

	if (numbers[arrSize] > prevNum)
		cache[arrSize] = max(cache[arrSize], tmp - length);

	return tmp;
}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		numbers.clear();
		cin >> N;
		cache.assign(N, -1);
		int input;
		for (int i = 0; i < N; i++)
		{
			cin >> input;
			numbers.push_back(input);
		}
	
		int value = DFS(0, 0, -1);
		cout << value << endl;
	}	

	return 0;
}
