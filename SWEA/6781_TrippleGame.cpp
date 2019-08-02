
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>

#define R 0
#define G 1
#define B 2

using namespace std;

vector<int> hands;
vector<int> numbers;
vector<int> colors;
int handsCnt = 0;

char str[15];


int arr[9] = { 0,1,2,3,4,5,6,7,8 };
bool flag[9] = { false, };


bool CheckCanSet(int a, int b, int c)
{
	a = hands[a];
	b = hands[b];
	c = hands[c];

	//a,b,c순으로 오르막 정렬 되어있다.
	//3개의 카드가 다 같은 경우
	if (a == b && b == c)
		return true;

	//a,b,c 순으로 1씩 증가 할 경우
	if (a + 1 == b && b + 1 == c)
		return true;

	return false;
}

bool canClear = false;
//9C3 * 6C3 * 3C3
void CombMulti(int arrSize)
{
	if (canClear == true)
		return;

	if (arrSize == 3)
	{
		canClear = true;
	}

	for (int first = 0; first < 7; first++)
	{
		if (flag[first] == true)
			continue;

		flag[first] = true;

		for (int second = first + 1; second < 8; second++)
		{
			if (flag[second] == true)
				continue;

			flag[second] = true;

			for (int third = second + 1; third < 9; third++)
			{
				if (flag[third] == true)
					continue;

				flag[third] = true;

				bool result = CheckCanSet(first, second, third);

				if(result == true)
					CombMulti(arrSize + 1);

				flag[third] = false;
			}
			flag[second] = false;
		}
		flag[first] = false;
	}
}

int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		hands.clear();
		numbers.clear();
		colors.clear();
		canClear = false;

		cin >> str;

		for (int i = 0; i < 9; i++)
			numbers.push_back(str[i] - '0');

		cin >> str;

		for (int i = 0; i < 9; i++)
		{
			int color;
			switch (str[i])
			{
			case 'R':
				color = R;
				break;

			case 'G':
				color = G;
				break;

			case 'B':
				color = B;
				break;
			}

			colors.push_back(color);
		}

		for (int i = 0; i < 9; i++)
		{
			int hand = 10 * colors[i] + numbers[i];		
			hands.push_back(hand);
		}
				
		sort(hands.begin(), hands.end());
		
		CombMulti(0);
		if (canClear == true)
			cout << "#" << testCase + 1 << " Win" << endl;
		else
			cout << "#" << testCase + 1 << " Continue" << endl;		
	}



	return 0;
}
