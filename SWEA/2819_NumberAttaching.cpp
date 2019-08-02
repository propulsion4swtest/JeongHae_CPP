
#include<iostream>
#include<vector>
#include<set>

using namespace std;

class Key
{
public:
	int value, x, y, length;

	Key(int value_, int x_, int y_, int length_) : value(value_), x(x_), y(y_), length(length_)
	{	}

	Key() : Key(-1, -1, -1, -1)
	{	}

	bool operator < (const Key &rhs) const
	{
		if (value != rhs.value)
			return value < rhs.value;
		else if (length != rhs.length)
			return length < rhs.length;
		else if (x != rhs.x)
			return x < rhs.x;
		else
			return y < rhs.y;
	}
};



set<Key> cache;
set<int> flag;

int board[4][4];

int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };

int number = 0;



int DFS(int arrSize, int x, int y)
{
	number = number * 10 + board[y][x];	
	
	if (arrSize == 6)
	{
		set<int>::iterator it = flag.find(number);
		if (it == flag.end())
		{
			flag.insert(number);
			number /= 10;
			return 1;
		}
		else
		{
			number /= 10;
			return 0;
		}
	}

	set<Key>::iterator it = cache.find(Key(number, x, y, arrSize));

	
	if (it != cache.end())
	{
		number /= 10;
		return 0;
	}
	

	cache.insert(Key(number, x, y, arrSize));

	int ret = 0;
	
	int nextX, nextY;
	for (int dir = 0; dir < 4; dir++)
	{
		nextX = x + moveX[dir];
		nextY = y + moveY[dir];

		if (nextX < 0 || nextX >= 4 || nextY < 0 || nextY >= 4)
			continue;

		ret += DFS(arrSize + 1, nextX, nextY);
	}

	number /= 10;

	return ret;
}



int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		

		for (int row = 0; row < 4; row++)
		{
			for (int cul = 0; cul < 4; cul++)
			{
				cin >> board[row][cul];
			}
		}

		cache.clear();
		flag.clear();

		int ret = 0;

		for (int row = 0; row < 4; row++)
		{
			for (int cul = 0; cul < 4; cul++)
			{
				number = 0;
				ret += DFS(0, cul, row);
			}
		}

		cout << "#" << testCase + 1 << " " << ret << endl;
	}


}



/*
#include<iostream>
#include<vector>

using namespace std;


bool cache[10000000][4][4][7];
bool flag[10000000];

int board[4][4];

int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };

int number = 0;



int DFS(int arrSize, int x, int y)
{
	number = number * 10 + board[y][x];

	if (arrSize == 6)
	{		
		if (flag[number] == false)
		{
			flag[number] = true;
			number /= 10;
			return 1;
		}
		else
		{
			number /= 10;
			return 0;
		}

	}

	if (cache[number][x][y][arrSize] == true)
	{
		number /= 10;
		return 0;
	}

	cache[number][x][y][arrSize] = true;

	int ret = 0;

	int nextX, nextY;
	for (int dir = 0; dir < 4; dir++)
	{
		nextX = x + moveX[dir];
		nextY = y + moveY[dir];

		if (nextX < 0 || nextX >= 4 || nextY < 0 || nextY >= 4)
			continue;

		ret += DFS(arrSize + 1, nextX, nextY);
	}

	number /= 10;

	return ret;
}



int main(void)
{
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		for (int num = 0; num < 10000000; num++)
		{
			for (int row = 0; row < 4; row++)
			{
				for (int cul = 0; cul < 4; cul++)
				{
					for (int length = 0; length < 7; length++)
					{
						cache[num][row][cul][length] = false;
					}
				}
			}
			flag[num] = false;
		}


		for (int row = 0; row < 4; row++)
		{
			for (int cul = 0; cul < 4; cul++)
			{
				cin >> board[row][cul];
			}
		}		
		

		int ret = 0;

		for (int row = 0; row < 4; row++)
		{
			for (int cul = 0; cul < 4; cul++)
			{
				number = 0;
				ret += DFS(0, cul, row);
			}
		}

		cout << "#" << testCase + 1 << " " << ret << endl;
	}


}
*/
