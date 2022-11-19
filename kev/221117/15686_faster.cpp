// 2022-11-11 10:00 ~ 11:34 396ms
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())
// r행 c열
// N, M의 크기가 작다 -> DFS
struct Node{
    int r;
    int c;
};

int N, M;
int city[50][50];
int answer = 2147483647;

vector<Node> houses;
vector<Node> chickens;
vector<bool> shut_downed;

void solve();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

int get_distance(const Node& house, const Node& chicken){
    return abs(house.r - chicken.r) + abs(house.c - chicken.c);
}

int get_total_distance(){
    int total_distance = 0;
    rep(i, size(houses)){
        int distance = 2147483647;
        rep(j, size(chickens)){
            if(shut_downed[j]) continue;
            distance = min(distance, get_distance(houses[i], chickens[j]));
        }
        total_distance += distance;
    }
    return total_distance;
}

void dfs(int cur, int cnt){
    if(cnt == 0){
        answer = min(answer, get_total_distance());
        return;
    }

    if(cur == size(chickens))
        return;

    for(int i = cur; i < size(chickens); i++){
        shut_downed[i] = true;
        dfs(i + 1, cnt - 1);
        shut_downed[i] = false;
    }
}

void solve(){
    cin >> N >> M;
    rep(r, N){
        rep(c, N){
            int label; cin >> label;
            if(label == 1)
                houses.push_back({r, c});
            else if(label == 2)
                chickens.push_back({r, c});
        }
    }
    rep(i, size(chickens))
        shut_downed.push_back(false);
    
    int cnt = size(chickens) - M;
    dfs(0, cnt);

    cout << answer << '\n';
}