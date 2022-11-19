#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
int number[11];
vector<int> Area[11];
vector<int> path; // 선거구 1
vector<int> path2; // 선거구 2
int visited[11];
int minDiff = 2134567890;
bool isConnected( int node, int len, int flag ) {

	if (len == 0 || len == n) return false;

	int cnt;
	queue<int> q;
	q.push(node);
	int checked[11] = { 0 };

	cnt = 1;
	checked[node] = 1;

	while (!q.empty()) {
		int item = q.front();
		q.pop();

		for (int i = 0; i < Area[item].size(); i++) {
			int now = Area[item][i];
			if (checked[now] == 0 && visited[now] == flag) {
				cnt += 1;
				q.push(now);
				checked[now] = 1;
			}
		}
		
	}

	if (cnt == len) return true;
	return false;
	
}

void dfs(int level, int num) {

	if (level>n) {
		
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 0) {
				path2.push_back(i);
			}
		}
		
		bool check;
		bool check2;

		if (path.size() == 0 || path.size() == n) check = false;
		else {
			check = isConnected(path[0], path.size(), 1);
		}

		if (path2.size() == 0 || path2.size() == n) check2 = false;
		else {
			check2 = isConnected(path2[0], path2.size(), 0);
		}

		if (check == true && check2 == true) {

			int num2 = 0;
			for (int i = 0; i < path2.size(); i++) {
				num2 += number[path2[i]];
			}

			int diff = abs(num - num2);
			if (minDiff > diff) minDiff = diff;
		}

		path2.clear();

		return;
	}

	path.push_back(level);
	visited[level] = 1;
	dfs(level + 1, num + number[level]);
	visited[level] = 0;
	path.pop_back();

	dfs(level + 1, num);
}

int main() {

	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> number[i];
	}

	for (int i = 1; i <= n; i++) {
		int num;
		cin >> num;
		for (int j = 0; j < num; j++) {
			int node;
			cin >> node;

			Area[i].push_back(node);
		}
	}

	dfs(1, 0);
	if (minDiff == 2134567890) minDiff = -1;
	cout << minDiff;

	return 0;
}