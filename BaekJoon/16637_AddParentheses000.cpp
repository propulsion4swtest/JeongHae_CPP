#include<iostream>
#include<algorithm>

using namespace std;

char equation[30];
int N;

long long boxSize;

bool boxes[15];

long long Calc(long long lhs, long long rhs, char op)
{
	switch (op)
	{
	case '+':
		return lhs + rhs;

	case '-':
		return lhs - rhs;

	case '*':
		return lhs * rhs;

	case '/':
		return lhs / rhs;
	}
}


long long Solve()
{
	char op;
	long long lhs;
	long long rhs;
	op = '+';
	lhs = 0;
	for (long long i = 0; i < N; i += 2)
	{
		if (boxes[i / 2] == true)
		{
			long long tmpLhs = equation[i] - '0';
			long long tmpRhs = equation[i + 2] - '0';
			long long tmpOp = equation[i + 1];

			rhs = Calc(tmpLhs, tmpRhs, tmpOp);

			i += 2;
		}
		else
		{
			rhs = equation[i] - '0';
		}


		lhs = Calc(lhs, rhs, op);
		
		if (i + 1 < N)
			op = equation[i + 1];
	}	

	return lhs;
}

long long maxValue = -2000000000;
void RPerm(int arrSize)
{
	if (arrSize == boxSize)
	{
		long long value = Solve();
		maxValue = max(maxValue, value);

		return;
	}

	//괄호 추가 안할 경우
	RPerm(arrSize + 1);

	//괄호 추가 할 경우
	if (arrSize == 0)
	{
		boxes[arrSize] = true;
		RPerm(arrSize + 1);
		boxes[arrSize] = false;
	}
	else
	{
		if (boxes[arrSize - 1] == false)
		{
			boxes[arrSize] = true;
			RPerm(arrSize + 1);
			boxes[arrSize] = false;
		}
	}
}



int main(void)
{
	cin >> N;
	cin >> equation;

	boxSize = N / 2;

	RPerm(0);
	cout << maxValue << endl;

	/*
	boxes[0] = 1;
	boxes[3] = 1;

	int value = Solve();
	cout << value << endl;
	*/

	return 0;
}
