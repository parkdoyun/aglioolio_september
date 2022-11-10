#include <iostream>
#include <vector>

using namespace std;

struct Info {
	int p, f, s, v, c;
};

int N;
Info m;
vector<Info> v;
vector<int> path;
int min_cost;
vector<int> min_path;

bool isValid(Info cur) {
	if (m.p > cur.p)
		return false;
	if (m.f > cur.f)
		return false;
	if (m.s > cur.s)
		return false;
	if (m.v > cur.v)
		return false;
	return true;
}

void dfs(Info cur, int now_id) {
	// base case
	if (min_cost <= cur.c)
		// 이미 만족하는 경우가 있는데, 이때의 최소비용보다 크면 return
		return;
	if (isValid(cur)) {
		// 지금까지의 누적 선택이 유효하면, 더 선택할 필요 없다.
		// 최소 비용보다 작은 경우이므로 갱신한다.
		min_cost = cur.c;
		min_path = path;
		return;
	}
	// recursive case
	for (int i = now_id; i < N; i++) {
		// 뽑기 시작해야할 id부터 선택하기
		// 지금까지 누적 계산한것에 선택한 식재료 정보 next에 누적
		// 다음에 뽑을 것은 지금 뽑은 것 다음부터
		Info next = cur;
		next.p += v[i].p;
		next.f += v[i].f;
		next.s += v[i].s;
		next.v += v[i].v;
		next.c += v[i].c;
		path.push_back(i);
		dfs(next, i + 1);
		path.pop_back();
	}
}

void solution() {
	dfs({}, 0);
	if (min_cost == 2147483647) {
		cout << -1;
		return;
	}
	cout << min_cost << "\n";
	for (int i = 0; i < min_path.size(); i++) {
		cout << min_path[i] + 1 << " ";
	}
}

void input() {
	min_cost = 2147483647;

	cin >> N;
	cin >> m.p >> m.f >> m.s >> m.v;
	for (int i = 0; i < N; i++) {
		Info t;
		cin >> t.p >> t.f >> t.s >> t.v >> t.c;
		v.push_back(t);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	input();
	solution();

	return 0;
}

/*
식재료 N 개중 선택
영양분 일정 이상 되도록
조건 만족시키면서 비용 최소
최저 영양소 기준 만족하는 최소 비용

*/
