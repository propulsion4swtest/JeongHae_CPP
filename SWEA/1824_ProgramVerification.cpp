#include<iostream>
 
#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
 
using namespace std;
 
int R, C;
char board[20][20];
bool cache[20][20][16][4];
//cache[y][x][score][dir] : score와 dir 정보로 x,y를 지난적이 있는가?(나갈때 기준)
 
int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };
 
bool isEnd = false;
 
void PrintGame(int x, int y, int dir, int score)
{
    cout << "\n\n";
 
    for (int row = 0; row < R; row++)
    {
        for (int cul = 0; cul < C; cul++)
        {
            if (row == y && cul == x)
                cout << "●";
            else
                cout << " " << board[row][cul];
        }
        cout << endl;
    }
 
    cout << "dir : " << dir << " ,  score : " << score;
 
    cout << "\n\n";
}
 
void Move(int &x, int &y, int dir)
{
    x += moveX[dir];
    y += moveY[dir];
 
    if (x == C)
        x = 0;
 
    if (x == -1)
        x = C - 1;
 
    if (y == R)
        y = 0;
 
    if (y == -1)
        y = R - 1;
}
 
void DFS(int x, int y, int dir, int score)
{
    //PrintGame(x, y, dir, score);
 
    if (isEnd == true)
        return;
 
    if (board[y][x] == '@')
    {
        isEnd = true;
        return;
    }
 
    if (cache[y][x][score][dir] == true)
    {
        return;
    }
 
    cache[y][x][score][dir] = true;
 
    if(board[y][x] >= '0' && board[y][x] <= '9')
    {
        score = board[y][x] - '0';
        Move(x, y, dir);
        DFS(x, y, dir, score);
    }
    else if (board[y][x] == '.')
    {
        Move(x, y, dir);
        DFS(x, y, dir, score);
    }
    else if (board[y][x] == '_')
    {
        if (score == 0)
        {
            dir = RIGHT;
            Move(x, y, dir);
        }
        else if (score != 0)
        {
            dir = LEFT;
            Move(x, y, dir);
        }
        DFS(x, y, dir, score);
    }
    else if (board[y][x] == '|')
    {
        if (score == 0)
        {
            dir = DOWN;
            Move(x, y, dir);
        }
        else if (score != 0)
        {
            dir = UP;
            Move(x, y, dir);
        }
        DFS(x, y, dir, score);
    }
    else if (board[y][x] == '<')
    {
        dir = LEFT;
        Move(x, y, dir);
        DFS(x, y, dir, score);
    }
    else if (board[y][x] == '>')
    {
        dir = RIGHT;
        Move(x, y, dir);
        DFS(x, y, dir, score);
    }
    else if (board[y][x] == '^')
    {
        dir = UP;
        Move(x, y, dir);
        DFS(x, y, dir, score);
    }
    else if (board[y][x] == 'v')
    {
        dir = DOWN;
        Move(x, y, dir);
        DFS(x, y, dir, score);
    }
    else if (board[y][x] == '?')
    {
        int nextX, nextY;
        for (int d = 0; d < 4; d++)
        {
            nextX = x;
            nextY = y;
 
            Move(nextX, nextY, d);
            DFS(nextX, nextY, d, score);
        }
    }
    else if (board[y][x] == '+')
    {
        score++;
        if (score == 16)
            score = 0;
 
        Move(x, y, dir);
        DFS(x, y, dir, score);
    }
    else if (board[y][x] == '-')
    {
        score--;
        if (score == -1)
            score = 15;
 
        Move(x, y, dir);
        DFS(x, y, dir, score);
    }
}
 
 
int main(void)
{
    int T;
    cin >> T;
    bool canEnd;
    for (int testCase = 0; testCase < T; testCase++)
    {
        isEnd = false;
        canEnd = false;
        cin >> R >> C;
 
        for (int row = 0; row < R; row++)
        {
            for (int cul = 0; cul < C; cul++)
            {
                cin >> board[row][cul];
 
                if (board[row][cul] == '@')
                    canEnd = true;
 
                for (int score_ = 0; score_ < 16; score_++)
                {
                    for (int dir_ = 0; dir_ < 4; dir_++)
                    {
                        cache[row][cul][score_][dir_] = false;
                    }
                }
            }
        }
 
        if(canEnd == true)
            DFS(0, 0, 0, 0);
 
        cout << "#" << testCase + 1 << " ";
        if (isEnd == true)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
 
    return 0;
}
