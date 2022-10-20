#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int arr[50];
vector<int> v;

bool cmp(int a, int b) {
	if (a > b) return true;
	if (a < b) return false;
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	cin >> M;
	for (int i = 0; i < M; i++) {
		int n;
		cin >> n;
		v.push_back(n);
	}

	// 내림차순 정렬
	sort(arr, arr + N, cmp);
	sort(v.begin(), v.end(), cmp);

	// 가장 무거운 박스가 최대 무게 제한을 넘으면 -1
	if (v[0] > arr[0]) {
		cout << -1;
		return 0;
	}

	int ans = 0;
	while (!v.empty()) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < v.size(); j++) {
				if (arr[i] >= v[j]) {
					v.erase(v.begin() + j);
					break;
				}
			}
		}
		ans++;
	}

	cout << ans;

	return 0;
}
