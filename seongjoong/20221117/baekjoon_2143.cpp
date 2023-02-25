#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T;
int N, M;
int a[1000];
int b[1000];
long long ans;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T >> N;
	for (int i = 0; i < N; i++)
		cin >> a[i];
	cin >> M;
	for (int i = 0; i < M; i++)
		cin >> b[i];

	// a의 모든 부분합 저장
	vector<int> sumA;
	for (int i = 0; i < N; i++) {
		int sum = 0;
		for (int j = i; j < N; j++) {
			sum += a[j];
			sumA.push_back(sum);
		}
	}
	// b의 모든 부분합 저장
	vector<int> sumB;
	for (int i = 0; i < M; i++) {
		int sum = 0;
		for (int j = i; j < M; j++) {
			sum += b[j];
			sumB.push_back(sum);
		}
	}

	// 정렬
	sort(sumA.begin(), sumA.end());
	sort(sumB.begin(), sumB.end());

	// Two Pointer -> A의 최소 부분합, B의 최대 부분합부터 탐색.
	int left = 0;
	int right = sumB.size() - 1;
	while (left < sumA.size() && right >= 0) {
		int sum = sumA[left] + sumB[right];
		if (sum == T) {
			// 같은 부분합을 가진 서로 다른 부분수열 모두 확인
			long long cntA = 1;
			long long cntB = 1;
			while (1) {
				if (left == sumA.size() - 1)
					break;
				if (sumA[left] == sumA[left + 1]) {
					cntA++;
					left++;
				}
				else break;
			}
			while (1) {
				if (right == 0)
					break;
				if (sumB[right] == sumB[right - 1]) {
					cntB++;
					right--;
				}
				else break;
			}
			ans += cntA * cntB;

			// 둘 중 아무거나 한칸 이동
			left++;
		}
		else if (sum > T)
			right--;
		else
			left++;
	}

	cout << ans;

	return 0;
}

================================================================

// unordere_map 이용한  풀이

#include <iostream>
#include <unordered_map>
using namespace std;

int T;
int N, M;
int a[1000];
int b[1000];
long long ans;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T >> N;
	for (int i = 0; i < N; i++)
		cin >> a[i];
	cin >> M;
	for (int i = 0; i < M; i++)
		cin >> b[i];

	// a의 모든 부분합 저장
	unordered_map<int, long long> um;
	for (int i = 0; i < N; i++) {
		int sum = 0;
		for (int j = i; j < N; j++) {
			sum += a[j];
			um[sum]++;
		}
	}

	// b의 모든 부분합 확인
	for (int i = 0; i < M; i++) {
		int sum = 0;
		for (int j = i; j < M; j++) {
			sum += b[j];
			ans += um[T - sum];
		}
	}

	cout << ans;

	return 0;
}
