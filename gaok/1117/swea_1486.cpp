#include <iostream>
#include <vector>
using namespace std;

int n, b;
vector<int> Height;
int minHeight = 2134567890;

void dfs(int level, int sum) {

	if (level >= n) {
		if (sum >= b) {
			if (minHeight > sum) minHeight = sum;
		}
		return;
	}

	dfs(level + 1, sum + Height[level]);
	dfs(level + 1, sum);
}

void init() {
	Height.clear();
	minHeight = 2134567890;
}

int main() {

	int t;
	cin >> t;

	for (int testcase = 0; testcase < t; testcase++) {

		cin >> n >> b;

		for (int i = 0; i < n; i++) {
			int h;
			cin >> h;
			Height.push_back(h);
		}

		dfs(0, 0);

		cout << "#"<<testcase+1<<" "<< abs(b-minHeight) << "\n";

		init();
	}

	return 0;
}
