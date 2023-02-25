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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    init();
    solve();
    return 0;
}

vector<int> seq;
unordered_map<int, int> um;
void init(){
    int N; cin >> N;
    seq.resize(N);
    rep(i, N){
        cin >> seq[i];
        um[seq[i]]++;
    }
}

void solve(){
    // N명의 코딩 실력이 -10000 ~ 10000 사이의 정수로 주어 질 떄
    // 3명의 코딩 실력의 합이 0이 되는 모든 경우의 수 세기
    sort(all(seq));

    int cnt = 0;
    for(int i = 0; i < size(seq) - 2; ++i){
        int t = -seq[i];
        int j = i + 1, k = size(seq) - 1;
        while(j < k){
            int s = seq[j] + seq[k];
            if(s < t) ++j;
            else if(s == t) {--k; ++cnt;}
            else --k;
        }
    }

    cout << cnt << "\n";

}