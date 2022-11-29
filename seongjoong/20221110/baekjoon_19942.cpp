#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int mp, mf, mc, mv;
int arr[16][5]; // 단, 지, 탄, 비, 가격
vector<int> path;
int ans = 2134567890;
vector<int> ansV;

void dfs(int now, int p, int f, int c, int v, int cost) {
	if (p >= mp && f >= mf && c >= mc && v >= mv) {
		if (cost < ans) {
			ans = cost;
			ansV.assign(path.begin(), path.end());
		}
		return;
	}

	// 조합 -> now보다 큰 번호들만 탐색 -> visited 필요 X
	for (int i = now + 1; i <= N; i++) {
		path.push_back(i);
		dfs(i, p + arr[i][0], f + arr[i][1], c + arr[i][2], v + arr[i][3], cost + arr[i][4]);
		path.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	cin >> mp >> mf >> mc >> mv;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < 5; j++)
			cin >> arr[i][j];

	for (int i = 1; i <= N; i++) {
		path.push_back(i);
		dfs(i, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4]);
		path.pop_back();
	}

	if (ans == 2134567890) {
		cout << -1;
		return 0;
	}

	cout << ans << '\n';
	for (int i = 0; i < ansV.size(); i++)
		cout << ansV[i] << " ";

	return 0;
}
