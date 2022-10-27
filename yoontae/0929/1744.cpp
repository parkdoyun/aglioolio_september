#include <iostream>

using namespace std;

typedef long long ll;

ll N, M;
ll arr[1000000];
ll sumarr[1000000];
int cnt[1000];

void input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		if (i == 0)
			sumarr[i] = arr[i];
		else {
			sumarr[i] = sumarr[i - 1] + arr[i];
		}
	}
}

void solution() {
	for (int i = 0; i < N; i++) {
		cnt[sumarr[i] % M]++;
	}

	int ans = 0;

	for (int i = 0; i < M; i++) {
		ans += cnt[i] * (cnt[i] - 1) / 2;
	}

	ans += cnt[0];

	cout << ans;
}

int main() {
	input();
	solution();

	return 0;
}