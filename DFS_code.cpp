#include<iostream>
#include <vector>
#include<stack>

using namespace std;

void PrintArr(int *arr, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
}


void SwapArr(int *arr, int a, int b)
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}


//조합
void Comb(int *arr, int arrSize, int m, int n, int index)
{
	if (arrSize == n)
	{
		PrintArr(arr, n);
		return;
	}

	if (index == m)
		return;

	arr[arrSize] = index;
	Comb(arr, arrSize + 1, m, n, index + 1);
	Comb(arr, arrSize, m, n, index + 1);
}


//중복조합
void RComb(int *arr, int arrSize, int m, int n, int index)
{
	if (arrSize == n)
	{
		PrintArr(arr, arrSize);
		return;
	}
	else if (index == m)
	{
		return;
	}

	arr[arrSize] = index;
	RComb(arr, arrSize + 1, m, n, index);
	RComb(arr, arrSize, m, n, index + 1);
}


//순열
void Perm(int *arr, int arrSize, int m, int n)
{
	if (arrSize == n)
	{
		PrintArr(arr, n);
		return;
	}

	for (int i = arrSize; i < m; i++)
	{
		SwapArr(arr, i, arrSize);
		Perm(arr, arrSize + 1, m, n);
		SwapArr(arr, i, arrSize);
	}
}


//중복순열
void RPerm(int *arr, int arrSize, int m, int n)
{
	if (arrSize == n)
	{
		PrintArr(arr, n);
		return;
	}

	for (int i = 0; i < m; i++)
	{
		arr[arrSize] = i;
		RPerm(arr, arrSize + 1, m, n);
	}
}


int main(void)
{
	int m, n;

	int *arr, *set;
	vector<int> vi;

	scanf("%d %d", &m, &n);

	vi.assign(m, 0);

	printf("\n\n\n");

	arr = new int[m];
	set = new int[m];

	for (int i = 0; i < m; i++)
	{
		arr[i] = i;
	}

	printf("Comb\n");
	Comb(set, 0, m, n, 0);	
	printf("\n\n\n");	

	printf("RComb\n");
	RComb(set, 0, m, n, 0);
	printf("\n\n\n");

	printf("Perm\n");
	Perm(arr, 0, m, n);
	printf("\n\n\n");	

	printf("RPerm\n");
	RPerm(arr, 0, m, n);
}


/*
input
=======
4 2


output
========
Comb
0 1
0 2
0 3
1 2
1 3
2 3


RComb
0 0
0 1
0 2
0 3
1 1
1 2
1 3
2 2
2 3
3 3


Perm
0 1
0 2
0 3
1 0
1 2
1 3
2 1
2 0
2 3
3 1
3 2
3 0


RPerm
0 0
0 1
0 2
0 3
1 0
1 1
1 2
1 3
2 0
2 1
2 2
2 3
3 0
3 1
3 2
3 3
*/
