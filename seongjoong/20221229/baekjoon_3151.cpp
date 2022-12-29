#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
int arr[10000];
long long ans;

int comb(int N) {
	return N * (N - 1) / 2;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> arr[i];

	sort(arr, arr + N);

	// 하나를 고정시켜놓고, 나머지 2개 two pointer -> O(N) * O(N)
	for (int i = 0; i < N - 2; i++) {
		int tar = -arr[i];

		int left = i + 1;
		int right = N - 1;

		while (left < right) {
			int now = arr[left] + arr[right];

			if (now == tar) {
				// 중복되는 숫자 확인
				int A = arr[left];
				int B = arr[right];

				// 두 수가 같으면 개수 중에서 2개 뽑기 -> 조합
				if (A == B) {
					ans += comb(right - left + 1);
					break;
				}
				else {
					int cntA = 0;
					int cntB = 0;
					while (arr[left] == A) {
						cntA++;
						left++;
					}
					while (arr[right] == B) {
						cntB++;
						right--;
					}

					ans += cntA * cntB;
				}
			}
			else if (now < tar)
				left++;
			else
				right--;
		}
	}

	cout << ans;

	return 0;
}
