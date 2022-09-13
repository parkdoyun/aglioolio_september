#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <limits.h>

using namespace std;
using ll = long long;

typedef struct _node{
    int y;
    int x;
}Node;

typedef struct _path{
    Node src; // row, col
    Node dest;
    int to_src; // 택시가 움직일 떄마다 갱신
    int to_dest; // 항상 값이 고정
}Path;

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, -1, 0, 1};

int N, M, F;

void init();
void solve();

int grid[21][21];
int dist[21][21]; // 이게 바뀜

int ty, tx;

vector<Path> paths;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init();
    solve();
    
    return 0;
}

void init(){
    cin >> N >> M >> F;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> grid[i][j];
        }
    }
    cin >> ty >> tx;
    for(int i = 0; i < M; i++){
        int src_y, src_x, dest_y, dest_x;
        cin >> src_y >> src_x >> dest_y >> dest_x;
        paths.push_back({{src_y, src_x}, {dest_y, dest_x}});
    }
}

void bfs(Node start){
    memset(dist, -1, sizeof(dist));
    queue<Node> q;
    q.push(start);
    dist[start.y][start.x] = 0;

    while(!q.empty()){
        Node cur = q.front();
        q.pop();

        for(int k = 0; k < 4; k++){
            int ny = cur.y + dy[k];
            int nx = cur.x + dx[k];

            if(ny <= 0 || nx <= 0 || ny > N || nx > N)
                continue;
            
            if(grid[ny][nx] == 1)
                continue;
            
            if(dist[ny][nx] >= 0)
                continue;

            dist[ny][nx] = dist[cur.y][cur.x] + 1;
            q.push({ny, nx});
        }
    }
}

bool cmp(const Path& l, const Path& r){
    int ly = l.src.y;
    int lx = l.src.x;
    int ry = r.src.y;
    int rx = r.src.x;

    if(l.to_src < r.to_src) return true;
    if(l.to_src > r.to_src) return false;

    if(ly < ry) return true;
    if(ly > ry) return false;

    if(lx < rx) return true;
    if(lx > rx) return false;
    
    return false;
}

vector<Path>::iterator get_closest_passenger(){
    // update distance;
    bfs({ty, tx});

    for(Path& p: paths){
        p.to_src = dist[p.src.y][p.src.x];
        if(p.to_src == -1)
            p.to_src = INT_MAX;
    }

    
    // sort pickup location
    vector<Path>::iterator it = min_element(begin(paths), end(paths), cmp);

    return it;
}

void set_requiring_fuel(){
    // 원소를 꺼내고 그 원소의 값을 변경한다
    // call by reference
    for(Path& p: paths){
        bfs(p.src); // 출발지에서 bfs -> dist 가 바뀐다
        p.to_dest = dist[p.dest.y][p.dest.x];
        if(p.to_dest == -1)
            p.to_dest = INT_MAX;
    }
}

void solve(){
    set_requiring_fuel(); // 손님 출발지 ~ 목적지 가는데 필요한 연료

    ll fuel_remaining = F;
    bool mission_complete = true;

    while(!paths.empty()){
        auto it = get_closest_passenger(); // 택시 위치에 따라 손님까지 거리를 갱신

        Path p = *it;
        paths.erase(it);

        ll fuel_requiring = p.to_src;
        fuel_requiring += p.to_dest;

        if(fuel_remaining - fuel_requiring < 0){
            mission_complete = false;
            break;
        }
        else{
            fuel_remaining -= fuel_requiring;
            fuel_remaining += p.to_dest * 2;

            ty = p.dest.y;
            tx = p.dest.x;
        }
    }
    if(mission_complete) cout << fuel_remaining << '\n';
    else cout << -1 << '\n';
}