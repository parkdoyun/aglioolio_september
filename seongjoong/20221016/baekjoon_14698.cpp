#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

#define div 1000000007

int T;
int N;
priority_queue<long long, vector<long long>, greater<long long>> pq;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		while (!pq.empty())
			pq.pop();

		cin >> N;
		for (int i = 0; i < N; i++) {
			long long n;
			cin >> n;
			pq.push(n);
		}

		long long ans = 1;
		while (pq.size() > 1) {
			long long a = pq.top();
			pq.pop();
			long long b = pq.top();
			pq.pop();

			long long temp = a * b;
			pq.push(temp);
			temp %= div;
			ans *= temp;
			ans %= div;
		}

		cout << ans << '\n';
	}

	return 0;
}
