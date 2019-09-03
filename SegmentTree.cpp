#include<iostream>

using namespace std;


class SegmentTree
{
public:
	SegmentTree *pLeft;
	SegmentTree *pRight;

	int from, to;
	int value;

	SegmentTree()
	{
		pLeft = 0;
		pRight = 0;
		value = -1;
		from = -1;
		to = -1;
	}

	void Init(int *arr, int left, int right)
	{
		from = left;
		to = right;

		if (left == right)
		{
			value = arr[from];
		}
		else
		{
			int mid = left + (right - left) / 2;

			pLeft = new SegmentTree;
			pRight = new SegmentTree;

			pLeft->Init(arr, left, mid);
			pRight->Init(arr, mid + 1, right);

			value = pLeft->value + pRight->value;
		}
	}

	int GetValue(int left, int right)
	{
		if (left <= from && to <= right)
			return value;
		else if (to < left || from > right)
			return 0;
		else
		{
			return pLeft->GetValue(left, right) + pRight->GetValue(left, right);
		}
	}

	void Clear()
	{
		if (pLeft != 0)
			if (pLeft->from != pLeft->to)
				pLeft->Clear();

		if (pRight != 0)
			if (pRight->from != pRight->to)
				pRight->Clear();

		delete pLeft;
		delete pRight;
	}

	//구간내의 배열에 특정값을 더할경우
	int PlusValue(int left, int right, int changer)
	{
		if (to < left || from > right)
			return 0;
		else if (from == to)
		{
			value += changer;
			return changer;
		}
		else
		{
			int a = pLeft->PlusValue(left,right,changer);
			int b = pRight->PlusValue(left, right, changer);
			value += a + b;
			return a + b;
		}
	}

	//index의 값을 value로 바꾼다
	int SetValue(int index, int number)
	{
		if (index < from || to < index)
		{	
			return value;
		}
		else if(from == index && to == index)
		{
			value = number;
			return value;
		}
		else
		{
			int a = pLeft->SetValue(index, number);
			int b = pRight->SetValue(index, number);
			value = a + b;
			return value;
		}

	}


};



int main(void)
{
	int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };
	SegmentTree trees;
	trees.Init(arr, 0, 9);

	
	cout << trees.GetValue(0, 9) << endl;
	cout << trees.GetValue(3, 7) << endl;

	trees.PlusValue(3, 7, 2);

	for (int i = 0; i < 10; i++)
		cout << trees.GetValue(i, i) << " ";

	cout << endl;

	cout << trees.GetValue(3, 7) << endl;
	cout << trees.GetValue(0, 9) << endl;
	cout << trees.GetValue(2, 4) << endl;
	

	trees.SetValue(4, 30);

	for (int i = 0; i < 10; i++)
		cout << trees.GetValue(i, i) << " ";
	
	cout << endl;
	cout << trees.GetValue(3, 7) << endl;
	cout << trees.GetValue(0, 9) << endl;
	cout << trees.GetValue(2, 4) << endl;

	trees.Clear();
}
