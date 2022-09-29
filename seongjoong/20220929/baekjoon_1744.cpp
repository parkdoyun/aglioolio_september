#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int a, int b) {
	if (a > b) return true;
	if (a < b) return false;
	return false;
}

int N;
vector<int> pos; // 양수
vector<int> neg; // 음수
int zero; // 0의 개수

int ans;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N;
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		if (n < 0)
			neg.push_back(n);
		else if (n == 0)
			zero++;
		else
			pos.push_back(n);
	}

	// 최대가 되려면 큰 수끼리 곱해야 함 -> 내림차순 정렬
	// 음수 -> 음수끼리 곱해서 양수로 만들거나 0과 곱해서 없애버리기

	sort(pos.begin(), pos.end(), cmp);
	sort(neg.begin(), neg.end());

	for (int i = 0; i < pos.size(); i += 2) {
		// 원소 개수가 홀수이면
		if (i + 1 == pos.size()) {
			ans += pos[i];
			break;
		}
		// 두 수의 곱이 합보다 크면
		if (pos[i] * pos[i + 1] > pos[i] + pos[i + 1])
			ans += pos[i] * pos[i + 1];
		else
			ans += pos[i] + pos[i + 1];
	}

	for (int i = 0; i < neg.size(); i += 2) {
		if (i + 1 == neg.size()) {
			// 0이 있으면 0을 곱해준다.
			if (zero > 0)
				continue;
			ans += neg[i];
			break;
		}
		ans += neg[i] * neg[i + 1];
	}

	cout << ans;

	return 0;
}
