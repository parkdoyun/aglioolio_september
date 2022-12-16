#include <algorithm>
#include <cmath>
#include <limits.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

#define OFF '0'
#define ON '1'

void init();
void solve();

int N; // 2 ~ 100,000
vector<char> lights;
vector<char> target_pattern;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    init();
    solve();
    return 0;
}

void init(){
    cin >> N;
    lights.resize(N);
    target_pattern.resize(N);

    rep(i, N) cin >> lights[i];
    rep(i, N) cin >> target_pattern[i];
}

void push_switch(vector<char>& state, int ith){
    for(int i = ith - 1; i <= ith + 1; ++i){
        if(i < 0 || i > N - 1) continue;
        state[i] = (state[i] == ON) ? OFF : ON;
    }
}

bool is_pattern_matched(const vector<char>& subject, const vector<char>& target){
    return subject[N - 1] == target[N - 1];
}

void solve(){
    // 이전에 누른 스위치는 다시 누를 수 없다고 가정하자. 
    // 두 가지 경우를 생각해 볼 수 있다.
    // i) 첫 번째 스위치를 누르지 않은 상태에서 시작
    // ii) 첫 번째 스위치를 누른 상태에서 시작

    vector<vector<char>> light_states(2, lights);
    push_switch(light_states[1], 0); // 첫 번째 스위치 누른 상태

    vector<int> push_counters = {0, 1};

    for(int i = 0; i < 2; ++i){
        
        vector<char>& state = light_states[i];
        int& cnt = push_counters[i];
        
        for(int j = 1; j < N; ++j){
            if(state[j - 1] == target_pattern[j - 1]) continue;
            push_switch(state, j);
            ++cnt;
        }

    }

    int answer = INT_MAX;
    for(int i = 0; i < 2; ++i){
        vector<char>& state = light_states[i];
        int& cnt = push_counters[i];

        if(is_pattern_matched(state, target_pattern))
            answer = min(answer, cnt);
    }

    if(answer == INT_MAX) cout << -1 << "\n";
    else cout << answer << "\n";
}