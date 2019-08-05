#include<iostream>
#include<algorithm>
#include<limits.h>

using namespace std;

char equation[25];
int N;

bool box[25];

long long BoxSolve(int &start)
{
	long long lhs = equation[start] - '0';
	long long rhs;
	char op;
	int i;

	for (i = start + 1; ; i += 2)
	{
		op = equation[i];
		rhs = equation[i + 1] - '0';


		switch (op)
		{
		case '+':
			lhs = lhs + rhs;
			break;

		case '-':
			lhs = lhs - rhs;
			break;

		case '*':
			lhs = lhs * rhs;
		}


		if (box[(i + 1) / 2] == true)
			break;
	}
	
	start = i + 1;

	return lhs;
}


long long Solve()
{
	long long lhs = 0, rhs;
	char op = '+';
	
	
	//박스 연산을 우선적으로 한다.
	for (int i = 0; i < N; i += 2)
	{
		if (box[i / 2] == true)
			rhs = BoxSolve(i);
		else
			rhs = equation[i] - '0';

		switch (op)
		{
		case '+':
			lhs = lhs + rhs;
			break;

		case '-':
			lhs = lhs - rhs;
			break;

		case '*':
			lhs = lhs * rhs;
		}
		
		if(i + 1 < N)
			op = equation[i + 1];
	}

	return lhs;
}

int numSize = 0;
int arr[20];
long long maxValue = LLONG_MIN + 10;
void Comb(int arrSize, int m, int n, int index)
{
	if (arrSize == n)
	{	

		//arrSize에 괄호를 씌울 좌표가 저장 되어 있다.
		for (int i = 0; i < numSize; i++)
		{
			box[i] = false;
		}

		for (int i = 0; i < n; i++)
		{
			box[arr[i]] = true;
			box[arr[i] + 1] = true;
		}

		long long value = Solve();
		maxValue = max(value, maxValue);
		
		
		return;
	}


	if (index == m)
		return;

	//괄호를 안 씌울 경우
	Comb(arrSize, m, n, index + 1);



	//arrSize번째로 괄호가 씌워질 위치는 index 이다.
	//arrSize = 0 위치는 괄호를 무조건 씌울 수 있다.
	//arrSize = 1 위치는 이전 좌표를 점검해야 씌울 수 있다.
	if (arrSize == 0)
	{
		arr[arrSize] = index;
		Comb(arrSize + 1, m, n, index + 1);
	}
	else
	{
		int prevIndex = arr[arrSize - 1];

		if (index - prevIndex > 1)
		{
			arr[arrSize] = index;
			Comb(arrSize + 1, m, n, index + 1);
		}
	}
}


int main(void)
{
	cin >> N;
	cin >> equation;
	
	numSize = N / 2 + 1;
	for (int i = 0; i <= numSize / 2; i++)
	{
		Comb(0, numSize - 1, i, 0);
	}

	cout << maxValue << endl;
	
	/*
	box[0] = true;
	box[2] = true;

	box[6] = true;
	box[8] = true;
	*/

	/*
	box[8] = true;
	box[9] = true;


	Solve();
	*/

	return 0;
}
