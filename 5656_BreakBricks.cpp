#include<iostream>
#include<queue>
#include<algorithm>
 
using namespace std;
 
int orgBoard[20][20];
int N, W, H;
int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };
 
class Node
{
public:
    int x, y, size;
 
    Node(int x_, int y_, int size_) : x(x_), y(y_), size(size_)
    {   }
 
    Node() : Node(-1, -1, -1)
    {   }
};
 
void PrintBoard(int board[][20])
{
    cout << "\n\n";
    for (int row = 0; row < H; row++)
    {
        for (int cul = 0; cul < W; cul++)
        {
            cout << board[row][cul] << " ";
        }
        cout << endl;
    }
    cout << "\n\n";
}
 
 
//x,y, 지점에 size 크기로 폭발을 일으킨다
void Explosion(queue<Node> &qu, int x, int y, int size, int board[][20])
{
    int nextX, nextY;
    board[y][x] = 0;
    for (int dir = 0; dir < 4; dir++)
    {
        nextX = x;
        nextY = y;
        for (int length = 0; length < size - 1; length++)
        {
            nextX += moveX[dir];
            nextY += moveY[dir];
 
            if (nextX < 0 || nextX >= W || nextY < 0 || nextY >= H)
                break;
 
            if (board[nextY][nextX] > 1)
                qu.push(Node(nextX, nextY, board[nextY][nextX]));
 
            board[nextY][nextX] = 0;
        }
    }
}
 
void Explosion(queue<Node> &qu, Node &node, int board[][20])
{
    Explosion(qu, node.x, node.y, node.size, board);
}
 
 
void DropBomb(int x, int board[][20])
{
    int y = 0;
    queue<Node> qu;
 
    for (y = 0; y < H; y++)
    {
        if (board[y][x] != 0)
            break;
    }
 
    if (y == H)
        return;
 
    qu.push(Node(x, y, board[y][x]));
    board[y][x] = 0;
 
    while (!qu.empty())
    {
        Node node = qu.front();
        qu.pop();
 
        Explosion(qu, node, board);
 
    }
 
}
 
int DropLine(int cul, int board[][20])
{
    int line[25];
    int lineSize = 0;
    for (int row = H - 1; row >= 0; row--)
    {
        if (board[row][cul] != 0)
        {
            line[lineSize] = board[row][cul];
            board[row][cul] = 0;
            lineSize++;
        }
    }
         
    for (int i = 0, row = H- 1; i < lineSize; i++, row--)
    {
        board[row][cul] = line[i];
    }
 
    return lineSize;
}
 
int DropCity(int board[][20])
{
    bool isEmpty = false;
    int sum = 0;
    for (int cul = 0; cul < W; cul++)
    {
        sum += DropLine(cul, board);
    }
 
    return sum;
}
 
bool isEnd = false;
int minCount = 999999999;
//(가로길이W) PI (폭탄 투하 횟수N)
/*
void RPerm(int arr[], int count, int m, int n)
{
    if (isEnd == true)
        return; 
 
    if (count == n)
    {
        //arr[0] ~ [N]에 폭탄을 투하할 x좌표가 들어있다.
        int board[20][20];
        for (int row = 0; row < 20; row++)
        {
            for (int cul = 0; cul < 20; cul++)
            {
                board[row][cul] = orgBoard[row][cul];
            }
        }
 
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            int x = arr[i];
 
            DropBomb(x, board);
            count = DropCity(board);
 
            if (count == 0)
            {
                minCount = 0;
                isEnd = true;
                return;
            }
 
            minCount = min(minCount, count);
        }
 
 
        return;
    }
 
    for (int i = 0; i < m; i++)
    {
        arr[count] = i;
        RPerm(arr, count + 1, m, n);
    }
}
*/
 
void CopyBoard(int lhs[][20], int rhs[][20])
{
    for (int row = 0; row < 20; row++)
    {
        for (int cul = 0; cul < 20; cul++)
        {
            lhs[row][cul] = rhs[row][cul];
        }
    }
}
 
void RPerm(int count, int m, int n)
{
    if (isEnd == true)
        return;
 
    int backup[20][20];
 
    CopyBoard(backup, orgBoard);
 
    if (count == n)
    {   
        return;
    }
 
    int num = 0;
    for (int i = 0; i < m; i++)
    {
        DropBomb(i, orgBoard);
        num = DropCity(orgBoard);
 
        if (num == 0)
        {
            minCount = 0;
            isEnd = true;
            return;
        }
         
        minCount = min(minCount, num);
 
        RPerm(count + 1, m, n);
 
        CopyBoard(orgBoard, backup);
    }
}
 
 
int main(void)
{
    int T;
    cin >> T;
 
    for (int testCase = 0; testCase < T; testCase++)
    {
        isEnd = false;
        minCount = 999999999;
        cin >> N >> W >> H;
 
        for (int row = 0; row < H; row++)
        {
            for (int cul = 0; cul < W; cul++)
            {
                cin >> orgBoard[row][cul];
            }
        }
 
        queue<Node> dummy;
        //Explosion(dummy, 2, 7, 6);
 
 
        //int arr[6];
        //RPerm(arr, 0, W, N);
        RPerm(0, W, N);
        cout << "#" << testCase + 1 << " " << minCount<<endl;
         
        /*
        DropBomb(2);
 
        PrintBoard();
 
        DropBomb(2);
 
        PrintBoard();
         
 
        int a = DropCity();
        PrintBoard();
        cout << a << endl;
        */
    }
 
 
    return 0;
}
