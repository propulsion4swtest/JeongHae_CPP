#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Point {
public:
	int x, y;

	Point(int x_, int y_) : x(x_), y(y_) {}

	Point() :Point(-1, -1) {}

	bool operator < (const Point& rhs) const {
		if (y != rhs.y)
			return y < rhs.y;
		else
			return x < rhs.x;
	}
};

int N;
vector<Point> points;

class SortedNode {
public:
	int index;
	double degree;

	SortedNode(int index_, double degree_) : index(index_), degree(degree_) {}

	SortedNode() : SortedNode(-1,-1) {}

	bool operator < (const SortedNode& rhs) const {
		return degree < rhs.degree;
	}

};

vector<SortedNode> sortedIndex;

//b가 a의 왼편에 있으면 -, 오른편에 있으면 +
int CrossProduct(Point& a, Point& b) {
	return (a.x * b.y) - (a.y * b.x);
}

double GetDegree(Point& a, Point& b) {
	if (b.y - a.y == 0) {
		if (b.x > a.x)
			return 100000000;
		else
			return -100000000;
	}
	else
		return double(b.x - a.x) / double(b.y - a.y);
}

vector<int> ret;

void ConvexHull() {
	sort(points.begin(), points.end());

	//제일 왼쪽 위에 있는 points[0]을 기준으로 모든 점들이 반시계 방향이 되도록 정렬한다.
	sortedIndex.push_back(SortedNode(0, -2000000000));
	double degree;
	for (int i = 1; i < N; i++) {
		degree = GetDegree(points[0], points[i]);
		sortedIndex.push_back(SortedNode(i, degree));
	}

	sort(sortedIndex.begin(), sortedIndex.end());

	ret.push_back(sortedIndex[0].index);
	ret.push_back(sortedIndex[1].index);

	int first, second, other;                                                                     
	int cIndex = 2;
	Point lineA, lineB;
	double dir;
	while (cIndex < N) {
		other = sortedIndex[cIndex].index;

		while (1) {
			//lineA : first -> second
			//lineB : first -> other
			//lineB가 lineA의 왼편에 올때까지 반복
			first = ret[ret.size() - 2];
			second = ret[ret.size() - 1];
			
			lineA.x = points[second].x - points[first].x;
			lineA.y = points[second].y - points[first].y;

			lineB.x = points[other].x - points[second].x;
			lineB.y = points[other].y - points[second].y;

			dir = CrossProduct(lineA, lineB);

			if (dir < 0) {
				ret.push_back(other);
				break;
			}
			else
				ret.pop_back();
		}
		cIndex++;
	}

}


int main(void) {
	cin >> N;
	int x, y;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		points.push_back(Point(x, y));
	}

	//CrossProduct(points[0], points[1]);
	//CrossProduct(points[0], points[2]);



	ConvexHull();

	return 0;
}


/*
17
4 1
7 1
2 2
7 2
10 2
5 3
8 3
1 4
3 4
9 4
10 4
8 5
5 6
7 6
3 7
9 7
6 8
*/
