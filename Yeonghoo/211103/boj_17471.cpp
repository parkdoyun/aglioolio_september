/* Category : DFS, BFS, BruteForce
* Solving time : 1h 45min
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

//1. 각 선거구는 적어도 한 구역을 가지고 있어야 함
//2. 한 선거구는 모두 연결되어 있어야 함
//연결되어 있음 : 구역 A에서 인접 구역을 통해서 구역 B로 갈 수 있을 때(모두 같은 선거구)
using namespace std;

int N;
int popu[10];

vector<int> graph[10];

int answer = 2123456789;
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> popu[i];
	}

	for (int i = 0; i < N; i++) {
		int cnt;
		cin >> cnt;

		for (int j = 0; j < cnt; j++) {
			int to;
			cin >> to;
			graph[i].push_back(to-1);
		}
	}
}
vector<int> path;
int visited[10] = { 0, };

//두 선거구 색깔 칠해보기 (파란색 0, 빨간색1)
int groupColor[10];
//BFS visited
bool BFS(vector<int> g1, int color) {
	queue<int> q;
	int start = g1.at(0);

	int bfsVisited[10] = { 0, };

	q.push(start);
	bfsVisited[start] = 1;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		for (int i = 0; i < graph[now].size(); i++) {
			if (groupColor[graph[now].at(i)] != color)
				continue;
			if (bfsVisited[graph[now][i]] == 1)
				continue;

			bfsVisited[graph[now][i]] = 1;
			q.push(graph[now][i]);
		}
	}

	//bfsVisited와 p를 비교해봤을 때 다르면 선거구 만족 X

	bool flag = true;
	for (int i = 0; i < g1.size(); i++) {
		if (bfsVisited[g1.at(i)] == 0) {
			flag = false;
			break;
		}
	}

	return flag;




}


//정해진 선거구가 조건 만족?
bool isSatisfy(vector<int> p) {
	memset(groupColor, 0, 10*sizeof(int));
	//1. 각 선거구는 적어도 한 구역을 가지고 있어야 함
	if (p.size() == 0 || p.size() == N)
		return false;
	//2. 한 선거구는 모두 연결되어 있어야 함
	//색깔 칠해보기 p는 1, ap는 0
	for (int i = 0; i < p.size(); i++) {
		groupColor[p.at(i)] = 1;
	}
	//다른 선거구 ap
	vector<int> ap;
	for (int i = 0; i < N; i++) {
		if (groupColor[i] == 0)
			ap.push_back(i);
	}
	//BFS
	bool pSatisfy = BFS(p, 1);
	bool apSatisfy = BFS(ap, 0);

	//두 그룹 모두 선거구 만족!
	if (pSatisfy && apSatisfy)
		return true;
	else
		return false;
	
//연결되어 있음 : 구역 A에서 인접 구역을 통해서 구역 B로 갈 수 있을 때(모두 같은 선거구)

}

int getDiff() {
	int pop1 = 0;
	int pop2 = 0;

	for (int i = 0; i < N; i++) {
		if (groupColor[i] == 1)
			pop1 += popu[i];
		else if (groupColor[i] == 0)
			pop2 += popu[i];
	}

	return abs(pop1 - pop2);
}

void dfs(int idx, int depth, int r) {
	if (depth >= r) {
		/*
		for (int i = 0; i < r; i++) {
			cout << path.at(i) << " ";
		}
		cout << endl;
		*/
		//색깔 칠한거 초기화;
		//각각 뽑아본 선거구에 대해서 조건을 만족하는지 확인한다.
		bool result = isSatisfy(path);

		// 인구 차이 구하고 갱신
		//선거구 조건 만족하면
		if (result) {
			int diff = getDiff();

			if (diff < answer)
				answer = diff;
		}
		return;
	}

	for (int i = idx; i < N; i++) {
		if (visited[i] == 1)
			continue;
		visited[i] = 1;
		path.push_back(i);
		dfs(i + 1, depth + 1, r);
		path.pop_back();
		visited[i] = 0;
	}
}

int main() {
	input();
	for (int i = 1; i <= N; i++) {
		dfs(0, 0, i);
	}

	if (answer == 2123456789)
		cout << -1;
	else
		cout << answer;
}
