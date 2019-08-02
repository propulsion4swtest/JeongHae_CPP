/*
#include<iostream>
#include<algorithm>

using namespace std;

class Area
{
public:
	int begin, end;
	
	Area(int begin_, int end_) : begin(begin_), end(end_)
	{	}

	Area() : Area(-1, -1)
	{	}

};

int N, K;
//int cameras[10200];
int cameras[1020000];
int camera_size = 0;

bool flag[1020000] = { false, };

Area areas[1020];
int minValue = 1000000000;

//i번째 감지기의 begin을 설치하면서 i-1번째 감지기의 end를 설정한다.

//	K C 3, arrSize = 1, index = 1부터 시작시킨다.
int Comb(int arrSize, int m, int n, int index, int cnt)
{
	if (arrSize == n)
	{
		//마지막 감지기의 end는 마지막 카메라로 설정
		areas[arrSize - 1].end = cameras[camera_size - 1];

		cnt += (areas[arrSize - 1].end - areas[arrSize - 1].begin);
		minValue = min(minValue, cnt);
		return cnt;
	}

	if(minValue < cnt)
		return 1000000000;


	if (index == m)
		return 1000000000;
	
	int ret = 1000000000;
	
	//arr[arrSize] = index;
	//arrSize 번째의 감지기는 index번째의 카메라에 위치시킨다.
	//arrSize번째 감지기의 begin을 설치하면서 arrSize-1번째 감지기의 end를 설정한다.
	
	areas[arrSize].begin = cameras[index];
	areas[arrSize - 1].end = cameras[index - 1];

	int tmp =Comb(arrSize + 1, m, n, index + 1, cnt + (areas[arrSize - 1].end - areas[arrSize - 1].begin));
	ret = min(tmp, ret);
	
	tmp = Comb(arrSize, m, n, index + 1, cnt);
	ret = min(tmp, ret);

	return ret;
}


int Solve()
{
	//첫번째 감지기는 제일 왼쪽에 설치한다.
	areas[0].begin = cameras[0];

	int value = Comb(1, camera_size, K, 1, 0);
	return value;
}


int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		minValue = 1000000000;
		cin >> N >> K;	

		camera_size = 0;
		
		int input;
		for (int i = 0; i < N; i++)
		{
			cin >> input;
			if (flag[input] == false)
			{
				flag[input] = true;
				cameras[camera_size] = input;
				camera_size++;
			}
		}

		sort(&cameras[0], &cameras[camera_size]);

		int value;
		if (camera_size <= K)
			value = 0;
		else
			value = Solve();

		cout << "#" << testCase + 1 << " " << value << endl;

		for (int i = 0; i < camera_size; i++)
		{
			flag[cameras[i]] = false;
		}
	}
	return 0;
}
*/

#include<iostream>
#include<algorithm>

using namespace std;

int N, K;
//int cameras[10200];
int cameras[1020000];
int camera_size = 0;

int area[1020000];

bool flag[1020000] = { false, };


bool desc(const int &a, const int &b)
{
	return a > b;
}


int Solve()
{
	int value = 0;
	for (int i = K - 1; i < camera_size - 1; i++)
	{
		value += area[i];
	}

	return value;
}

int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> N >> K;

		camera_size = 0;

		int input;
		for (int i = 0; i < N; i++)
		{
			cin >> input;
			if (flag[input] == false)
			{
				flag[input] = true;
				cameras[camera_size] = input;
				camera_size++;
			}
		}

		sort(&cameras[0], &cameras[camera_size]);
		
		for (int i = 1; i < camera_size; i++)
			area[i - 1] = cameras[i] - cameras[i - 1];

		sort(&area[0], &area[camera_size - 1], desc);


		int value;
		if (camera_size <= K)
			value = 0;
		else
			value = Solve();

		cout << "#" << testCase + 1 << " " << value << endl;

		for (int i = 0; i < camera_size; i++)
		{
			flag[cameras[i]] = false;
		}
	}
	return 0;
}

