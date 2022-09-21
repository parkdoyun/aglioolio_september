#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, C;
vector<int> house;
int maxi = -2134567890;
int mini = 2134567890;;

void input() {
	cin >> N >> C;

	for (int i = 0; i < N; i++) {
		int h;
		cin >> h;
		maxi = max(maxi, h);
		mini = min(mini, h);
		house.push_back(h);
	}
}

void solution() {
	sort(house.begin(), house.end());

	int left = 1;
	int right = maxi;
	int ans = 0;

	while (left <= right) {
		int mid = (left + right) / 2;

		int cnt = 1;
		int lastInstalled = house[0];

		for (int i = 1; i < N; i++) {
			if (house[i] - lastInstalled >= mid) {
				cnt++;
				lastInstalled = house[i];
			}
		}

		if (cnt >= C) {
			ans = mid;

			left = mid + 1;
		}
		else
			right = mid - 1;
	}

	cout << ans;
}

int main() {
	input();
	solution();

	return 0;
}