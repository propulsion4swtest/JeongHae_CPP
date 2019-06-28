#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
 
using namespace std;
 
int N;
 
char board[300][300];
 
int moveX[8] = { 1,1,0,-1,-1,-1,0,1 };
int moveY[8] = { 0,1,1,1,0,-1,-1,-1 };
 
 
class Coord 
{
public:
    int x, y;
 
    Coord(int x_, int y_) : x(x_), y(y_)
    {   }
 
};
 
//x,y에 들어갈 번호를 알아낸다.
int FindNumber(int x, int y)
{
    int  value = 0;
    for (int dir = 0; dir < 8; dir++)
    {
        int nextX = x + moveX[dir];
        int nextY = y + moveY[dir];
 
        if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N)
            continue;
 
        if (board[nextY][nextX] == '*')
            value++;
    }
 
    return value;
}
 
//x,y 다음 좌표를 찾는다
bool FindNext(int &x, int &y)
{
    while (1)
    {
        if (y == N)
            return false;
 
        if (board[y][x] == '.')
            return true;
 
        x++;
        if(x == N)
        {
            x = 0;
            y++;
        }
    }
}
 
//x,y를 클릭한다, 이번 클릭으로 덮여진 좌표값을 vector에 저장한다
void CoverBoard(int x, int y)
{
    queue<Coord> qu;
 
    int result = FindNumber(x, y);
    board[y][x] = '0' + result;
    if (result == 0)
        qu.push(Coord(x, y));
     
    while (!qu.empty())
    {
        int tmpX = qu.front().x;
        int tmpY = qu.front().y;
        qu.pop();
 
        for (int dir = 0; dir < 8; dir++)
        {
            int nextX = tmpX + moveX[dir];
            int nextY = tmpY + moveY[dir];
 
            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N)
                continue;
 
            if (board[nextY][nextX] != '.')
                continue;
 
            result = FindNumber(nextX, nextY);
            board[nextY][nextX] = '0' + result;
            if (result == 0)
                qu.push(Coord(nextX, nextY));   
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
            if (board[row][cul] == '.')
                cout << " .";
            else if (board[row][cul] == '*')
                cout << " *";
            else
                cout << " " << board[row][cul];
 
        }
        cout << endl;
    }
    cout << "\n\n";
 
}
 
 
bool IsFull()
{
    for (int row = 0; row < N; row++)
    {
        for (int cul = 0; cul < N; cul++)
        {
            if (board[row][cul] == '.')
                return false;
        }
    }
 
    return true;
}
 
//클릭에 의해서 덮여진 0이외의 숫자의 좌표를 별도 저장해야한다.
//뒤덮은 지역을 다시 empty로 되돌린 후 x좌표를 1 더하고 넘긴다.
int click_count = 0;
int min_count = 999999999;
/*
void DFS(int x, int y)
{
    if (FindNext(x, y) == false)
    {
        if (IsFull() == true)
        {
            min_count = min(min_count, click_count);
            //PrintBoard();
            //클릭횟수 갱신
        }
         
        return;
    }
 
    vector<Coord> covered;
    click_count++;
    CoverBoard(x, y, covered);
    //PrintBoard();
     
    DFS(x, y);
 
    int size = covered.size();
    int tmpX, tmpY;
    for (int i = 0; i < size; i++)
    {
        tmpX = covered[i].x;
        tmpY = covered[i].y;
 
        board[tmpY][tmpX] = '.';
    }
    click_count--;
    //PrintBoard();
 
    if (board[y][x] != '0')
    {
        x++;
        if (x == N)
        {
            x = 0;
            y++;
        }
        DFS(x, y);
    }
}
*/
 
void Simulation()
{
    int x = 0, y = 0;
 
    while (1)
    {
        FindNext(x, y);
 
        if (y == N)
            break;
 
        int value = FindNumber(x, y);
        if (value == 0)
        {
            CoverBoard(x, y);
            click_count++;
            //PrintBoard();
        }
        else
        {
            x++;
            if (x == N)
            {
                x = 0;
                y++;
            }
        }
    }
 
    x = 0;
    y = 0;
 
    while (1)
    {
        FindNext(x, y);
 
        if (y == N)
            break;
         
        CoverBoard(x, y);
        click_count++;
        //PrintBoard();
 
    }
 
    //PrintBoard();
}
 
int main(void)
{
    int T;
    cin >> T;
    for (int testCase = 0; testCase < T; testCase++)
    {
        click_count=0;
        min_count = 99999999;
 
        cin >> N;
        string str;
        for (int row = 0; row < N; row++)
        {
            cin >> str;       
            for(int cul = 0; cul < N; cul++)
            {
                board[row][cul] = str[cul];
            }
        }
 
        Simulation();
 
        cout << "#" << testCase + 1 << " " << click_count << endl;
        //DFS(0, 0);
 
        /*
        vector<Coord> dummy;
        CoverBoard(0, 0, dummy);
        CoverBoard(4, 0, dummy);
        CoverBoard(0, 2, dummy);
        CoverBoard(0, 3, dummy);
        CoverBoard(0, 4, dummy);
        CoverBoard(2, 2, dummy);
        CoverBoard(3, 2, dummy);
        CoverBoard(4, 4, dummy);
 
        PrintBoard();
        */
        /*
        vector<Coord> dummy;
        while (1)
        {
            dummy.clear();
            int inputX, inputY;
            cin >> inputX >> inputY;
 
            CoverBoard(inputX, inputY, dummy);
            PrintBoard();
 
 
            int zzz;
            cin >> zzz;
            int size = dummy.size();
            int tmpX, tmpY;
            if (zzz == -1)
            {
                for (int i = 0; i < size; i++)
                {
                    tmpX = dummy[i].x;
                    tmpY = dummy[i].y;
 
                    board[tmpY][tmpX] = '.';
                }
                PrintBoard();
            }
        }
        */
         
    }
 
 
 
    /*
    if (IsFull())
        cout << "full" << endl;
    else
        cout << "empty" << endl;
    */
    /*
    int x = 0;
    int y = 0;
 
    if (!FindNext(x, y))
    {
        cout << "fail" << endl;
    }
    cout << endl;
    */
     
    /*
    CoverBoard(0, 9);
    PrintBoard();
 
    CoverBoard(9, 9);
    PrintBoard();
    */
 
    /*
    int result = FindNumber(4, 4);
    cout << result << endl;
    */
 
    return 0;
}
