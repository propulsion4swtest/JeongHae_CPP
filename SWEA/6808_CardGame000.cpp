#include<iostream>
#include<vector>
#include<stdio.h>
#include<cstdio>
 
#define _CRT_SECURE_NO_WARNINGS
 
using namespace std;
 
/*
vector<int> enemyCard;
vector<int> myCard;
vector<bool> flag;
*/
 
int enemyCard[9];
int myCard[9];
bool flag[19];
 
//362880
 
void SwapArr(vector<int> &arr, int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}
 
vector<vector<int>> cache;
 
int score = 0;
long long test = 0;
 
 
void Perm(int length, int myScore,int enemyScore)
{
    if (length == 9)
    {
        if (myScore > enemyScore)
            score++;
 
        return;
    }
 
    for (int i = length; i < 9; i++)
    {
        //SwapArr(myCard, length, i);
        int tmp = myCard[length];
        myCard[length] = myCard[i];
        myCard[i] = tmp;
 
        if (myCard[length] > enemyCard[length])
            myScore += (myCard[length] + enemyCard[length]);
        else
            enemyScore += (myCard[length] + enemyCard[length]);
 
        Perm(length + 1, myScore, enemyScore);
 
        if (myCard[length] > enemyCard[length])
            myScore -= (myCard[length] + enemyCard[length]);
        else
            enemyScore -= (myCard[length] + enemyCard[length]);
 
        //SwapArr(myCard, length, i);
        tmp = myCard[length];
        myCard[length] = myCard[i];
        myCard[i] = tmp;
    }
     
}
 
 
int main(void)
{
    int T;
    cin >> T;
    int input;
    for (int testCase = 0; testCase < T; testCase++)
    {
        //myScore = 0;
        //enemyScore = 0;
        //cache.assign(9, vector<int>((1 << 9) + 1, -1));
        //flag.assign(19, false);
        //enemyCard.assign(9, 0);
        //myCard.clear();
         
        for (int i = 0; i < 19; i++)
            flag[i] = false;
 
        for (int i = 0; i < 9; i++)
        {
            enemyCard[i] = 0;
            myCard[i] = 0;
        }
         
        score = 0;
        for (int i = 0; i < 9; i++)
        {
            cin >> input;
            //scanf("%d", &input);
            enemyCard[i] = input;
            flag[input] = true;
        }
 
        int index = 0;
        for (int i = 1; i <= 18; i++)
        {
            if (flag[i] == false)
            {
                myCard[index] = i;
                index++;
            }
        }
        Perm(0,0,0);
        //cout <<"#"<<testCase + 1<<" " << score << " "<< 362880 - score <<endl;
        //cout << test << endl;
        printf("#%d %d %d\n", testCase + 1, 362880 - score, score);
    } 
 
}
