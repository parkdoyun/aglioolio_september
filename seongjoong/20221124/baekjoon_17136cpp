#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Coord {
    int y, x;
};

int paper[6] = { 0,5,5,5,5,5 };
int MAP[10][10];
vector<Coord> v;
int covered[10][10];
int ans = 2134567890;

bool canCover(int y, int x, int size) {
    for (int i = y; i < y + size; i++) {
        for (int j = x; j < x + size; j++) {
            if (MAP[i][j] == 0)
                return false;
            // ** 색종이가 곂치는가 **
            if (covered[i][j] == 1)
                return false;
        }
    }
    return true;
}

void cover(int y, int x, int size) {
    for (int i = y; i < y + size; i++) {
        for (int j = x; j < x + size; j++) {
            if (covered[i][j] == 0)
                covered[i][j] = 1;
            else
                covered[i][j] = 0;
        }
    }
}

void dfs(int idx, int cnt) {
    if (cnt >= ans)
        return;

    // ** 여기까지 도달했으면 마지막 1까지 다 붙인 것 **
    // -> 종이를 못 붙이는 경우 중간에 리턴되므로 다 붙였는지 확인할 필요 X
    if (idx == v.size()) {
        ans = cnt;
        return;
    }

    // 현재 좌표가 이미 덮어져 있으면 다음 좌표로
    if (covered[v[idx].y][v[idx].x] == 1)
        dfs(idx + 1, cnt);
    else {
        Coord now = v[idx];
        // 최소 개수 -> 큰 색종이부터 붙이기
        for (int k = 5; k >= 1; k--) {
            // k 사이즈 색종이를 다 썼으면 패스
            if (paper[k] == 0)
                continue;
            // 붙이려는 색종이가 MAP을 벗어나면 패스
            if (now.y + k - 1 >= 10 || now.x + k - 1 >= 10)
                continue;
            if (canCover(now.y, now.x, k) == true) {
                cover(now.y, now.x, k);
                paper[k]--;
                dfs(idx + 1, cnt + 1);
                cover(now.y, now.x, k);
                paper[k]++;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == 1)
                v.push_back({ i,j });
        }
    }

    dfs(0, 0);

    if (ans == 2134567890)
        ans = -1;
    cout << ans;

    return 0;
}
