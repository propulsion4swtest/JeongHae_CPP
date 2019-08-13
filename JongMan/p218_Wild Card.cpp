#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<vector<int>> cache;

bool isFind = false;
void RPerm(string &lhs, string &rhs, int lhsIndex, int rhsIndex)
{
	if(cache[lhsIndex][rhsIndex] != -1)
		return;

	while(1)
	{
		//전혀 다른 글자가 매칭 된 경우,문자열의 끝에 다 온경우 반복문을 빠져 나온다.
		if(lhs[lhsIndex] != '?' && lhs[lhsIndex] != rhs[rhsIndex])
			break;

		//lhs나 rhs의 index가 끝에 도달했을 경우
		if(lhsIndex == lhs.size() || rhsIndex == rhs.size())
			break;

		lhsIndex++;
		rhsIndex++;
	}

	//기저사례 : index가 끝에 도달하여 2개의 문자열이 같을 경우
	if(lhsIndex == lhs.size() && rhsIndex == rhs.size())
	{	
		isFind = true;
		cache[lhsIndex][rhsIndex] = 1;
		return;
	}

	//lhs가 *이 아니어서 서로 완전히 다른경우
	if(lhs[lhsIndex] != '*')
	{
		cache[lhsIndex][rhsIndex] = 0;
		return;
	}

	rhsIndex;
	//rhsIndex를 계속 증가시켜가면서 2개의 문자를 비교한다.
	while(1)
	{
		if(rhsIndex == rhs.size())
			break;
		
		//cout<<lhs.size()<<endl;
		if(lhsIndex == lhs.size() - 1 && lhs[lhsIndex] == '*')
		{
			isFind = true;
			cache[lhsIndex][rhsIndex] = 1;
			return;
		}
			
		if(lhs[lhsIndex + 1] == rhs[rhsIndex])
			RPerm(lhs,rhs,lhsIndex + 1, rhsIndex);

		rhsIndex++;
	}

	cache[lhsIndex][rhsIndex] = 0;
}



int main(void)
{
	cache.assign(101, vector<int>(101, -1));

	/*
	string lhs = "he*p";
	string rhs = "heap";
	*/		
	
	string lhs = "t*l?*o*r?ng*s";
	string rhs = "thelordoftherings";	
	
	/*
	string lhs = "a*a";
	string rhs = "aaaaaaaaab";
	*/

	RPerm(lhs,rhs,0,0);
	if(isFind)
	{
		cout<<"Equal"<<endl;		
	}
	else
	{
		cout<<"fail"<<endl;
	}

}
