#include <iostream>
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
unordered_map<int, int> sub_a;
unordered_map<int, int> sub_b;

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

void solve(){
    int T; cin >> T;
    
    int N; cin >> N;
    vector<int> a(N);
    rep(i, N) cin >> a[i];

    int M; cin >> M;
    vector<int> b(M);
    rep(i, M) cin >> b[i];

    // 누적합 구하기 O(N), O(M)
    // acc_a[0] = 0
    for(int i = 1; i <= N; i++){
        acc_a[i] = acc_a[i - 1] + a[i - 1];
    }

    for(int i = 1; i <= M; i++){
        acc_b[i] = acc_b[i - 1] + b[i - 1];
    }

    // 모든 구간합 구하면서 해시에 등록 O(N^2), O(M^2)
    for(int i = 0; i < N; i++){
        for(int j = i + 1; j <= N; j++){
            int key = acc_a[j] - acc_a[i];
            sub_a[key]++;
        }
    }

    for(int i = 0; i < M; i++){
        for(int j = i + 1; j <= M; j++){
            int key = acc_b[j] - acc_b[i];
            sub_b[key]++;
        }
    }
    
    long long answer = 0;
    iterate(it, sub_a){
        auto look_for = sub_b.find(T - it->first);
        if(look_for == sub_b.end())
            continue;
        long long a_cnt = it->second;
        long long b_cnt = look_for->second;
        answer += a_cnt * b_cnt;
    }
    cout << answer << '\n';
}