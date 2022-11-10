#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// 솔루션 참고

#define rep(i, n) for(int i = 0; i < (n); i++)

struct Command{
    int a;
    int b;
    long long c;
};

struct Bound{
    int start, end;
};

long long* segtree;
long long* seq;
Command* cmds;

long long init(int i, Bound b){
    if(b.start == b.end) return segtree[i] = seq[b.start];
    int mid = (b.start + b.end) >> 1;
    return segtree[i] = init(i * 2, {b.start, mid}) + init(i * 2 + 1, {mid + 1, b.end});
}

/**
 * @brief 특정 구간합을 구한다
 * 
 * @param i segtree idx
 * @param b segment bound 
 * @param t target segment bound
 * @return long long 
 */
long long get_partial_sum(int i, Bound b, Bound t){
    if(t.start > b.end || t.end < b.start)
        return 0;
    
    if(t.start <= b.start && b.end <= t.end)
        return segtree[i];
    
    int mid = (b.start + b.end) >> 1;
    int left_child = get_partial_sum(i*2, {b.start, mid}, t);
    int right_child = get_partial_sum(i*2 + 1, {mid + 1, b.end}, t);
    
    return left_child + right_child;
}

/**
 * @brief segment tree 업데이트
 * 
 * @param i segtree index
 * @param b segment bounds
 * @param ti target index
 * @param d 변경된 타겟 인덱스 차이
 */
void update(int i, Bound b, int ti, long long d){
    if(ti < b.start || ti > b.end) return;
    
    segtree[i] += d;
    
    if(b.start == b.end) return;
    
    int mid = (b.start + b.end) >> 1;
    
    update(i*2, {b.start, mid}, ti, d);
    update(i*2 + 1, {mid + 1, b.end}, ti, d);
}

void solve(){
    int N, M, K;
    cin >> N >> M >> K;

    seq = new long long[N];
    rep(i, N)
        cin >> seq[i];
    
    cmds = new Command[M + K];
    rep(i, M + K){
        cin >> cmds[i].a
            >> cmds[i].b
            >> cmds[i].c;
    }

    // initialize segtree
    int h = (int)ceil(log2(N));
    int size = 1 << (h + 1);
    segtree = new long long[size];
    init(1, {0, N - 1});

    const int UPDATE = 1;
    const int PARTIAL_SUM = 2;
    for(int i = 0; i < M + K; i++){
        int opcode = cmds[i].a;
        switch (opcode)
        {
        case UPDATE:
            {
                int t = cmds[i].b - 1;
                long long diff = cmds[i].c - seq[t];
                seq[t] = cmds[i].c;
                update(1, {0, N - 1}, t, diff);
            }
            break;
        case PARTIAL_SUM:
            {
                Bound u = {0, N - 1};
                Bound t = {cmds[i].b - 1, (int)(cmds[i].c - 1)};
                long long result = get_partial_sum(1, u, t);
                cout << result << '\n';
            }
            break;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

     solve();

    return 0;
}