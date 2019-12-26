#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Point {
public:
	int x, y;

	Point(int x_, int y_) : x(x_), y(y_){}

	Point():Point(-1,-1){}
};

int N;
vector<Point> points;

//오른편에 있다면 양수, 왼편에 있다면 음수를 반환
double CrossProduct(Point &a, Point &b) {
	return double(a.x * b.y - a.y * b.x);
}

class SortedIndex {
public:
	int index;
	double degree;

	SortedIndex(int index_, double degree_) : index(index_), degree(degree_){}

	SortedIndex() : SortedIndex(-1,-1){}

	bool operator < (const SortedIndex& rhs) const {
		return degree < rhs.degree;
	}
};


vector<int> ret;

double GetDegree(Point &a, Point &b) {

	if (a.y == b.y) {
		if (b.x > a.x)
			return 100000000;
		else
			return -100000000;
	}
	else
		return (double(b.x) - double(a.x)) / (double(b.y) - double(a.y));
}

//ret에 외곽을 이루는 점들만 모은다
void ConvexHull() {
	//points 내에서 x,y 좌표가 제일 낮은 좌표(최 상단 좌측의)를 구한다.	
	int startIndex = 0;

	for (int i = 1; i < N; i++) {
		if (points[i].y < points[startIndex].y)
			startIndex = i;
		else if (points[i].y == points[startIndex].y) {
			if (points[i].x < points[startIndex].x)
				startIndex = i;
		}
	}

	//시계방향에 있는 순으로 index를 정렬한다.
	vector<SortedIndex> sortedIndex;
	sortedIndex.push_back(SortedIndex(startIndex, -999999999));
	double degree;
	for (int i = 1; i < N; i++) {
		degree = GetDegree(points[startIndex], points[i]);
		sortedIndex.push_back(SortedIndex(i, degree));
	}

	sort(sortedIndex.begin(), sortedIndex.end());

	//이제 index에 있는 값 순서로 접근하면 반시계 방향으로 접근 가능하다.


	//이제 ret에 값들을 형성해 나간다.
	ret.push_back(sortedIndex[0].index);
	ret.push_back(sortedIndex[1].index);

	int cIndex = 2;
	Point lineA, lineB;
	int first, second, other;
	double dir;
	while (1) {
		if (cIndex == N)
			break;

		//ret[ret.size() - 1] 에서 ret[ret.size() - 2] 로 향하는선을 긋는다.
		//ret[ret.size() - 1] 에서 sortedIndex[cIndex].index 로 향하는 선을 긋는다.
		while (1) {
			first = ret[ret.size() - 2];
			second = ret[ret.size() - 1];
			other = sortedIndex[cIndex].index;

			lineA.x = points[second].x - points[first].x;
			lineA.y = points[second].y - points[first].y;

			lineB.x = points[other].x - points[first].x;
			lineB.y = points[other].y - points[first].y;

			dir = CrossProduct(lineA, lineB);

			if (dir < 0) {
				//sortedIndex[cIndex].index의 점이 선의 왼편에 있다면(외적이 음수)
				ret.push_back(other);
				break;
			}
			else {
				//sortedIndex[cIndex].index의 점이 선의 오른편에 있다면(외적이 양수)
				//first에서 second로 그은 선의 왼편에 other이 존재할때까지 계속해서 ret를 pop_back 한다.
				ret.pop_back();
			}
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
