#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int T;
int value;

int check[20];
int arr[10];
int brr[10];
int cnt;

int agsum, bgsum;

long long test = 0;
void dfs(int size, int asum, int bsum) {
	if (size == 9) {
		if (asum > bsum) cnt++;
		return;
	}
	

	int nsum, prev, pagsum, pbgsum;
	pagsum = agsum;
	pbgsum = bgsum;

	for (int i = 0; i < 9; ++i) {
		if (brr[i] != 0) {
			nsum = arr[size] + brr[i];
			prev = brr[i];
			agsum -= arr[size];
			bgsum -= brr[i];
			if (arr[size] > brr[i]) {
				brr[i] = 0;
				dfs(size + 1, asum + nsum, bsum);
			}
			else {
				brr[i] = 0;
				dfs(size + 1, asum, bsum + nsum);
			}
			brr[i] = prev;
			agsum = pagsum;
			bgsum = pbgsum;
		}
	}
	
}

int main(void) {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> T;
	for (int ab = 1; ab <= T; ++ab) {
		for (int i = 0; i < 9; ++i) arr[i] = brr[i] = 0;
		for (int i = 1; i <= 18; ++i) check[i] = 0;
		for (int i = 0; i < 9; ++i) {
			cin >> arr[i];
			check[arr[i]]--;
			agsum += arr[i];
		}

		int id = 0;
		for (int i = 1; i <= 18; ++i) {
			if (check[i] == 0) brr[id++] = i;
			bgsum += i;
		}

		dfs(0, 0, 0);
		cout << "#" << ab << " " << cnt << " " << 362880 - cnt << endl;
		cnt = 0;
	}
}
