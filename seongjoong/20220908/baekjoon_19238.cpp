#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Coord {
    int y, x;
};

struct Pass {
    int y, x, dist;
};

bool operator<(Pass a, Pass b) {
    // 거리 짧은 순 -> MINHEAP --> false
    if (a.dist < b.dist) return false;
    if (a.dist > b.dist) return true;
    // 행 번호 작은 순
    if (a.y < b.y) return false;
    if (a.y > b.y) return true;
    // 열 번호 작은 순
    if (a.x < b.x) return false;
    if (a.x > b.x) return true;
    return false;
}

int N, M, fuel;
int MAP[21][21];
int Y, X; // 택시 시작점
Coord des[21][21]; // 해당 좌표에 있는 승객의 목적지 저장

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

Pass findPassenger(int y, int x) {
    // *** 문제 조건 ***
    // 택시와 승객이 같은 위치에 서 있으면 그 승객까지의 최단거리는 0이다.
    // --> 택시 시작점 or 이전 승객의 목적지에 다음 승객이 있을 수 있다!
    // bfs를 돌리면 해당 경우를 따지지 못한다.

    // 현재 택시 위치에 승객이 있다면
    if (des[y][x].y != 0 && des[y][x].x != 0)
        return { y,x,0 };

    queue<Coord> q;
    q.push({ y,x });

    int visited[21][21] = { 0 };
    visited[y][x] = 1;

    priority_queue<Pass> pq; // 승객을 우선순위에 맞게 기록
    while (!q.empty()) {
        Coord now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];
            if (ny < 1 || nx < 1 || ny > N || nx > N)
                continue;
            if (visited[ny][nx])
                continue;
            // 벽이면 패스
            if (MAP[ny][nx] == 1)
                continue;
            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ ny, nx });
            // 승객을 찾았으면 기록
            if (des[ny][nx].y != 0 && des[ny][nx].x != 0)
                pq.push({ ny,nx,visited[ny][nx] - 1 });
        }
    }
    // 태울 수 있는 승객이 없으면
    if (pq.empty())
        return { -1,-1,-1 };
    else {
        // 이번에 태울 승객
        return pq.top();
    }
}

int taxiRide(int sy, int sx, int ey, int ex) {
    queue<Coord> q;
    q.push({ sy,sx });

    int visited[21][21] = { 0 };
    visited[sy][sx] = 1;

    while (!q.empty()) {
        Coord now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];
            if (ny<1 || nx<1 || ny>N || nx>N)
                continue;
            if (visited[ny][nx])
                continue;
            if (MAP[ny][nx] == 1)
                continue;
            visited[ny][nx] = visited[now.y][now.x] + 1;
            // 목적지를 찾았으면 종료
            if (ny == ey && nx == ex)
                return visited[ny][nx] - 1;

            q.push({ ny,nx });
        }
    }
    // 목적지까지 가는 방법이 없다면
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> N >> M >> fuel;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> MAP[i][j];
    cin >> Y >> X;
    for (int i = 0; i < M; i++) {
        int sy, sx, ey, ex;
        cin >> sy >> sx >> ey >> ex;
        des[sy][sx] = { ey,ex };
    }

    // 승객 M명만큼 반복
    for (int i = 0; i < M; i++) {
        // 현재 택시 위치 -> 가장 가까운 승객 찾기
        Pass now = findPassenger(Y, X);
        if (now.dist == -1) {
            cout << -1;
            return 0;
        }
        // 승객 태우러 간 거리만큼 연료 감소
        fuel -= now.dist;
        if (fuel <= 0) {
            cout << -1;
            return 0;
        }
        // 현재 승객의 목적지
        int ey = des[now.y][now.x].y;
        int ex = des[now.y][now.x].x;
        // 승객 목적지까지 데려다주기
        int ret = taxiRide(now.y, now.x, ey, ex);
        if (ret == -1) {
            cout << -1;
            return 0;
        }
        // 승객 탑승 거리만큼 연료 감소
        fuel -= ret;
        // 있는 연료를 딱 다 쓰고 도착한 경우 남은 연료 == 0
        if (fuel < 0) {
            cout << -1;
            return 0;
        }
        // 목적지까지 도달했다면 연료 충전
        fuel += (ret * 2);
        // 다음 승객을 찾기 위해 택시 좌표 갱신
        Y = ey;
        X = ex;
        // 현재 승객은 목적지에 도착했으므로 해당 승객 삭제
        des[now.y][now.x] = { 0,0 };
    }

    cout << fuel;

    return 0;
}
