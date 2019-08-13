#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

bool isEnd = false;

class Circle
{
public:
	double x,y,r;

	Circle(double x_, double y_, double r_) : x(x_), y(y_), r(r_)
	{	}


	Circle()
	{	
		x = -1;
		y = -1;
		r = -1;
	}
};

vector<Circle> circles;
int m;
double R;

bool IsIntersect(Circle &circleA, Circle &circleB)
{
	double distance = sqrt(pow(circleB.x - circleA.x, 2) + pow(circleB.y - circleA.y, 2));
	
	double lhs = 2 * R;
	double rhs = distance + circleA.r + circleB.r;

	if(lhs < rhs)
		return false;	//안겹친다
	else
		return true;	//겹친다.
}


void Comb(vector<int> &arr, int arrSize, int m, int n, int index)
{
	if(isEnd)
		return;

	if(arrSize == n)
	{
		//circles[arr[0]]과 circles[arr[1]]에 있는 원2개의 area를 비교한다.
		if(IsIntersect(circles[arr[0]], circles[arr[1]]))
		{
			//cout << "intersect"<<endl;
		}
		else
		{
			//cout << "null" << endl;
			isEnd = true;
		}

		return;
	}

	if(index == m)
		return;

	arr[arrSize] = index;	
	Comb(arr,arrSize + 1, m, n, index+1);
	Comb(arr,arrSize, m, n, index+1);
}





int main(void)
{
	cin >> m >> R;

	double x,y,r;
	for(int i=0; i<m; i++)
	{
		cin >> x>>y>>r;

		circles.push_back(Circle(x,y,r));
	}
	
	vector<int> arr;
	arr.assign(2,0);
	Comb(arr,0,m,2,0);

	if(isEnd)
		cout << "fail" << endl;
	else
		cout << "success" << endl;

	return 0;
}
