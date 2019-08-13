#include<iostream>
#include<vector>

using namespace std;


bool IsLIS(vector<int> &arr)
{
	int size = arr.size();

	for(int i=0; i<size - 1; i++)
	{
		if(arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

vector<int> vi;

void PrintArr(vector<int> &arr)
{
	cout<<"\n\n";

	for(int i=0; i<arr.size(); i++)
	{
		cout << arr[i] <<" ";
	}

	cout<<"\n\n";
}

bool isFind = false;
int answer = 1;
void Comb(vector<int> &arr, int arrSize, int m, int n, int index)
{
	if(isFind == true)
		return;

	if(arrSize == n)
	{
		//arr[0] ~ arr[n-1] 의 index에 있는 값을 제외한 나머지 값이 저장된 vector를 만든다.
		vector<int> tmp;
		//int exceptIndex = 0;
		vector<int>::iterator it = arr.begin();
		for(int i = 0; i<vi.size() ; i++)
		{
			if(it != arr.end())
				if(i == *it)
					it++;
				else
					tmp.push_back(vi[i]);		
			else
				tmp.push_back(vi[i]);
		}

		//PrintArr(tmp);
		if(IsLIS(tmp))
		{
			answer = m - n;
			isFind = true;
		}

		return;
	}

	if(index == m)
		return;

	arr[arrSize] = index;

	Comb(arr, arrSize + 1, m, n, index+1);
	Comb(arr, arrSize, m, n, index+1);
}


/*
5
1 3 4 2 4
*/

int main(void)
{
	int M;
	cin >> M;

	int input;
	for(int i=0; i<M; i++)
	{
		cin >> input;
		vi.push_back(input);
	}

	vector<int> arr;
	for(int i=0; i < M; i++)
	{
		arr.assign(i,-1);
		Comb(arr,0,M,i,0);
		if(isFind == true)
		{
			cout<<answer<<endl;
			break;
		}
	}


	/*
	int N = 2;
	vector<int> arr;
	arr.assign(N, -1);

	Comb(arr,0,M,N,0);
	*/

	return 0;
}
