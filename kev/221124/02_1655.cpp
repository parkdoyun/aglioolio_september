// 22-11-19 12:50 ~ 13:10
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

// 전형적인 우선 순위 큐 활용 문제

void solve(){
    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;
    
    int N; cin >> N;
    rep(i, N){
        int num; cin >> num;
        
        if(max_heap.empty()){
            max_heap.push(num);
        }
        else if(num >= max_heap.top())
            min_heap.push(num);
        else{
            max_heap.push(num);
        }

        if(size(min_heap) - size(max_heap) == 1){
            int tmp = min_heap.top();
            min_heap.pop();
            max_heap.push(tmp);
        }
        else if(size(max_heap) - size(min_heap) == 2){
            int tmp = max_heap.top();
            max_heap.pop();
            min_heap.push(tmp);
        }
        
        cout << max_heap.top() << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}