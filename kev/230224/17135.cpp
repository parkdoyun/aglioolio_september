#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <limits.h>
#include <set>
using namespace std;

struct Coord
{
    int y;
    int x;
};

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, -1, 0, 1};

int N, M, D;

Coord get_nearest_target(const Coord &archer,
                         const vector<vector<int>> &enemies)
{
    int min_dist = INT_MAX;
    Coord ret = {-1, -1};
    
    for (int y = archer.y - 1; y >= 0; --y)
    {
        for (int x = 0; x < M; ++x)
        {
            int dist = abs(archer.y - y) + abs(archer.x - x);
            if (dist > D)
                continue;
            if (enemies[y][x] == 0)
                continue;

            if(dist < min_dist){
                min_dist = dist;
                ret = {y, x};
                continue;
            }

            if(dist == min_dist && x < ret.x){
                ret = {y, x};
            }
        }
    }

    return ret;
}

bool is_coord_valid(const Coord &target)
{
    return target.y >= 0 && target.x >= 0 && target.y < N && target.x < M;
}

int simulate_wave_attack(vector<vector<int>> &enemies,
                         vector<Coord> &archers)
{
    int kill_count = 0;

    for (int y = N; y > 0; --y)
    {
        set<pair<int, int>> targets;
        for (int i = 0; i < 3; ++i)
        {
            archers[i].y = y;
            Coord t = get_nearest_target(archers[i],
                                         enemies);

            if (!is_coord_valid(t))
                continue;

            targets.insert({t.y, t.x});
        }
        for(auto it=targets.begin(); it != targets.end(); it++)
            enemies[(*it).first][(*it).second]=0;
        kill_count += targets.size();
    }

    return kill_count;
}

void solve()
{

    // 궁수는 거리가 D 이내에 있는 적군 중 가장 가까운 대상을 공격한다
    // 가장 가까운 대상이 2개 이상일 경우 가장 왼쪽 대상을 공격한다
    // 궁수의 공격은 동시에 이루어지며 궁수의 공격이 끝나면 적이 한칸 성쪽으로 이동한다

    // 3 <= N <= 15 therefore, 455(15C3) cases of archer depolyment
    cin >> N >> M >> D;

    vector<vector<int>> enemies(N, vector<int>(M));
    for (auto &r : enemies)
        for (auto &c : r)
            cin >> c;

    vector<int> position(M, 0);
    for (int i = M - 3; i < M; ++i)
        position[i] = 1;

    int max_kill_count = 0;
    do
    {
        vector<vector<int>> copy = vector<vector<int>>(N, vector<int>(M));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                copy[i][j] = enemies[i][j];

        vector<Coord> archers;
        for (int i = 0; i < M; ++i)
        {
            if (position[i] == 0)
                continue;
            archers.push_back({N, i});
        }

        int kill_count = simulate_wave_attack(copy, archers);

        max_kill_count = max(kill_count, max_kill_count);

    } while (next_permutation(position.begin(), position.end()));

    cout << max_kill_count << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}