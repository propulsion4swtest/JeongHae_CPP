#include<iostream>
#include<queue>

using namespace std;

class RNG {
public:
	unsigned signal;

	RNG() : signal(1983u) {}
	unsigned next() {
		unsigned ret = signal;
		signal = (signal * 214013u + 2531011u);

		ret = ret % 10000 + 1;
		return ret;
	}
};

int Solve(unsigned N, unsigned K) {
	int answer = 0;
	int sum = 0;
	RNG rng;
	queue<int> qu;
	for (int i = 0; i < K; i++) {
		int signal = rng.next();

		sum += signal;

		qu.push(signal);
		while (sum > N) {
			sum -= qu.front();
			qu.pop();
		}
		if (sum == N)
			answer += 1;
	}

	return answer;
}


int main() {
	int C;
	cin >> C;

	for (int i = 0; i < C; i++) {
		unsigned N, K;
		cin >> N >> K;
		cout << Solve(N, K) << endl;
	}
	return 0;
}

