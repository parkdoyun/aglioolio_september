#include <iostream>
#include <vector>
using namespace std;

struct Coord {
	int y, x;
};

int N, M;
int MAP[50][50];
vector<Coord> house;
vector<Coord> chicken;
int choose[13];
int ans = 2134567890;

int getDist(Coord a, Coord b) {
	return abs(a.y - b.y) + abs(a.x - b.x);
}

void cal() {
	int sum = 0;
	for (int i = 0; i < house.size(); i++) {
		int minDist = 2134567890;
		for (int j = 0; j < chicken.size(); j++) {
			if (choose[j] == 0)
				continue;
			int dist = getDist(house[i], chicken[j]);
			if (dist < minDist)
				minDist = dist;
		}
		sum += minDist;
	}

	if (sum < ans)
		ans = sum;
}

void dfs(int now, int cnt) {
	// M개가 정해졌으면 거리 갱신
	if (cnt == M) {
		cal();
		return;
	}

	if (now == chicken.size())
		return;

	// now 유지
	choose[now] = 1;
	dfs(now + 1, cnt + 1);
	choose[now] = 0;

	// now 폐업
	dfs(now + 1, cnt);
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1)
				house.push_back({ i,j });
			if (MAP[i][j] == 2)
				chicken.push_back({ i,j });
		}
	}

	// 살릴 치킨 집 고르기
	dfs(0, 0);

	cout << ans;

	return 0;
}
