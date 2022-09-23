#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int T;

int check(string str) {
	int left = 0;
	int right = str.length() - 1;

	int minval = 99999;
	int cnt = 0; // 좌우에서 확인했을 때 다른 문자 개수
	while (left < right) {
		if (str[left] == str[right]) {
			left++;
			right--;
		}
		else {
			// 두 문자가 다른 경우 왼쪽, 오른쪽 지우는 경우 2가지 모두 봐야 한다.
			left++;
			cnt++;
		}

		if (cnt > 1)
			break;
	}
	minval = min(minval, cnt);

	// 다를 경우 right를 이동
	left = 0;
	right = str.length() - 1;
	cnt = 0;
	while (left < right) {
		if (str[left] == str[right]) {
			left++;
			right--;
		}
		else {
			right--;
			cnt++;
		}

		if (cnt > 1)
			break;
	}
	minval = min(minval, cnt);

	return minval;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> T;
	for (int i = 0; i < T; i++) {
		string str;
		cin >> str;

		// 모든 문자를 1개씩 지워보면서 체크하면 시간초과 발생
		// Two Pointer -> 좌우에서 문자 확인하면서 다를 경우 카운트.
		cout << check(str) << '\n';
	}

	return 0;
}
