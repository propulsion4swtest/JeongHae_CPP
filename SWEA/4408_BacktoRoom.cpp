#include<iostream>
#include<list>
#include<algorithm>
  
using namespace std;
  
class Path
{
public:
    int begin, end;
  
    Path(int begin_, int end_) : begin(begin_), end(end_)
    {   }
  
    bool operator < (const Path & rhs) const
    {
        if (begin != rhs.begin)
            return begin < rhs.begin;
        else
            return end < rhs.end;
    }
};
  
list<Path> paths;
  
int N;
  
//false : 안겹처진다
bool IsOverLap(int Abegin, int Aend, int Bbegin, int Bend)
{
    if (Abegin > Bend || Bbegin > Aend)
        return false;
    else
        return true;
}
  
int Solve()
{
    int count = 0;
  
    for (list<Path>::iterator it1 = paths.begin(); it1 != paths.end(); count++)
    {
        list<Path>::iterator it2 = it1;
        it2++;
  
        Path lastPath = *it1;
  
        for (; it2 != paths.end();)
        {            
            if (IsOverLap(it2->begin, it2->end, lastPath.begin, lastPath.end) == false)
            {
                lastPath = *it2;
                it2 = paths.erase(it2);
            }
            else
                it2++;
        } 
        it1 = paths.erase(it1);
    } 
    return count;
}
  
int main(void)
{
    int T;
    cin >> T;
    int begin, end;
    for (int testCase = 0; testCase < T; testCase++)
    {
        paths.clear();
        cin >> N;
  
        for (int i = 0; i < N; i++)
        {
            cin >> begin >> end;
            begin = (begin - 1) / 2;
            end = (end - 1) / 2;
  
            paths.push_back(Path(min(begin, end), max(begin, end)));
        }
  
        paths.sort(); 
        int ret = Solve(); 
        cout << "#" << testCase + 1 << " " << ret << endl; 
    }  
}
