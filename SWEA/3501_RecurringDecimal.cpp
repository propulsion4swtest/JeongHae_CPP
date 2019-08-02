#include<iostream>
#include<vector>
#include<string.h>
 
using namespace std;
 
int p, q;
int start = -1;
 
 
vector<int> decimals;
int remains[10000000];  //map[a] = b : 나머지a가 오는 순서
 
                        //true : 순환소수 아님 , false : 순환소수임
bool FindDecimal()
{
    int remain, decimal;
    int index = 0;
    while (1)
    {
        remain = p % q;
        if (remain == 0)
            return true;
 
        p = remain * 10;
        decimal = p / q;
 
        if (remains[remain] == -1)
        {
            //한번도  호출 된 적 없는 remain 이면...
            //아직 start를 못찾았다.
            remains[remain] = index;
            decimals.push_back(decimal);
        }
        else
        {
            //호출 된 적이 있는 remain이다.
            //start를 찾았다.
            start = remains[remain];
 
            return false;
        }
        index++;
    }
}
 
 
int main(void)
{
    int T;
    cin >> T;
    for (int testCase = 0; testCase < T; testCase++)
    {
        decimals.clear();
        memset(remains, -1, sizeof(remains));
        start = -1;
        cin >> p >> q;
         
        cout << "#" << testCase + 1 << " ";
     
        cout << p / q;
     
        FindDecimal();
 
        if(decimals.size() != 0)
        cout << ".";
         
        for (int i = 0; i < decimals.size(); i++)
        {
            if (i == start)
                cout << "(";
 
            cout << decimals[i];
        }
     
        if (start != -1)
            cout << ")";
 
        cout << endl;
    }
 
}
