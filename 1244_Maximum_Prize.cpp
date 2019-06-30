
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#include<set>

using namespace std;

vector<vector<int>> order;
//order[a] : order[a][0] 과 order[a][1] 을 swap 한다
//a = length C 2
string numbers;
int N;


void Comb(vector<int> &arr, int arrSize, int m, int n, int index)
{
	if (arrSize == n)
	{
		order.push_back(vector<int>());
		order.back().push_back(arr[0]);
		order.back().push_back(arr[1]);
		return;
	}

	if (index == m)
		return;

	arr.push_back(index);
	Comb(arr, arrSize + 1, m, n, index + 1);
	arr.pop_back();
	Comb(arr, arrSize, m, n, index + 1);
}

void SwapArr(vector<int> &arr, int a, int b)
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

//order.size() P N

void PrintArr(vector<int> &arr, int size)
{
	cout << "\n\n";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}

int String2Int(string &str)
{
	int size = str.size();
	int value = 0;
	for (int i = 0; i < size; i++)
	{
		value *= 10;
		value += str[i] - '0';
	}
	return value;
}

//set<int> flag;
set<pair<int, int>> flag;
//count, num

int maxValue = -1;
void Perm(vector<int> &arr, int arrSize, int m, int n)
{
	if (arrSize == n)
	{
		//PrintArr(arr, n);
		int value = String2Int(numbers);
		//cout << value << endl << endl;

		if (value < 0)
			cout << endl;


		maxValue = max(maxValue, value);

		
		return;
	}

	for (int i = arrSize; i < m; i++)
	{
		SwapArr(arr, i, arrSize);

		int index = arr[arrSize];
		int a = order[index][0];
		int b = order[index][1];

		char tmp = numbers[a];
		numbers[a] = numbers[b];
		numbers[b] = tmp;

		int value = String2Int(numbers);

		set<pair<int,int>>::iterator it;
		it = flag.find(pair<int,int>(arrSize,value));

		if (it != flag.end())
		{
			tmp = numbers[a];
			numbers[a] = numbers[b];
			numbers[b] = tmp;
			continue;
		}
		else
		{
			flag.insert(pair<int, int>(arrSize, value));
		}

		Perm(arr, arrSize + 1, m, n);

		tmp = numbers[a];
		numbers[a] = numbers[b];
		numbers[b] = tmp;

		SwapArr(arr, i, arrSize);
	}

}


int main(void)
{

	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		flag.clear();
		order.clear();
		maxValue = -1;
		cin >> numbers;
		cin >> N;

		vector<int> arr;
		Comb(arr, 0, numbers.size(), 2, 0);

		arr.assign(order.size(), 0);
		for (int i = 0; i < order.size(); i++)
		{
			arr[i] = i;
		}

		Perm(arr, 0, arr.size(), N);

		cout << "#" << testCase + 1 << " " << maxValue << endl;
	}

}
