#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
vector<int> v;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	//freopen("input.txt", "r", stdin);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		v.push_back(n);
	}

	// 오름차순 정렬
	sort(v.begin(), v.end());

	// two pointer
	int left = 0;
	int right = N - 1;
	// 최소일 때 갱신하면서 기록
	long long minval = 9999999999999999;
	int a = 0, b = 0;
	while (left < right) {
		// 두 용액의 합
		long long sum = v[left] + v[right];
		// 0에 가까운 값을 찾아야 하므로 절댓값 **
		if (abs(sum) < minval) {
			minval = abs(sum);
			a = v[left];
			b = v[right];
		}

		// 합이 0보다 작으면 left 이동
		if (sum < 0)
			left++;
		else if (sum > 0)
			right--;
		else // 합이 0이면 더이상 볼 필요 X
			break;
	}

	cout << a << " " << b;

	return 0;
}