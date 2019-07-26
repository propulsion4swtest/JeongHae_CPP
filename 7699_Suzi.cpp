#include<iostream>
#include<algorithm>
 
using namespace std;
 
char board[25][25];
 
int R, C;
 
bool nodeFlag[26] = { false, };
 
int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };
 
int DFS(int x, int y, int score)
{
 
    bool canMove = false;
 
    char cNode = board[y][x];
 
    nodeFlag[cNode - 'A'] = true;
     
    int nextX, nextY;
    char nextNode;
     
    int tmp = 0;
    int ret = 0;    
 
    for (int dir = 0; dir < 4; dir++)
    {
        nextX = x + moveX[dir];
        nextY = y + moveY[dir];
 
        if (nextX < 0 || nextX >= C || nextY < 0 || nextY >= R)
            continue;
 
        nextNode = board[nextY][nextX];
 
        if (nodeFlag[nextNode - 'A'] == true)
            continue;
 
         
        tmp = DFS(nextX, nextY, score + 1);
        ret = max(ret, tmp);
 
        if (ret == 26)
            return 26;
 
        canMove = true;
    }
 
    nodeFlag[cNode - 'A'] = false;
 
    if (canMove == false)
        return score;
    else
        return ret;
 
}
 
 
int main(void)
{
    int T;
    cin >> T;
    char str[25];
    for (int testCase = 0; testCase < T; testCase++)
    {
        cin >> R >> C;
 
        for (int row = 0; row < R; row++)
        {
            cin >> str;
            for (int cul = 0; cul < C; cul++)
            {
                board[row][cul] = str[cul];
            }
        }
 
        for (int i = 0; i < 'Z' - 'A' + 1; i++)
            nodeFlag[i] = false;
         
        int ret = DFS(0, 0, 1);
        cout << "#" << testCase + 1 << " " << ret << endl;
    }
 
}
