/*
 
#include<iostream>
 
using namespace std;
 
int city[300050];
 
int main(void)
{
    int T;
    cin >> T;
 
    for (int testCase = 0; testCase < T; testCase++)
    {
        int cnt = 0;
        int N, D;
        cin >> N >> D;
 
        for (int i = 0; i < N; i++)
        {
            cin >> city[i];
        }
 
        int d = 0;
        for (int i = 0; i < N; i++)
        {
            if (d == D - 1 && city[i] == 0)
            {
                d = 0;
                cnt++;
            }
            else if (city[i] == 1)
            {
                d = 0;
            }
            else
            {
                d++;
            }
        }
 
        cout << "#" << testCase + 1 << " " << cnt << endl;
 
    }
 
}
*/
 
 
 
#include<iostream>
 
using namespace std;
 
int city[300050];
int N, D;
 
 
int GetCount(int start, int end)
{
    int diff = end - start - 1;
 
    int cnt = diff / D;
    return cnt;
}
 
 
int main(void)
{
    int T;
    cin >> T;
 
    for (int testCase = 0; testCase < T; testCase++)
    {
        int cnt = 0;
        cin >> N >> D;
 
        int cityCnt = 0;
        int input;
         
        city[cityCnt++] = -1;
        for (int i = 0; i < N; i++)
        {
            cin >> input;
            if (input == 1)
                city[cityCnt++] = i;
        }
        city[cityCnt++] = N;
 
         
        for (int i = 1; i < cityCnt; i++)
        {
            cnt += GetCount(city[i - 1], city[i]);
        }
 
        cout << "#" << testCase + 1 << " " << cnt << endl;
 
 
    }
}
