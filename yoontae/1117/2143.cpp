#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long T, n, m;
long long arrA[1001];
long long sumA[1001];
long long arrB[1001];
long long sumB[1001];
vector<long long> subtotalA;
vector<long long> subtotalB;

void input() {
	cin >> T;
	cin >> n;
	long long sum = 0;
	for (long long i = 0; i < n; i++) {
		cin >> arrA[i];
		sum += arrA[i];
		sumA[i] = sum;
	}

	sum = 0;
	cin >> m;
	for (long long i = 0; i < m; i++) {
		cin >> arrB[i];
		sum += arrB[i];
		sumB[i] = sum;
	}
}

void solve() {
	long long left = 0;
	long long right = n - 1;

	long long sum = 0;
	long long ans = 0;

	for (left = -1; left < n - 1; left++) {
		for (right = left + 1; right < n; right++) {

			long long a = 0;

			if (left == -1) {
				a = sumA[right];
			}
			else {
				a = sumA[right] - sumA[left];
			}
			
			subtotalA.push_back(a);
		}
	}

	for (left = -1; left < m - 1; left++) {
		for (right = left + 1; right < m; right++) {

			long long b = 0;

			if (left == -1) {
				b = sumB[right];
			}
			else {
				b = sumB[right] - sumB[left];
			}

			subtotalB.push_back(b);
		}
	}

	sort(subtotalA.begin(), subtotalA.end());
	sort(subtotalB.begin(), subtotalB.end());

	left = 0;
	right = (long long)(subtotalB.size() - 1);

	while (left < (long long)(subtotalA.size()) && right >= 0) {
		if (subtotalA[left] + subtotalB[right] > T)
			right--;

		else if (subtotalA[left] + subtotalB[right] < T)
			left++;

		else if (subtotalA[left] + subtotalB[right] == T) {
			long long a = subtotalA[left];
			long long cntA = 0;
			while (subtotalA[left] == a) {
				left++;
				cntA++;
				if (left == (long long)(subtotalA.size()))
					break;
			}

			long long b = subtotalB[right];
			long long cntB = 0;
			while (subtotalB[right] == b) {
				right--;
				cntB++;
				if (right < 0)
					break;
			}

			ans += cntA * cntB;
			right++;
		}
	}

	cout << ans;
}

int main() {
	input();
	solve();

	return 0;
}