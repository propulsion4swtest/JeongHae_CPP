
#include<iostream>
#include<algorithm>
 
using namespace std;
 
int D, W, K;
 
bool board[14][21];
 
//position 위치에서의 수직방향 안정성을 점검한다.
bool CheckArmor(bool board[][21], int position)
{
    int count = 1;
    bool lastType = false;
 
    lastType = board[position][0];
    for (int depth = 1; depth < D; depth++)
    {
        if (count == K)
            return true;
 
        if (board[depth - 1][position] != board[depth][position])
        {
            lastType = board[depth][position];
            count = 1;
 
            if (depth > D - K)
                return false;
        }
        else if (board[depth - 1][position] == board[depth][position])
        {
            count++;
        }
    }
 
    if (count == K)
        return true;
 
    return false;
}
 
 
bool CheckTotalArmor(bool board[][21])
{
    for (int cul = 0; cul < W; cul++)
    {
        if (CheckArmor(board, cul) == false)
            return false;
    }
 
    return true;
}
 
//board[row]를 모두다 type으로 바꾼다.
void ChangeLayer(bool board[][21], int row, bool type)
{
    for (int cul = 0; cul < W; cul++)
    {
        board[row][cul] = type;
    }
}
 
 
void ReturnLayer(bool board[][21], int row, bool layer[])
{
    for (int cul = 0; cul < W; cul++)
    {
        board[row][cul] = layer[cul];
    }
}
 
int minValue;
bool isClear;
void Comb(int arrSize, int m, int n, int index)
{
    if (isClear)
        return;
 
    if (arrSize == n)
    {
        if (CheckTotalArmor(board) == true)
        {
            minValue = min(n, minValue);
            isClear = true;
        }
 
        return;
    }
 
    if (index == m)
        return;
 
    //index번째 라인의 필름을 모두다 바꾼다.
    bool layerBackup[21];
    for (int cul = 0; cul < W; cul++)
    {
        layerBackup[cul] = board[index][cul];
    }
 
    //A로 바꾼다
    ChangeLayer(board, index, true);
    Comb(arrSize + 1, m, n, index + 1);
    ReturnLayer(board, index, layerBackup);
    //롤백
     
    //B로 바꾼다
    ChangeLayer(board, index, false);
    Comb(arrSize + 1, m, n, index + 1);
    ReturnLayer(board, index, layerBackup);
    //롤백    
     
    Comb(arrSize, m, n, index + 1);
}
 
 
int main(void)
{
    int T;
    cin >> T;
    for (int testCase = 0; testCase < T; testCase++)
    {
        minValue = 9999;
        isClear = false;
 
        cin >> D >> W >> K;
 
        for (int row = 0; row < D; row++)
        {
            for (int cul = 0; cul < W; cul++)
            {
                cin >> board[row][cul];
            }
        }
 
 
        for (int cnt = 0; cnt <= D; cnt++)
        {
            if (isClear == true)
                break;
 
            Comb(0, D, cnt, 0);
        }
 
        cout << "#" << testCase + 1 << " " << minValue << endl;
    }
 
 
    return 0;
}



/*
#include<iostream>
#include<algorithm>
 
using namespace std;
 
int D, W, K;
 
bool board[14][21];
 
//position 위치에서의 수직방향 안정성을 점검한다.
bool CheckArmor(bool board[][21], int position)
{
    int count = 1;
    bool lastType = false;
 
    lastType = board[position][0];
    for (int depth = 1; depth < D; depth++)
    {
        if (count == K)
            return true;
 
        if (board[depth - 1][position] != board[depth][position])
        {
            lastType = board[depth][position];
            count = 1;
 
            if (depth > D - K)
                return false;
        }
        else if (board[depth - 1][position] == board[depth][position])
        {
            count++;
        }
    }
 
    if (count == K)
        return true;
 
    return false;
}
 
 
bool CheckTotalArmor(bool board[][21])
{
    for (int cul = 0; cul < W; cul++)
    {
        if (CheckArmor(board, cul) == false)
            return false;
    }
 
    return true;
}
 
//board[row]를 모두다 type으로 바꾼다.
void ChangeLayer(bool board[][21], int row, bool type)
{
    for (int cul = 0; cul < W; cul++)
    {
        board[row][cul] = type;
    }
}
 
 
void ReturnLayer(bool board[][21], int row, bool layer[])
{
    for (int cul = 0; cul < W; cul++)
    {
        board[row][cul] = layer[cul];
    }
}
 
int minValue;
bool isClear;
void Comb(int arrSize, int m, int n, int index)
{
    if (isClear)
        return;
 
    if (arrSize == n)
    {
        if (CheckTotalArmor(board) == true)
        {
            minValue = min(n, minValue);
            isClear = true;
        }
 
        return;
    }
 
    if (index == m)
        return;
 
    //index번째 라인의 필름을 모두다 바꾼다.
    bool layerBackup[21];
    for (int cul = 0; cul < W; cul++)
    {
        layerBackup[cul] = board[index][cul];
    }
 
    //A로 바꾼다
    ChangeLayer(board, index, true);
    Comb(arrSize + 1, m, n, index + 1);
    ReturnLayer(board, index, layerBackup);
    //롤백
     
    //B로 바꾼다
    ChangeLayer(board, index, false);
    Comb(arrSize + 1, m, n, index + 1);
    ReturnLayer(board, index, layerBackup);
    //롤백    
     
    Comb(arrSize, m, n, index + 1);
}
 
 
 
void RPerm(int arrSize, int n, int count)
{
    if (CheckTotalArmor(board))
    {
        minValue = min(minValue, count);
    }
 
    if (arrSize == n)
    {
        return;
    }
     
    bool layerBackup[21];
    for (int cul = 0; cul < W; cul++)
    {
        layerBackup[cul] = board[arrSize][cul];
    }
 
    //index 번째 layer를 A로 덮는다
 
    ChangeLayer(board, arrSize, true);
    RPerm(arrSize + 1, n, count + 1);
    ReturnLayer(board, arrSize, layerBackup);
 
    //B로 덮는다
 
    ChangeLayer(board, arrSize, false);
    RPerm(arrSize + 1, n, count + 1);
    ReturnLayer(board, arrSize, layerBackup);
 
 
    //안 덮는다
    RPerm(arrSize + 1, n, count);
 
}
 
 
int main(void)
{
    int T;
    cin >> T;
    for (int testCase = 0; testCase < T; testCase++)
    {
        minValue = 9999;
        isClear = false;
 
        cin >> D >> W >> K;
 
        for (int row = 0; row < D; row++)
        {
            for (int cul = 0; cul < W; cul++)
            {
                cin >> board[row][cul];
            }
        }
 
        /*
        for (int cnt = 0; cnt <= D; cnt++)
        {
            if (isClear == true)
                break;
 
            Comb(0, D, cnt, 0);
        }
        */
        RPerm(0, D, 0);
 
        cout << "#" << testCase + 1 << " " << minValue << endl;
    }
 
 
    return 0;
}
*/
