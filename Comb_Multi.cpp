#include<iostream>
#include<vector>

using namespace std;

/*
9C3 * 6C3 * 3C3 = 1680
*/

int arr[9] = { 0,1,2,3,4,5,6,7,8 };
bool flag[9] = { false, };

vector<int> vi;

//9C3 * 6C3 * 3C3
int cnt = 0;
void Comb(int arrSize)
{
	if (arrSize == 3)
	{
		for (int i = 0; i < 9; i++)
		{
			cout << vi[i] << " ";

			if (i % 3 == 2)
				cout << "      ";
		}
		cnt++;
		cout << endl;
	}

	for (int first = 0; first < 7; first++)
	{
		if (flag[first] == true)
			continue;

		flag[first] = true;
		vi.push_back(first);

		for (int second = first + 1; second < 8; second++)
		{
			if (flag[second] == true)
				continue;

			flag[second] = true;
			vi.push_back(second);

			for (int third = second + 1; third < 9; third++)
			{
				if (flag[third] == true)
					continue;

				flag[third] = true;
				vi.push_back(third);

				Comb(arrSize + 1);
				
				flag[third] = false;
				vi.pop_back();
			}
			flag[second] = false;
			vi.pop_back();
		}
		flag[first] = false;
		vi.pop_back();
	}
}


int main(void)
{
	Comb(0);

	cout << cnt << endl;

	return 0;
}
