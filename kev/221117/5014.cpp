#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

int F, S, G, U, D;

void solve(){
    cin >> F >> S >> G >> U >> D;
    
    vector<int> dat(F + 1, INT_MAX);
    dat[S] = 0;
    queue<int> q; q.push(S);
    while(!q.empty()){
        int cur = q.front();
        q.pop();

        if(cur + U <= F && dat[cur + U] > dat[cur] + 1){
            dat[cur + U] = dat[cur] + 1;
            q.push(cur + U);
        }

        if(cur - D >= 1 && dat[cur - D] > dat[cur] + 1){
            dat[cur - D] = dat[cur] + 1;
            q.push(cur - D);
        }
    }
    if(dat[G] == INT_MAX){
        cout << "use the stairs" << '\n';
    }
    else{
        cout << dat[G] << '\n';
    }
}

int main(){
    solve();
    return 0;
}