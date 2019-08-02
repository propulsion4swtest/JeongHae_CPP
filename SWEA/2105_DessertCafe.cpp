#include<iostream>
#include<algorithm>
 
using namespace std;
 
int N;
int board[25][25];
 
int moveX[4] = { 1,-1,-1,1 };
int moveY[4] = { 1,1,-1,-1 };
 
int flag[105] = { false, };
int maxCnt = -1;
 
 
bool FollowPath(int cX, int cY, int aLength, int bLength)
{
    int tmpFlag[105] = { false, };
    int dir = 2;
    int nextX, nextY;
    int num;
 
    nextX = cX;
    nextY = cY;
 
    num = board[nextY][nextX];
    if (flag[num] == true || tmpFlag[num] == true)
        return false;
 
    tmpFlag[num] = true;
 
    for (int i = 0; i < aLength - 1; i++)
    {
        nextX += moveX[dir];
        nextY += moveY[dir];
 
        if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N)
            return false;
 
        num = board[nextY][nextX];
        if (flag[num] == true || tmpFlag[num] == true)
            return false;
 
        tmpFlag[num] = true;
    }
 
    dir++;
 
    for (int i = 0; i < bLength - 1; i++)
    {
        nextX += moveX[dir];
        nextY += moveY[dir];
 
        if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N)
            return false;
 
        num = board[nextY][nextX];
        if (flag[num] == true || tmpFlag[num] == true)
            return false;
 
        tmpFlag[num] = true;
    }
 
 
    return true;
}
 
 
void DFS(int cX, int cY, int aLength, int bLength, int dir)
{
    if (dir == 2)
    {
        if (aLength == 0 || bLength == 0)
            return;
 
        bool result = FollowPath(cX, cY, aLength, bLength);
 
        if (result == true)
        {
            int cnt = (aLength + bLength) * 2;
            maxCnt = max(maxCnt, cnt);
        }
        return;
    }
 
    int num = board[cY][cX];
 
    if (flag[num] == true)
        return;
 
    flag[num] = true;
 
 
    //현재 방향 유지
    int nextX = cX + moveX[dir];
    int nextY = cY + moveY[dir];
 
    if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N)
    {
        if (dir == 0)
        {
                DFS(nextX, nextY, aLength + 1, bLength, dir);
        }
        else if (dir == 1)
        {
                DFS(nextX, nextY, aLength, bLength + 1, dir);
        }
    }
         
 
 
    //방향 전환
    nextX = cX + moveX[dir + 1];
    nextY = cY + moveY[dir + 1];
 
    if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N)
    {
        if (dir == 0)
        {
            if (aLength > 0)
                DFS(nextX, nextY, aLength, bLength + 1, dir + 1);
        }
        else if (dir == 1)
        {
            if (bLength > 0)
                DFS(nextX, nextY, aLength, bLength, dir + 1);
        }
    }
 
 
 
 
    flag[num] = false;
}
 
 
int main(void)
{
    int T;
    cin >> T;
    for (int testCase = 0; testCase < T; testCase++)
    {
        maxCnt = -1;
        cin >> N;
        for (int row = 0; row < N; row++)
        {
            for (int cul = 0; cul < N; cul++)
            {
                cin >> board[row][cul];
            }
        }
 
        for (int row = 0; row < N; row++)
        {
            for (int cul = 0; cul < N; cul++)
            {
                DFS(cul, row, 0, 0, 0);
            }
        }
 
        cout << "#" << testCase + 1 << " " << maxCnt << endl;
    }
 
}
