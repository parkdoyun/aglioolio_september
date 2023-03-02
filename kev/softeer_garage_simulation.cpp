#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

int grid[45][15];
int prev_grid[3][45][15];

int N;

struct Coord{
    int y;
    int x;
};

struct Bounds{
    Coord max;
    Coord min;
};

void update_bounds(Bounds& bounds, const Coord& coord){
    Coord& max = bounds.max;
    Coord& min = bounds.min;

    if(coord.y > max.y) max.y = coord.y;
    if(coord.y < min.y) min.y = coord.y;
    if(coord.x > max.x) max.x = coord.x;
    if(coord.x < min.x) min.x = coord.x;
}

int get_area(const Bounds& bounds){
    const Coord& max = bounds.max;
    const Coord& min = bounds.min;

    int width = max.x - min.x + 1;
    int height = max.y - min.y + 1;

    return width * height;
}

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, -1, 0, 1};

int bfs(const Coord& start, Bounds& bounds, vector<vector<bool>>& simulate_already){
    queue<Coord> q;
    q.push({start.y, start.x});

    simulate_already[start.y][start.x] = true;

    int target_color = grid[start.y][start.x];
    grid[start.y][start.x] = 0;
    int removed = 1;

    while(!q.empty()){
        auto cur = q.front();
        q.pop();

        for(int k = 0; k < 4; ++k){
            int ny = cur.y + dy[k];
            int nx = cur.x + dx[k];

            if(ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            if(grid[ny][nx] != target_color) continue;

            grid[ny][nx] = 0; // mark as empty
            simulate_already[ny][nx] = true; // this coord do not needs to simulate anymore

            update_bounds(bounds, {ny, nx});

            removed++;

            q.push({ny, nx});
        }
    }

    return removed;
}

bool find_first_empty_row(int& empty_row, int col){
    for(; empty_row < N; ++empty_row){
        if(grid[empty_row][col] != 0) continue;
        return true;
    }
    return false;
}

void pull_next_cars(const Bounds& removed_bound){
    const Coord& max = removed_bound.max;
    const Coord& min = removed_bound.min;

    for(int c = min.x; c <= max.x; ++c){
        int empty_row = min.y;
        if(!find_first_empty_row(empty_row, c)) continue;

        for(int r = empty_row + 1; r < 3 * N; ++r){
            if(grid[r][c] == 0) continue;
            grid[empty_row++][c] = grid[r][c];
            grid[r][c] = 0;
        }
    }
}

int max_score = 6;
void dfs(int sim_cnt, int score){
    if(sim_cnt == 3){
        max_score = max(score, max_score);
        return;
    }

    int max_potential_gain = (N * N * 2) * (3 - sim_cnt);
    if(score + max_potential_gain <= max_score) return; // 큰 영향은 없었다

    // visited 배열
    vector<vector<bool>> simulate_already(N, vector<bool>(N, false));
    for(int i = 0; i < 3 * N; ++i)
        for(int j = 0; j < N; ++j)
            prev_grid[sim_cnt][i][j] = grid[i][j];

    for(int r = 0; r < N; ++r){
        for(int c = 0; c < N; ++c){
            if(grid[r][c] == 0) continue;
            if(simulate_already[r][c]) continue;

            Bounds removed_bounds = {{r, c}, {r, c}}; // remove_bound를 저장해서
            int removed = bfs({r, c}, removed_bounds, simulate_already);

            if(sim_cnt < 2) // 마지막 시뮬레이션의 경우 더 이상 차를 위에서 가져올 필요가 없다
                pull_next_cars(removed_bounds); // bfs를 통해 차가 사라진 영역을 알았다. 그 영역에 영향을 받는 좌표만 차를 위에서 가져온다

            dfs(sim_cnt + 1, score + removed + get_area(removed_bounds));

            if(sim_cnt == 2){ // 마지막 시뮬레이션이면
                const Coord& max = removed_bounds.max;
                const Coord& min = removed_bounds.min;

                for(int i = min.y; i <= max.y; ++i)
                    for(int j = min.x; j <= max.x; ++j)
                        grid[i][j] = prev_grid[sim_cnt][i][j];
                continue;
            } // dfs 탈출하고 이전 배열로 상태를 복원할 때 마지막 시뮬레이션의 경우 N * N 영역에 대해서만 다시 상태 복원하도록 한다

            for(int i = 0; i < 3 * N; ++i)
                for(int j = 0; j < N; ++j)
                    grid[i][j] = prev_grid[sim_cnt][i][j];
        }
    }
}

void solve(){
    cin >> N;
    
    for(int i = 0; i < 3 * N; ++i){
        for(int j = 0; j < N; ++j){
            cin >> grid[3 * N - 1 - i][j];
        }
    }

    dfs(0, 0);

    cout << max_score << '\n';

        // col 0 1
    // row
    // 0       1 2 <- simulation space
    // 1       4 4 
    // 2       3 3 <- next cars
    // 3       1 1
    // 4       2 2
    // 5       1 1
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}