#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Coord
{
public:
	int x,y;

	Coord(int x_, int y_) : x(x_) , y(y_)
	{}

	Coord()
	{
		x = -1;
		y = -1;
	}	

	bool operator < (const Coord &rhs)
	{
		if(y != rhs.y)
			return y < rhs.y;
		else
			return x < rhs.x;

	}

};

vector<vector<Coord>> orgBlock;


//x,y 좌표가 제일 낮은 블록이 0,0으로 오도록 평행이동 시켜야 한다.
void SlideBlock(vector<vector<Coord>> &block)
{
	int minX = 9999;
	int minY = 9999;

	int size = block[0].size();

	for(int dir = 0; dir < 4; dir++)
	{		
		sort(block[dir].begin(), block[dir].end());

		int moveX = block[dir][0].x;
		int moveY = block[dir][0].y;

		for(int num = 0; num < size; num++)
		{
			block[dir][num].x -= moveX;
			block[dir][num].y -= moveY;		
		}
	}
}


void SetBlock(vector<vector<Coord>> &block, vector<Coord> &orgCoords)
{
	int size = orgCoords.size();

	block.assign(4, vector<Coord>(size, Coord()));

	int x,y;
	for(int dir = 0; dir<4; dir++)
	{
		for(int num = 0; num < size; num++)
		{
			switch(dir)
			{
			case 0:
				x = orgCoords[num].x;
				y = orgCoords[num].y;
				break;

			case 1:
				x = -orgCoords[num].y;
				y = orgCoords[num].x;
				break;

			case 2:
				x = orgCoords[num].y;
				y = -orgCoords[num].x;
				break;

			case 3:
				x = -orgCoords[num].x;
				y = -orgCoords[num].y;
				break;
			}
			block[dir][num].x = x;
			block[dir][num].y = y;
		}	
	}

	SlideBlock(block);
}

int Width, Height;


//x,y는 반드시 범위내의 값이어야 한다
bool GetNext(vector<vector<bool>> &block, int x, int y, int &nextX, int &nextY)
{
	while(1)
	{
		if(block[y][x] == false)
		{
			nextX = x;
			nextY = y;
			return true;
		}

		if(y >= Height)
		{			
			nextX = -1;
			nextY = -1;

			return false;
		}

		x++;

		if(x >= Width)
		{
			x = 0;
			y++;
		}

	}
}

int left_count = 0;
int score = 0;

vector<vector<bool>> orgBoard;


bool CanPut(vector<vector<bool>> &board, int x, int y, int dir)
{
	int currentX, currentY;

	int numSize = orgBlock[0].size();

	for(int num=0; num<numSize; num++)
	{
		currentX = x + orgBlock[dir][num].x;
		currentY = y + orgBlock[dir][num].y;

		if(currentX < 0 || currentX >= Width || currentY < 0 || currentY >= Height)
			return false;

		if(board[currentY][currentX] == true)
			return false;

	}

	return true;

}


void SetBoard(vector<vector<bool>> &board, int x, int y, int dir)
{
	int numSize = orgBlock[0].size();
	int currentX, currentY;

	for(int num=0; num<numSize; num++)
	{
		currentX = x + orgBlock[dir][num].x;
		currentY = y + orgBlock[dir][num].y;

		board[currentY][currentX] = !board[currentY][currentX];
	}

}


int RPerm(int x, int y)
{
	if(left_count == 0)
	{
		score++;	
		return 1;
	}

	if(GetNext(orgBoard,x,y,x,y) == false)
	{
		return 0;
	}

	int ret = 0;

	for(int dir = 0; dir < 4; dir++)
	{
		if(CanPut(orgBoard, x, y, dir) == false)
			continue;
		
		SetBoard(orgBoard, x, y, dir);
		left_count -= 3;

		ret += RPerm(x,y);

		SetBoard(orgBoard, x, y, dir);
		left_count += 3;
	}
	
	return ret;
}


int main(void)
{
	
	vector<Coord> coord;
	coord.push_back(Coord(0,0));
	coord.push_back(Coord(1,0));
	coord.push_back(Coord(0,1));
	
	SetBlock(orgBlock, coord);

	cin >> Height>>Width;
	orgBoard.assign(Height, vector<bool>(Width,false));
	left_count = Height * Width;
	int input;
	for(int row = 0; row< Height; row++)
	{
		for(int cul = 0; cul< Width; cul++)
		{
			cin >> input;

			if(input)
			{
				orgBoard[row][cul] = true;
				left_count--;
			}
		}
	}

	int result = RPerm(0,0);
	
	//cout << result << endl;
	cout << result << endl;

	return 0;
}
