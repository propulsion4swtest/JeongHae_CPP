#include<iostream>
#include<list>
#include<string.h>
#include<stdio.h>
 
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
};
 
list<Cell> cells;
Cell *board[105][105];
int afterBoard[105][105];
 
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
 
    afterBoard[cell.y][cell.x] += cell.size;
 
    if (board[cell.y][cell.x] != 0)
    {
        Cell &otherCell = *board[cell.y][cell.x];
 
        if (otherCell.size > cell.size)
        {
            cell.size = 0;
        }
        else if (otherCell.size < cell.size)
        {
            otherCell.size = 0;
            board[cell.y][cell.x] = &cell;
        }
    }
    else
    {
        board[cell.y][cell.x] = &cell;
    }
}
 
 
 
//1초동안 시뮬레이션
void Simulation()
{   
    for (list<Cell>::iterator it = cells.begin(); it != cells.end(); it++)
    {
        CellMove(*it);
    }
 
    for (list<Cell>::iterator it = cells.begin(); it != cells.end(); )
    {
        if (it->size == 0)
        {
            it = cells.erase(it);
        }
        else
        {
            int x, y;
            x = it->x;
            y = it->y;
 
            it->size = afterBoard[y][x];
            board[y][x] = &*it;
            it++;
        }       
    }
}
 
 
void PrintBoard()
{
    cout << "\n\n";
    for (int row = 0; row < N; row++)
    {
        for (int cul = 0; cul < N; cul++)
        {
            if (board[row][cul] != 0)
            {
                printf("%5d", board[row][cul]->size);
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
    for (list<Cell>::iterator it = cells.begin(); it != cells.end(); it++)
    {
        cnt += it->size;
    }
 
    return cnt;
}
 
 
int StartSimulation()
{
    //PrintBoard();
    for (int time = 0; time < M; time++)
    {
        memset(board, 0, sizeof(board));
        memset(afterBoard, 0, sizeof(afterBoard));
 
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
        memset(board, 0, sizeof(board));
        memset(afterBoard, 0, sizeof(afterBoard));
 
        cin >> N >> M >> K;
 
        for (int i = 0; i < K; i++)
        {
            cin >> y >> x >> size >> dir;
            dir--;
 
            cells.push_back(Cell(x, y, size, dir));
            board[y][x] = &cells.back();
        }
 
        int cnt = StartSimulation();
 
        cout << "#" << testCase + 1 << " " << cnt << endl;
    }
 
     
 
    return 0;
}
