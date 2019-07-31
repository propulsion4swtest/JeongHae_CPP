#include<iostream>
#include<vector>
#include<string.h>
#include<stdio.h>
#include<algorithm>
 
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
 
using namespace std;
 
 
class Cell
{
public:
    int x, y, size, dir;
    Cell(int x_, int y_, int size_, int dir_) : x(x_), y(y_), size(size_), dir(dir_)
    {   }
 
 
    bool operator < (const Cell &rhs) const
    {
        if (size == 0 || rhs.size == 0)
        {
            return size > rhs.size;
        }
        else
        {
            if (y != rhs.y)
                return y < rhs.y;
            else if (x != rhs.x)
                return x < rhs.x;
            else
                return size > rhs.size;
        }
    }
};
 
vector<Cell> cells;
 
int moveX[4] = { 0,0,-1,1 };
int moveY[4] = { -1,1,0,0 };
 
int N, M, K;
 
//한칸 이동시킨다.
void CellMove(Cell &cell)
{
    int nextX, nextY;
    nextX = cell.x + moveX[cell.dir];
    nextY = cell.y + moveY[cell.dir];
 
    if (nextX == 0 || nextX == N - 1 || nextY == 0 || nextY == N - 1)
    {
        switch (cell.dir)
        {
        case UP:
            cell.dir = DOWN;
            break;
 
        case DOWN:
            cell.dir = UP;
            break;
 
        case LEFT:
            cell.dir = RIGHT;
            break;
 
        case RIGHT:
            cell.dir = LEFT;
            break;
        }
 
        cell.size /= 2;
        if (cell.size == 0)
            return;
    }
 
     
    cell.x = nextX;
    cell.y = nextY;
}
 
 
 
//1초동안 시뮬레이션
void Simulation()
{   
    for (int i = 0 ; i < cells.size(); i++)
    {
        if(cells[i].size > 0)
            CellMove(cells[i]);
    }
 
    //같은 위치에 겹친 Cell들은 모두다 하나로 합친다.
 
    sort(cells.begin(), cells.end());
     
    int index;
    int cIndex = 0;
    for (index = 1; index < cells.size(); index++)
    {
        if (cells[index].size == 0)
            break;
 
        if (cells[cIndex].x != cells[index].x || cells[cIndex].y != cells[index].y)
        {
            cIndex = index;
        }
        else if (cells[cIndex].x == cells[index].x && cells[cIndex].y == cells[index].y)
        {
            cells[cIndex].size += cells[index].size;
            cells[index].size = 0;
        }
    }
 
     
    vector<Cell>::iterator it = cells.begin();
    cells.erase(it + index, cells.end());
     
}
 
 
 
void PrintBoard()
{
    int board[305][305] = { 0, };
 
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].size != 0)
        {
            int row, cul;
            cul = cells[i].x;
            row = cells[i].y;
 
            board[row][cul] = cells[i].size;
        }
    }
 
    cout << "\n\n";
    for (int row = 0; row < N; row++)
    {
        for (int cul = 0; cul < N; cul++)
        {
            if (board[row][cul] != 0)
            {
                printf("%5d", board[row][cul]);
            }
            else
            {
                printf("    .");
            }
        }
        cout << "\n";
    }
}
 
 
int GetCount()
{
    int cnt = 0;
    for (int i=0; i<cells.size(); i++)
    {
        cnt += cells[i].size;
    }
 
    return cnt;
}
 
 
int StartSimulation()
{
    //PrintBoard();
    for (int time = 0; time < M; time++)
    {
 
        Simulation();
 
        //PrintBoard();
    }
    int cnt = GetCount();
    return cnt;
}
 
 
int main(void)
{
    int T;
    cin >> T;
    int y, x, size, dir;
    for (int testCase = 0; testCase < T; testCase++)
    {
        cells.clear();
 
        cin >> N >> M >> K;
 
        for (int i = 0; i < K; i++)
        {
            cin >> y >> x >> size >> dir;
            dir--;
 
            cells.push_back(Cell(x, y, size, dir));
        }
 
        int cnt = StartSimulation();
 
        cout << "#" << testCase + 1 << " " << cnt << endl;
    }
 
     
 
    return 0;
}
