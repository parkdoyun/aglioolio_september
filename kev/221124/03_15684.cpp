#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

// 13:11 ~

struct Node{
    int n;
    int h;
};

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())
#define pii pair<int, int>

int N, M, H;
int ladder[12][31];

bool is_ladder_valid(int n, int h){
    return ladder[n - 1][h] == 0 && ladder[n + 1][h] == 0;
}

bool is_goal_achieved(){
    for(int i = 1; i <= N; i++){
        int start = i, cur = i;
        for(int a = 1; a <= H; a++){
            if(ladder[cur - 1][a] == 1) cur--;
            else if(ladder[cur][a] == 1) cur++;
        }
        if(cur != start) return false;
    }
    return true;
}

void solve(){
    // 세로선 N개 / 가로선 놓은 수 있는 위치 H개 / 가로선 M개
    // i번 세로선에서 출발해서 i번으로 도착하는 것이 목표
    // 목표를 달성하기 위해 추가해야되는 최소 가로선의 개수?
    // 추가해야 되는 가로선이 3개 보다 많으면 -1
    // 불가능한 경우에도 -1
    cin >> N >> M >> H;
    rep(i, M){
        int a, b;
        cin >> a >> b;
        ladder[b][a] = 1;
    }

    if(is_goal_achieved()){
        cout << 0 << '\n';
        return;
    }
    
    vector<Node> candidates;
    for(int n = 1; n < N; n++){
        for(int h = 1; h <= H; h++){
            if(ladder[n][h] == 1) continue;
            if(ladder[n - 1][h] == 1) continue;
            if(ladder[n + 1][h] == 1) continue;
            candidates.push_back({n, h});
        }
    }

    vector<int> mask(size(candidates), 0);
    vector<Node> new_ladders;
    
    for(int additional_ladders = 1; additional_ladders <= 3; additional_ladders++){
        // 추가할 사다리의 개수가 놓을 수 있는 위치의 개수보다 많으면 더 이상 목표를 달성할 수 없다
        if(additional_ladders > size(candidates)){
            cout << -1 << '\n';
            return;
        }
        
        rep(i, additional_ladders) mask[i] = 1;
        
        new_ladders.clear();
        new_ladders.resize(additional_ladders);

        do{
            int k = 0;
            for(int i = 0; i < size(candidates); i++){
                if(mask[i] == 0) continue;
                new_ladders[k++] = candidates[i];
            }

            
            for(const auto& l: new_ladders){
                ladder[l.n][l.h] = 1;
            }

            bool is_valid = true;
            for(const auto& l: new_ladders){
                is_valid &= is_ladder_valid(l.n, l.h);
            }
            
            if(!is_valid){
                for(const auto& l: new_ladders){
                    ladder[l.n][l.h] = 0;
                }
                continue;
            }

            if(is_goal_achieved()){
                cout << additional_ladders << '\n';
                return;
            }

            for(const auto& l: new_ladders){
                ladder[l.n][l.h] = 0;
            }

        }while(prev_permutation(all(mask)));
        
        int back = size(mask) - 1;
        rep(i, additional_ladders) mask[back - i] = 0;
    }

    cout << -1 << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    
    return 0;
}