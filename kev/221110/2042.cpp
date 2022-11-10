#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Query{
    int a;
    int b;
    long long c;
};

struct Bound{
    int start;
    int end;
};

vector<long long> segtree;
vector<long long> seq;
vector<Query> queries;

void solve();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}

long long init(int root, Bound bound){
    if(bound.start == bound.end)
        return segtree[root] = seq[bound.start];
    int mid = (bound.start + bound.end) / 2;
    return segtree[root] = init(root*2, {bound.start, mid}) + init(root*2 + 1, {mid + 1, bound.end});
}

void update(int root, Bound bound, int t, long long diff){
    if(t < bound.start || t > bound.end)
        return;
    
    segtree[root] += diff;

    if(bound.start == bound.end)
        return;
    
    int mid = (bound.start + bound.end) / 2;
    update(root*2, {bound.start, mid}, t, diff);
    update(root*2 + 1, {mid + 1, bound.end}, t, diff);
}

long long get_partial_sum(int root, Bound u, Bound t){
    if(t.start > u.end || t.end < u.start)
        return 0;
    
    if(t.start <= u.start && u.end <= t.end)
        return segtree[root];
    
    int mid = (u.start + u.end) / 2;
    return get_partial_sum(root*2, {u.start, mid}, t) + get_partial_sum(root*2 + 1, {mid + 1, u.end}, t);
}

void solve(){
    int N, M, K;
    cin >> N >> M >> K;

    seq.resize(N);
    for(int i = 0; i < N; i++){
        cin >> seq[i];
    }

    queries.resize(M + K);
    for(int i = 0; i < M + K; i++){
        cin >> queries[i].a
            >> queries[i].b
            >> queries[i].c;
    }

    int h = (int)ceil(log2(N));
    int tree_size = 1 << (h + 1);
    segtree.resize(tree_size);
    init(1, {0, N - 1});

    for(const auto& q: queries){
        int a = q.a, b = q.b;
        long long c = q.c;

        if(a == 1){ // update
            long long diff = c - seq[b - 1];
            seq[b - 1] = c;
            update(1, {0, N - 1}, b - 1, diff);
        }
        else{ // get partial sum
            cout << get_partial_sum(1, {0, N-1}, {b-1, (int)c - 1}) << '\n';
        }
    }
}