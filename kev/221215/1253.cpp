#include <algorithm>
#include <cmath>
#include <limits.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

const int d4y[4] = {-1, 0, 1, 0};
const int d4x[4] = {0, -1, 0, 1};

void init();
void solve();

int N;
vector<int> seq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    init();
    solve();

    return 0;
}

void init(){
    cin >> N;
    seq.resize(N);
    rep(i, N) cin >> seq[i];
}

void solve(){
    if(N < 3){
        cout << "0" << "\n";
        return;
    }

    unordered_map<int, int> hashmap;
    // 1 1 0
    // hash[1] = 2
    // hash[0] = 1
    for(const auto e: seq) hashmap[e]++; // 숫자, 개수
    // hashmap[1] == 1
    int good_number_counter = 0;

    for(int i = 0; i < N; ++i){
        // is seq[i] "good"?
        // 0 1 2 3 4 3 2 1

        // 1 (0 1) 
        for(int j = 0; j < N; ++j){
            if(i == j) continue;
            
            //  1        1        0
            int target = seq[i] - seq[j];
            // 0 0 0 ok
            // 0 0 
            // target not found
            if(hashmap.find(target) == hashmap.end()) continue;

            // target not found
            if((seq[j] == target || seq[i] == target) && (hashmap[target] < 2)) continue;
            if((seq[j] == target && seq[i] == target) && (hashmap[target] < 3)) continue;

            ++good_number_counter;

            break;
        }
    }
    
    cout << good_number_counter << '\n';
}