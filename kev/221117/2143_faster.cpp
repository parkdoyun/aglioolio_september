#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

int acc_a[1001];
int acc_b[1001];
vector<int> sub_a;
vector<int> sub_b;

// 14:35 ~ 15:13 252
void solve();

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(0);

    solve();

    return 0;
}

// 모든 구간합 비교 -> 연산이 너무 많다
// 최악의 경우
// A 모든 구간합, B 모든 구간합 구하는데 걸리는 시간
// M^2, N^2
// 각 구간 합을 더했을 때 T를 만드는 경우
// M^2 * N^2
// (MN)^2
// M = N = 1000일 때, 10^12
// 모든 구간합을 해시로 저장하면?
// A 집합에서 M^2의 구간합이 나왔다면 M^2번 해시 연산을 통해 답이 나옴
// 문제는 해시에 1000000개의 키 값을 저장하는게 속도에 지장이 없을지? -> 속도에는 큰 문제 없어보이는데
// 답이 틀렸다... 왜?

int find_and_count(const vector<int>& seq, int value){
    auto lb = lower_bound(all(seq), value);
    auto ub = upper_bound(all(seq), value);
    
    if(lb == end(seq))
        return 0;
    return distance(lb, ub);
}

//test test
void solve(){
    int T; cin >> T;
    
    int N; cin >> N;
    vector<int> a(N);
    rep(i, N) cin >> a[i];

    int M; cin >> M;
    vector<int> b(M);
    rep(i, M) cin >> b[i];

    // 모든 구간합 구하면서 해시에 등록 O(N^2), O(M^2)
    for(int i = 0; i < N; i++){
        int sum = 0;
        for(int j = 0; j < N - i; j++){
            sum += a[i + j];
            sub_a.push_back(sum);
        }
    }
    sort(all(sub_a));

    for(int i = 0; i < M; i++){
        int sum = 0;
        for(int j = 0; j < M - i; j++){
            sum += b[i + j];
            sub_b.push_back(sum);
        }
    }
    sort(all(sub_b));

    long long answer = 0;
    for(const auto& e: sub_a){
        auto lb = lower_bound(all(sub_b), T - e);
        auto ub = upper_bound(all(sub_b), T - e);
        answer += distance(lb, ub);
    }
    cout << answer << '\n';
}