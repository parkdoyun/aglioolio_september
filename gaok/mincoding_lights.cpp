#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, k;
vector<int> lights;
vector<int> lights_copy;
vector<int> info[18];
vector<int> path;

int minCnt = 2134567890;
void dfs(int level, int cnt) {

	if (level >= m) {

		for (int i = 0; i < path.size(); i++) {
			for (int j = 0; j < info[path[i]].size(); j++) {
				int light = info[path[i]][j];
				if (lights[light] == 0) lights[light] = 1;
				else if (lights[light] == 1) lights[light] = 0;
			}
		}

		int flag = 0;
		for (int i = 0; i < lights.size(); i++) {
			if (lights[i] == 0) {
				flag = 1;
				break;
			}
		}

		if (flag == 0) {
			minCnt = min(minCnt, cnt);
		}

		// 복구
		for (int i = 0; i < lights.size(); i++) {
			lights[i] = lights_copy[i];
		}

		return;
	}

	path.push_back(level);
	dfs(level + 1, cnt + 1);
	path.pop_back();

	dfs(level + 1, cnt);
}

int main() {

	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		int light;
		cin >> light;
		lights.push_back(light);
		lights_copy.push_back(light);
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			int num;
			cin >> num;
			info[i].push_back(num-1);
		}
	}

	dfs(0, 0);

	if (minCnt == 2134567890) cout << -1 << "\n";
	else cout << minCnt << "\n";

	return 0;
}
