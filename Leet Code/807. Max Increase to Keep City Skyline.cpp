#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
	int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
		int Height, Width;
		Height = grid.size();
		Width = grid[0].size();
		
		vector<int> verticalArr, horizontalArr;
		verticalArr.assign(Width, 0);
		horizontalArr.assign(Height, 0);

		int value = -1;
		for (int col = 0; col < Width; col++) {
			value = -1;
			for (int row = 0; row < Height; row++) {
				value = max(value, grid[row][col]);
			}
			verticalArr[col] = value;
		}

		for (int row = 0; row < Height; row++) {
			value = -1;

			for (int col = 0; col < Width; col++) {
				value = max(value, grid[row][col]);
			}
			horizontalArr[row] = value;
		}

		int ret = 0;

		for (int row = 0; row < Height; row++) {
			for (int col = 0; col < Width; col++) {
				ret += min(verticalArr[col], horizontalArr[row]) - grid[row][col];
			}
		}
		
		return ret;
	}
};


/*
4 4
3 0 8 4
2 4 5 7
9 2 6 3
0 3 1 0


output : 35
*/

int main(void) {
	int Height, Width;

	cin >> Height >> Width;

	vector<vector<int>> grid;
	grid.assign(Height, vector<int>(Width, 0));

	for (int row = 0; row < Height; row++) {
		for (int col = 0; col < Width; col++) {
			cin >> grid[row][col];
		}
	}

	Solution sol;
	cout << sol.maxIncreaseKeepingSkyline(grid) << endl;


}
