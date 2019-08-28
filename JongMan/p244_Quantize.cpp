#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>

using namespace std;

int N, S;
vector<int> numbers;
int pSum[105];
int pSqSum[105];

void Awake()
{
	pSum[0] = numbers[0];
	pSqSum[0] = numbers[0] * numbers[0];

	for (int i = 1; i < N; i++)
	{
		pSum[i] = pSum[i - 1] + numbers[i];
		pSqSum[i] = pSqSum[i - 1] + (numbers[i] * numbers[i]);
	}
}

//index번째 묶음이 arrSize부터 어디까지 뻗어나갈지를 순회한다.

/*
vector<int> vi;
int DFS(int arrSize, int index)
{
	if (arrSize == N)
		return 0;

	if (index == S - 1) {
		for (int i = 0; i < S - 1; i++) {
			cout << vi[i] << " ";
		}
		cout << endl;

		return 0;
	}	

	for (int i = arrSize + 1; i < N; i++)
	{
		vi.push_back(i);
		DFS(i, index + 1);
		vi.pop_back();
	}
}
*/

/*
int GetDiffSqr(int start, int end)
{
	int sum = 0;
	for (int i = start; i <= end; i++)
		sum += numbers[i];
	
	int avg = (int)(0.5f + ((float)sum / (float)(end - start + 1)));	//0.5를 더해서 반올림을 해준다.

	sum = 0;
	int diff;
	for (int i = start; i <= end; i++) {
		diff = numbers[i] - avg;
		diff *= diff;
		sum += diff;
	}

	return sum;
}
*/

int GetDiffSqr(int start, int end)
{
	int sum, sqSum;
	if (start == 0)
	{
		sum = pSum[end];
		sqSum = pSqSum[end];
	}
	else
	{
		sum = pSum[end] - pSum[start - 1];
		sqSum = pSqSum[end] - pSqSum[start - 1];
	}

	int avg = (int)(0.5f + ((float)sum / (float)(end - start + 1)));	//0.5를 더해서 반올림을 해준다.

	int ret = sqSum - 2 * avg * sum + (end - start + 1) * avg * avg;
	return ret;
}


int cache[15][105];	//cache[index][aarrSize] : index번째 덩어리의 arrSize번째 수에서의 최소 크기
int DFS(int arrSize, int index)
{
	if (arrSize == N)
		return 0;

	if (index == S)		
		return 900000000;
	

	if (cache[index][arrSize] != -1)
		return cache[index][arrSize];

	int avg;
	int tmp, ret = 900000000;
	for (int i = arrSize; i < N; i++)
	{
		//arrSize ~ i 의 수가 index 번째 올가미의 범위가 된다.
		avg = GetDiffSqr(arrSize, i);

		tmp = DFS(i + 1, index + 1);
		ret = min(ret, tmp + avg);
	}

	cache[index][arrSize] = ret;
	return ret;
}
					
					
/*
int DFS(int arrSize, int index)
{
	if (arrSize == N)
		return 900000000;

	if (index == S - 1) {
		int ret;
		ret = GetDiffSqr(arrSize, N - 1);
		return ret;
	}
	
	if (cache[index][arrSize] != -1)
		return cache[index][arrSize];

	int avg;
	int tmp, ret = 900000000;
	for (int i = arrSize; i < N; i++)
	{		
		//arrSize ~ i 의 수가 index 번째 올가미의 범위가 된다.
		avg = GetDiffSqr(arrSize, i);		
		
		tmp = DFS(i + 1, index + 1);
		ret = min(ret, tmp + avg);
	}
	
	cache[index][arrSize] = ret;
	return ret;
}
*/

int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		numbers.clear();
		memset(cache, -1, sizeof(cache));

		cin >> N >> S;
		int input;
		for (int i = 0; i < N; i++)
		{
			cin >> input;
			numbers.push_back(input);
		}

		sort(numbers.begin(), numbers.end());
		Awake();
		
		int value = DFS(0, 0);
		cout << value << endl;
	}


	return 0;
}
