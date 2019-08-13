#include<iostream>
#include<vector>

using namespace std;

class Coord{
public:
	int x,y;

	Coord(int x_, int y_) : x(x_), y(y_)
	{	}


	Coord() : x(-1) , y(-1)
	{	}

};


class Block
{
public :
	vector<vector<Coord>> coords;
	//coords[dir][i] : dir만큼 돌렷을때 i번째 블럭의 좌표	

	void Start(vector<Coord> &org_coord)
	{
		/*
		org_coord.push_back(Coord(0,0));
		org_coord.push_back(Coord(1,0));
		org_coord.push_back(Coord(0,1));
		*/

		int orgSize = org_coord.size();
		coords.assign(4, vector<Coord>(orgSize, Coord()));

		int x,y;
		for(int num = 0; num < orgSize; num++)
		{
			for(int dir = 0 ; dir< 4; dir++)
			{
				switch(dir)
				{
				case 0:
					x = org_coord[num].x;
					y = org_coord[num].y;					
					break;

				case 1:
					x = org_coord[num].y;
					y = -org_coord[num].x;	
					break;			

				case 2:
					x = -org_coord[num].y;
					y = org_coord[num].x;	
					break;

				case 3:
					x = -org_coord[num].x;
					y = -org_coord[num].y;		
					break;
				}	

				coords[dir][num].x = x;
				coords[dir][num].y = y;
			}
		}
	}

};


Block block;
int Height, Width;
vector<vector<bool>> orgBoard;
int left_count = 0;
bool FindNext(vector<vector<bool>> board, int x, int y, int &nextX, int &nextY)
{
	while(1)
	{
		if(x >= Width)
		{
			x = 0;
			y++;

			if(y >= Height)
			{
				nextX = -1;
				nextY = -1;
				return false;
			}
		}

		if(board[y][x] == false)
		{
			nextX = x;
			nextY = y;
			return true;
		}
		x++;		
	}
	
}


//x,y 좌표에 dir만큼 회전시킨 block을 놓을 수 있는가?
bool CanPut(vector<vector<bool>> &board, int x, int y, int dir)
{
	for(int i=0; i<block.coords[0].size(); i++)
	{
		int currentX = x + block.coords[dir][i].x;
		int currentY = y + block.coords[dir][i].y;

		//범위를 벗어나는가
		if(currentX < 0 || currentX >= Width || currentY < 0 || currentY >= Height)
			return false;		

		//이미 다른 블록이 있는가
		if(board[currentY][currentX] == true)
			return false;

	}

	return true;
}


//4방향으로 놓는다 + 놓지 않는다의 5가지 방법으로 중복순열을 나열해간다
int RPerm(int x, int y)
{
	
	//cout << "x : " << x << "    y : "<< y <<endl;
	if(left_count == 0)
	{		
		return 1;
	}

	if(FindNext(orgBoard,x,y,x,y) == false)
		return 0;

	int ret = 0;

	for(int dir=0; dir < 4; dir++)
	{
		//arr[arrSize] = i;
		//RPerm(arr,arrSize + 1, m ,n);

		if(CanPut(orgBoard, x,y,dir) == false)
			continue;

		int block_size = block.coords[0].size();
		int nextX, nextY;
		for(int i=0; i<block_size; i++)
		{
			nextX = x + block.coords[dir][i].x;
			nextY = y + block.coords[dir][i].y;
			orgBoard[nextY][nextX] = true;
		}
		left_count -= 3;

		ret += RPerm(x,y);

		for(int i=0; i<block_size; i++)
		{
			nextX = x + block.coords[dir][i].x;
			nextY = y + block.coords[dir][i].y;

			orgBoard[nextY][nextX] = false;
		}
		left_count += 3;
	}

	ret += RPerm(x + 1, y);

	return ret;
}

int main(void)
{
	vector<Coord> coords;
	coords.push_back(Coord(0,0));
	coords.push_back(Coord(1,0));
	coords.push_back(Coord(0,1));

	block.Start(coords);

	cin >> Height >> Width;
	left_count = Height * Width;
	orgBoard.assign(Height, vector<bool>(Width,false));
	int input;
	for(int row = 0; row< Height; row++)
	{
		for(int cul=0; cul<Width; cul++)
		{
			cin >> input;

			if(input)
			{
				orgBoard[row][cul] = true;
				left_count--;
			}
		}
	}

	/*
	int nextX, nextY;
	FindNext(orgBoard,3,3,nextX,nextY);
	*/

	int score = RPerm(0,0);
	//CanPut(orgBoard,5,0,0);

	cout<< score <<endl;

	return 0;
}
