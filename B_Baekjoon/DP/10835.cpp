#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>

using namespace std;

int N;
vector<int> leftCards;
vector<int> rightCards;

int cache[2005][2005];

int DFS(int leftIndex, int rightIndex, int score)
{
	if (leftIndex == N || rightIndex == N)
		return score;

	int tmp, ret = 0;

	if (cache[leftIndex][rightIndex] != -1)
		return cache[leftIndex][rightIndex] + score;

	//왼쪽을 버릴 경우
	tmp = DFS(leftIndex + 1, rightIndex, score);
	ret = max(ret, tmp);

	//둘 다 버릴경우
	tmp = DFS(leftIndex + 1, rightIndex + 1, score);
	ret = max(ret, tmp);


	//오른쪽을 버릴 경우
	if (leftCards[leftIndex] > rightCards[rightIndex])
	{
		tmp = DFS(leftIndex, rightIndex + 1, score + rightCards[rightIndex]);
		ret = max(ret, tmp);
	}

	cache[leftIndex][rightIndex] = ret - score;

	return ret;
}

int main(void)
{
	memset(cache, -1, sizeof(cache));

	cin >> N;
	int input;
	for (int i = 0; i < N; i++)
	{
		cin >> input;
		leftCards.push_back(input);
	}

	for (int i = 0; i < N; i++)
	{
		cin >> input;
		rightCards.push_back(input);
	}

	int value = DFS(0, 0, 0);
	cout << value << endl;

}
