//2중 for 문까지 돌리면서 3중 for a문 대신 이진탐색 활용해서 조건에 맞는 값 찾기
//반복문과 이진탐색으로 돌려가면서 생기는 중복 경우(index 0, 1, 2   2, 1, 0 등등)
//제외하면서 시간 복잡도를 줄이는 것이 핵심

#include <iostream>
#include <algorithm>

using namespace std;

int N;
int arr[10000];
long cnt = 0;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();

	sort(arr, arr + N);

	for (int i = 0; i < N - 2; i++) {
		for (int j = i + 1; j < N - 1; j++) {
			int total = arr[i] + arr[j];
			int target = 0 - total;

			//이진탐색(== target)
			int lb = lower_bound(arr + (j + 1), arr + N, target) - arr;
			int ub = upper_bound(arr + (j + 1), arr + N, target) - arr;

			cnt += ub - lb;
		}
	}
	cout << cnt;
}
