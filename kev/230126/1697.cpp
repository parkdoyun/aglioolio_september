#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

void init();
void solve();

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    init();
    solve();

    return 0;
}

int N, K;
void init(){
    cin >> N >> K;
}

int forward(int p){ return p + 1; }
int backward(int p){ return p - 1; }
int teleport(int p){ return p * 2; }

void solve(){

    const int MAX_X = 100000;
    const int INF = INT_MAX / 2;

    vector<int> x(MAX_X + 1, INF);
    x[N] = 0;
    
    queue<int> q;
    q.push(N);
    
    int (*fp[3])(int) = {teleport, forward, backward};

    while(!q.empty()){
        
        int cur = q.front();
        q.pop();

        for(int k = 0; k < 3; ++k){
            
            int next = fp[k](cur);
            
            if(next > MAX_X || next < 0) continue;
            if(x[next] < x[cur] + 1) continue;
            
            x[next] = x[cur] + 1;
            q.push(next);
        }
    }   
    
    cout << x[K] << '\n';
}