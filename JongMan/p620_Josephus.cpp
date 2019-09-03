#include<iostream>
#include<list>

using namespace std;

list<int> players;
int N, K;

void Solve() {
	players.clear();
	for (int i = 1; i <= N; i++)
		players.push_back(i);

	list<int>::iterator it = players.begin();
	int div;
	while (players.size() > 2)
	{
		it = players.erase(it);

		if (it == players.end())
			it = players.begin();

		div = K % (players.size());

		for (int i = 0; i < K - 1; i++) {
			it++;

			if (it == players.end())
				it = players.begin();
		}
	}
}

int main(void) {
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++)
	{
		cin >> N >> K;

		Solve();

		list<int>::iterator it = players.begin();
		cout << *it << " ";
		it++;
		cout << *it << endl;
	}

	return 0;
}
