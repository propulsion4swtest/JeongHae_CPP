#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<vector>
 
using namespace std;
 
int N, K;
 
int board[8][8];
 
int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };
 
int cache[2][4][8][8];
int length[2][4][8][8];
int path[8][8] = { 0, };
 
class Coord
{
public:
    int x, y;
 
    Coord(int x_, int y_) : x(x_), y(y_)
    {   }
};
 
bool flag[8][8];
 
void PrintFlag()
{
    cout << "\n\n";
    for (int row = 0; row < N; row++)
    {
        for (int cul = 0; cul < N; cul++)
        {
            cout << flag[row][cul];
        }
        cout << endl;
    }
}
 
 
void PrintPath()
{
    cout << "\n\n";
    for (int row = 0; row < N; row++)
    {
        for (int cul = 0; cul < N; cul++)
        {
            printf("%3d", path[row][cul]);
        }
        cout << endl;
    }
}
 
 
int DFS(int arrSize, int shovel, int x, int y)
{
    int nX, nY;
    int cH, nH;
    cH = board[y][x];
 
    int canMove = false;
    int ret = 0, tmp = -1;
 
    flag[y][x] = true;
 
    path[y][x] = arrSize + 1;
 
     
    for (int dir = 0; dir < 4; dir++)
    {
        nX = x + moveX[dir];
        nY = y + moveY[dir];
 
        if (nX < 0 || nX >= N || nY < 0 || nY >= N)
            continue;
 
        nH = board[nY][nX];
 
        if (length[shovel][dir][y][x] < arrSize)
        {
            if (cH > nH && flag[nY][nX] == false)
            {
                //삽질 없이 이동 가능하다.
 
                if (cache[shovel][dir][y][x] > -1)
                {
                    canMove = true;
                    tmp = arrSize + cache[shovel][dir][y][x];
                    ret = max(ret, tmp);
                }
                else
                {
                    length[shovel][dir][y][x] = arrSize;
 
                    canMove = true;
                    tmp = DFS(arrSize + 1, shovel, nX, nY);
                    ret = max(ret, tmp);
 
                    if (tmp != -1)
                        cache[shovel][dir][y][x] = tmp - arrSize;
                }
 
            }
            else if (cH <= nH && flag[nY][nX] == false)
            {
                if (cH > nH - K && shovel == 1)
                {
                    if (cache[shovel][dir][y][x] > -1)
                    {
                        canMove = true;
                        tmp = arrSize + cache[shovel][dir][y][x];
                        ret = max(ret, tmp);
                         
                    }
                    else
                    {
                        //삽질 해야 이동 할 수 있다.
                        length[shovel][dir][y][x] = arrSize;
 
                        canMove = true;
 
                        board[nY][nX] = cH - 1; //한칸 더 작게 흙을 파낸다.
                        tmp = DFS(arrSize + 1, 0, nX, nY);
                        board[nY][nX] = nH;
 
                        ret = max(ret, tmp);
 
                        if (tmp != -1)
                            cache[shovel][dir][y][x] = tmp - arrSize;
                    }
                }
 
                 
            }
 
        }
        else
        {
            ret = max(ret, 0);
        }
    }
     
 
 
    flag[y][x] = false;
    path[y][x] = 0;
 
    //기저사례
    //4방향 중 갈 수 있는곳이 더 없을경우
    if (canMove == false)
        return arrSize; 
    else
        return ret;
     
}
 
 
vector<Coord> coords;
 
int main(void)
{
    int T;
    cin >> T;
    for (int testCase = 0; testCase < T; testCase++)
    {
        cin >> N >> K;
 
        int maxH = 0;
 
        coords.clear();
         
        for (int row = 0; row < N; row++)
        {
            for (int cul = 0; cul < N; cul++)
            {
                cin >> board[row][cul];
 
                if (board[row][cul] > maxH)
                {
                    maxH = board[row][cul];
                    coords.clear();
                    coords.push_back(Coord(cul, row));
                }
                else if (board[row][cul] == maxH)
                    coords.push_back(Coord(cul, row));
 
                for (int dir = 0; dir < 4; dir++)
                {
                    for (int shovel = 0; shovel < 2; shovel++)
                    {
                        length[shovel][dir][row][cul] = -1;
                        cache[shovel][dir][row][cul] = -1;
                    }
                }
            }
        }
 
        int ret = 0, tmp;
 
        for (int i = 0; i < coords.size(); i++)
        {
            tmp = DFS(0, 1, coords[i].x, coords[i].y);
            ret = max(ret, tmp);
        }
 
 
        cout << "#" << testCase + 1 << " " << ret + 1 << endl;
    } 
 
 
    return 0;
}
 
 
/*
1
5 2
9 5 4 8 6
4 7 5 1 9
1 2 3 4 9
3 5 2 4 6
5 7 8 4 2
*/
