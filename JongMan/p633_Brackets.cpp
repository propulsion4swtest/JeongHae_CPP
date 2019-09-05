#include<iostream>
#include<stack>
#include<string>

using namespace std;

string str;


int Char2Int(char bracket) {
	if (bracket == '(' || bracket == ')')
		return 1;
	else if (bracket == '{' || bracket == '}')
		return 2;
	else if (bracket == '[' || bracket == ']')
		return 3;
}

bool CheckClose(char bracket) {
	if (bracket == ')' || bracket == '}' || bracket == ']')
		return true;
	else
		return false;
}

bool Solve() {
	stack<int> brackets;

	for (int i = 0; i < str.size(); i++) {
		int value = Char2Int(str[i]);
		bool isClose = CheckClose(str[i]);

		if (isClose == false)
			brackets.push(value);
		else if (isClose == true && brackets.empty())
			return false;
		else if (isClose == true && !brackets.empty() && brackets.top() == value)
			brackets.pop();
		else if (isClose == true && !brackets.empty() && brackets.top() != value)
			return false;
	
	}

	if (brackets.empty())
		return true;
	else
		return false;
}


int main(void) {
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++) {
		cin >> str;

		bool ret = Solve();
		if (ret == true)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
