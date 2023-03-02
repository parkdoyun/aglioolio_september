#include <iostream>
using namespace std;

int N, M, H;
int MAP[31][11];

bool test() {
    for (int i = 1; i <= N; i++) {
        int now = i;
        for (int j = 1; j <= H; j++) {
            if (MAP[j][now - 1] == 1)
                now--;
            else if (MAP[j][now] == 1)
                now++;
        }
        if (now != i)
            return false;
    }
    return true;
}

bool canDraw(int y, int x) {
    if (MAP[y][x - 1] == 1 || MAP[y][x + 1] == 1)
        return false;
    return true;
}

void draw(int y, int x, int now, int cnt) {
    if (now == cnt) {
        if (test() == true) {
            cout << cnt;
            exit(0);
        }
        return;
    }

    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= N - 1; j++) {
            if (i < y && j < x)
                continue;
            if (MAP[i][j] == 1)
                continue;
            if (canDraw(i, j) == false)
                continue;
            MAP[i][j] = 1;
            draw(i, j, now + 1, cnt);
            MAP[i][j] = 0;
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> H;
    for (int i = 0; i < M; i++) {
        // b ~ b+1 -> a번 높이에서 연결
        int a, b;
        cin >> a >> b;
        MAP[a][b] = 1;
    }

    // 0 ~ 3개 그려보기
    for (int i = 0; i <= 3; i++)
        draw(1, 1, 0, i);

    cout << -1;

    return 0;
}
