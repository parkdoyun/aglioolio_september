#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define rep(idx, n) for(int idx = 0; idx < (n); ++idx)
#define all(container) (container).begin(), (container).end()
#define size(container) (int)((container).size())
#define ll long long

// 가방에는 최대 한 개의 보석만 넣을 수 있다
// 보석 무게 오름차순 정렬
// 가방을 capacity 오름차순 정렬
// 각 가방 이분 탐색, 선형 탐색 수행
// 정렬 KlogK + NlogN
// K(logN + N) -> O(KN) // 실패

// dp[300001][300001]
// 

struct Jewelry{
    int m;
    int v;
};

bool operator < (const Jewelry& l, const Jewelry& r){
    return l.m < r.m;
}

int N, K;
vector<Jewelry> jewelries;
vector<int> bags;

void init();
void solve();

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    init();
    solve();
    return 0;
}

void init(){
    cin >> N >> K;
    vector<Jewelry> tmp_jewelries(N);
    rep(i, N){
        cin >> tmp_jewelries[i].m >> tmp_jewelries[i].v;
    }

    vector<int> tmp_bags(K);
    rep(i, K){
        cin >> tmp_bags[i];
    }

    swap(jewelries, tmp_jewelries);
    swap(bags, tmp_bags);
}

void solve(){
    sort(all(jewelries)); // NlogN
    sort(all(bags)); // KlogK

    ll max_val = 0;
    int k = 0;
    int n = 0;
    priority_queue<int> top_values;
    while(k < K){
        while(n < N && jewelries[n].m <= bags[k]){
            top_values.push(jewelries[n++].v);
        } // NlogN

        if(!top_values.empty()){
            max_val += top_values.top();
            top_values.pop();
        }

        k++;
    }// K * NlogN

    while(k < K && !top_values.empty()){
        max_val += top_values.top();
        top_values.pop();
        k++;
    }

    cout << max_val << '\n';
}