#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int y;
	int x;
};

int n, m;
int MAP[51][51];
vector<Node> chicken;
vector<Node> house;

vector<int> path;
int minDist = 2134567890;
void dfs(int level, int cnt) {

	if (cnt > m) return;

	if (chicken.size() <= level) {

		// 치킨거리 계산
		int chicken_dist = 0;
		for (int i = 0; i < house.size(); i++) {
			int my_dist = 2134567890;
			for (int j = 0; j < path.size(); j++) {
				int dist = abs((chicken[path[j]].y - house[i].y)) + abs((chicken[path[j]].x - house[i].x));

				if (my_dist > dist) my_dist = dist;
			}
			chicken_dist += my_dist;
		}

		if (path.size() == 0) chicken_dist = 2134567890;  // 오버플로우 방지
		if (minDist > chicken_dist) minDist = chicken_dist;

		return;
	}

	path.push_back(level);
	dfs(level + 1, cnt + 1);
	path.pop_back();

	dfs(level + 1, cnt);

}

int main() {

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) house.push_back({ i, j });
			else if (MAP[i][j] == 2) chicken.push_back({ i, j });
		}
	}

	dfs(0, 0);

	cout << minDist;
	
	return 0;
}
