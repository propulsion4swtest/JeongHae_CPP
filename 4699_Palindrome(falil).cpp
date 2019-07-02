#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

class Memo
{
public:
	int buy;
	int sell;

	Memo(int buy_, int sell_) : buy(buy_), sell(sell_)
	{	}

	Memo() : Memo(-1, -1)
	{	}
};

class Node
{
public:
	string str;
	int index;
	int score;

	Node(string str_, int index_, int score_) : str(str_), index(index_), score(score_)
	{	}

	Node() : Node("", -1, -1)
	{	}
};


class Key
{
public:
	string str;
	int score;

	Key(string str_, int score_) : str(str_), score(score_)
	{	}

	Key() : Key("", -1)
	{	}

	//operator

};


int L, K;
string str;
vector<Memo> memos;



int minValue = 1999999999;
set<Key> sets;

bool IsPalindrome(string &rhs)
{
	int left = 0;
	int right = rhs.size() - 1;

	int size = rhs.size() / 2;

	for (int i = 0; i < size; left++, right--, i++)
	{
		if (rhs[left] != rhs[right])
			return false;
	}

	return true;
}

void BFS()
{
	queue<Node> qu;
	qu.push(Node(str, 0, 0));
	Node node;
	Node nextNode;

	while (!qu.empty())
	{
		node = qu.front();
		qu.pop();

		if (node.score > minValue)
			continue;

		if (IsPalindrome(node.str))
		{
			//cout << node.str << " " << node.score << endl;
			minValue = min(minValue, node.score);
			continue;
		}

		//추가
		for (int i = 0; i < K; i++)
		{
			nextNode = node;

			nextNode.str.insert(nextNode.str.begin() + nextNode.index, 'a' + i);
			nextNode.score += memos[i].buy;

			if (nextNode.score > minValue)
				continue;

			if (IsPalindrome(nextNode.str))
			{
				//cout << nextNode.str << " " << nextNode.score << endl;
				minValue = min(minValue, nextNode.score);
				continue;
			}

			qu.push(nextNode);
		}

		//삭제

		nextNode = node;

		if (nextNode.index < nextNode.str.size())
		{
			char tmp = nextNode.str[nextNode.index];
			nextNode.score += memos[tmp - 'a'].sell;
			nextNode.str.erase(nextNode.str.begin() + nextNode.index);		

			if (IsPalindrome(nextNode.str))
			{
				//cout << nextNode.str << " " << nextNode.score << endl;
				minValue = min(minValue, nextNode.score);
			}

			if (nextNode.score <= minValue)
				qu.push(nextNode);


			//넘기기(index 추가)
			nextNode = node;
			nextNode.index++;

			if (nextNode.index < nextNode.str.size())
				qu.push(nextNode);
		}
	}
}


int main(void)
{	
	
	int T;
	cin >> T;

	for (int testCase = 0; testCase < T; testCase++)
	{
		memos.clear();

		cin >> L >> K;
		cin >> str;

		int buy, sell;
		for (int i = 0; i < K; i++)
		{
			cin >> buy >> sell;
			memos.push_back(Memo(buy, sell));
		}

		BFS();
		cout << "#" << testCase + 1 << " " << minValue << endl;;

	}
	

	
	/*
	string str = "abcddcbz";
	if (IsPalindrome(str))
		cout << "true" << endl;	
	else
		cout << "false" << endl;
	*/

	/*
	string str = "abcdef";

	str.erase(str.begin() + 3);
	
	cout << str;
	*/

	/*
	string str = "abcdef";

	str.insert(str.begin() + 3, 'x');

	cout << str;
	*/


	/*
	set<string> set1;

	set1.insert("zzz");

	set<string>::iterator it = set1.find("aaa");


	if (it == set1.end())
		cout << "error" << endl;
	else
		cout << "success" << endl;
	*/
	return 0;
}
