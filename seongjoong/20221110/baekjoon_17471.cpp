#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
int arr[11];
vector<int> v[11];
int team[11];
int checked[11];
int ans = 2134567890;

// 나눈 팀끼리 연결되어 있는지 확인
// -> 임의의 한 점에서 시작하여 연결된 모든 점에 팀 번호 기록
void bfs(int n) {
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (team[i] == n) {
            q.push(i);
            checked[i] = n;
            break;
        }
    }

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < v[now].size(); i++) {
            int next = v[now][i];
            if (team[next] != n)
                continue;
            if (checked[next] == n)
                continue;
            checked[next] = n;
            q.push(next);
        }
    }
}

// 가능한 방법인지 확인
bool check() {
    memset(checked, 0, sizeof(checked));

    bfs(1);
    bfs(2);

    for (int i = 1; i <= N; i++){
        if (checked[i] == 0)
            return false;
    }

    return true;
}

void cal() {
    int a = 0;
    int b = 0;
    for (int i = 1; i <= N; i++) {
        if (team[i] == 1)
            a += arr[i];
        else
            b += arr[i];
    }

    ans = min(ans, abs(a - b));
}

void dfs(int now) {
    if (now == N + 1) {
        // 가능하면 인구수 차이 계산
        if (check() == true)
            cal();
        return;
    }

    // now를 첫번째 선거구에 넣기
    team[now] = 1;
    dfs(now + 1);

    // 두번째 선거구에 넣기
    team[now] = 2;
    dfs(now + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> arr[i];
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        for (int j = 0; j < n; j++) {
            int k;
            cin >> k;
            v[i].push_back(k);
        }
    }

    dfs(1);

    if (ans == 2134567890)
        ans = -1;
    cout << ans;

    return 0;
}
