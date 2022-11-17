// 2022-11-11 10:00 ~ 10:35 out of bound error
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;

// r행 c열
// N, M의 크기가 작다 -> DFS
struct Node{
    int r;
    int c;
};

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, -1, 0 ,1};


int N, M, C;
int city[50][50];
int answer = 2147483647;

vector<Node> houses;
vector<Node> bbqs;

void solve();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

int get_chicken_distance(const Node& house){
    int min_dist = 2147483647;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(city[i][j] != 2)
                continue;
            int dist = abs(house.r - i) + abs(house.c - j);
            min_dist = min(min_dist, dist);
        }
    }
    return min_dist;
}

void dfs(int idx, int cnt){    
    if(cnt == M){
        int total_chicken_distance = 0;
        for(const auto& house: houses){
            total_chicken_distance += get_chicken_distance(house);
        }
        answer = min(answer, total_chicken_distance);
        return;
    }

    if(idx == C)
        return;

    for(int i = idx; i < C; i++){
        int r = bbqs[i].r;
        int c = bbqs[i].c;
        
        city[r][c] = 0;
        dfs(i + 1, cnt - 1);
        city[r][c] = 2;
    }
}

void solve(){
    cin >> N >> M;
    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            cin >> city[r][c];
            if(city[r][c] == 1)
                houses.push_back({r, c});
            else if(city[r][c] == 2)
                bbqs.push_back({r, c});
        }
    }

    C = bbqs.size();
    dfs(0, C);

    cout << answer << '\n';
}