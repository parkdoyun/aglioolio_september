#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

int T;
int K;
priority_queue<long long, vector<long long>, greater<long long>> pq;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// init
		while (!pq.empty())
			pq.pop();

		cin >> K;
		for (int i = 0; i < K; i++) {
			int n;
			cin >> n;
			pq.push(n);
		}

		long long ans = 0;
		while (pq.size() > 1) {
			// 가장 작은 두 파일 합치기
			long long temp = 0;
			temp += pq.top();
			pq.pop();
			temp += pq.top();
			pq.pop();

			ans += temp;
			pq.push(temp);
		}

		cout << ans << '\n';
	}

	return 0;
}
