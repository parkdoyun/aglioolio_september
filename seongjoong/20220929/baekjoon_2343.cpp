#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int arr[1000000];
int maxval;
int total;

int record(int mid) {
	int cnt = 0;
	int sum = 0;
	for (int i = 0; i < N; i++) {
		sum += arr[i];
		if (sum > mid) {
			cnt++;
			sum = arr[i];
		}
		else if (sum == mid) {
			cnt++;
			sum = 0;
		}
	}

	if (sum > 0)
		cnt++;

	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		if (arr[i] > maxval)
			maxval = arr[i];
		total += arr[i];
	}

	int ans = 0;
	// Parametric Search
	int left = maxval;
	int right = total;
	while (left <= right) {
		int mid = (left + right) / 2;
		// mid를 최대 합으로 묶어보기
		int cnt = record(mid);

		if (cnt <= M) {
			right = mid - 1;
			ans = mid;
		}
		else {
			left = mid + 1;
		}
	}

	cout << ans;

	return 0;
}
