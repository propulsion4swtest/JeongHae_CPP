#include<iostream>
 
using namespace std;
 
int N;
int weights[1020];
int key[1000];  //key[weights[a]] : 해당 무게가 가지게 되는 index
int cache[0b111111111 + 1][0b111111111 + 1];
 
void SwapArr(int *arr, int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}
 
int Perm(int arrSize, int left, int right, int leftBit, int rightBit)
{
    if (left < right)
        return 0;
 
    if (arrSize == N)
    {
 
        return 1;
    }
 
    if (cache[leftBit][rightBit] != -1)
        return cache[leftBit][rightBit];
 
 
    int ret = 0;
 
    for (int i = arrSize; i < N; i++)
    {
        SwapArr(weights, i, arrSize);
 
        //왼쪽에 올린다.
        ret += Perm(arrSize + 1, left + weights[arrSize], right, leftBit | (1 << key[weights[arrSize]]), rightBit);
 
        //오른쪽에 올린다.
        ret += Perm(arrSize + 1, left, right + weights[arrSize], leftBit, rightBit | (1 << key[weights[arrSize]]));
 
        SwapArr(weights, i, arrSize);
    }
 
    cache[leftBit][rightBit] = ret;
    return ret;
}
 
int main(void)
{
    int T;
    cin >> T;
    for (int testCase = 0; testCase < T; testCase++)
    {
        cin >> N;
 
        for (int i = 0; i < N; i++)
        {
            cin >> weights[i];
            key[weights[i]] = i;
        }
 
        for (int row = 0; row < 0b111111111 + 1; row++)
        {
            for (int cul = 0; cul < 0b111111111 + 1; cul++)
            {
                cache[row][cul] = -1;
            }
 
        }
 
        int ret = Perm(0, 0, 0, 0, 0);
 
        cout << "#" << testCase + 1 << " " << ret << endl;
    }
 
    return 0;
}
