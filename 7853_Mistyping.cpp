#include<iostream>
#include<string>
 
using namespace std;
 
 
int dictionary[1050];
 
 
string str;
 
void GetNearbyNum(int i)
{
    if ((i - 1) >= 0)
        dictionary[i] |= 1 << (str[i - 1] - 'a');
 
    if ((i + 1) < str.size())
        dictionary[i] |= 1 << (str[i + 1] - 'a');
 
    dictionary[i] |= 1 << (str[i] - 'a');
}
 
int GetCount(int index)
{
    int ret = 0;
    for (int i = 0; i < 26; i++)
    {
        if ((dictionary[index] & (1 << i)) != 0)
            ret++;
    }
 
    return ret;
}
 
int main(void)
{
    int T;
    cin >> T;
    for (int testCase = 0; testCase < T; testCase++)
    {
        cin >> str;
 
        for (int i = 0; i < str.size(); i++)
            dictionary[i] = 0;
 
        long long cnt = 1;
 
        for (int i = 0; i < str.size(); i++)
        {
            GetNearbyNum(i);
            cnt *= GetCount(i);
            cnt %= 1000000007;
        }
 
        cout << "#" << testCase + 1 << " " << cnt << endl;
    }
 
    return 0;
}
