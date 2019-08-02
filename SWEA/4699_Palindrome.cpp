#include<iostream>
#include<algorithm>
 
using namespace std;
 
class Memo
{
public:
    int buy;
    int sell;
 
    Memo(int buy_, int sell_) : buy(buy_), sell(sell_)
    {   }
 
    Memo() : Memo(-1, -1)
    {   }
};
 
 
int L, K;
char str[2000];
Memo memos[30];
int cache[2010][2010];
 
 
int DFS(int head, int tail)
{
    if (head >= tail)
        return 0;
 
    if (str[head] == str[tail])
        return DFS(head + 1, tail - 1);
 
    if (cache[head][tail] != -1)
        return cache[head][tail];
 
    //왼쪽기준
    //추가
    int cost = 1999999999;
    cost = min(cost, memos[str[head] - 'a'].buy + DFS(head + 1, tail));
 
 
    //오른쪽 기준
    //추가
    cost = min(cost, memos[str[tail] - 'a'].buy + DFS(head, tail - 1));
 
 
    cost = min(cost, memos[str[head] - 'a'].sell + DFS(head + 1, tail));
    cost = min(cost, memos[str[tail] - 'a'].sell + DFS(head, tail - 1));
 
    cache[head][tail] = cost;
    return cost;
}
 
 
int main(void)
{
    int T;
    cin >> T;
 
    for (int testCase = 0; testCase < T; testCase++)
    {
        cin >> L >> K;
         
        for (int head = 0; head < L; head++)
            for (int tail = 0; tail < L; tail++)
                cache[head][tail] = -1;
         
        cin >> str;
        //memos.clear();
 
        int buy, sell;
        for (int i = 0; i < K; i++)
        {
            cin >> buy >> sell;
            //memos.push_back(Memo(buy, sell));
            memos[i].buy = buy;
            memos[i].sell = sell;
        }
 
        int value = DFS(0, L - 1);
 
        cout << "#" << testCase + 1 << " " << value << endl;;
    }
    return 0;
}
