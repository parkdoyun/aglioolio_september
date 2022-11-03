#include <iostream>
#include <vector>
using namespace std;

#define rep(idx, n) for(int idx = 0; idx < (n); ++idx)
#define all(container) (container).begin(), (container).end()
#define size(container) ((int)((container).size()))

int N, M;

bool can_move_all_boxes(const vector<int>& p, const vector<int>& w, int stride){
    int i = 0, j = 0;    
    while(i < N && j < M){
        if(p[i] < w[j]) return false;
        i++;
        j += stride;
    }
    return j >= M;
}

void solve(){
    cin >> N;
    vector<int> p(N); rep(i, N) cin >> p[i];
    
    cin >> M;
    vector<int> w(M); rep(i, M) cin >> w[i];

    sort(all(p), greater<int>());
    sort(all(w), greater<int>());
    
    if(p[0] < w[0]){
        cout << -1 << '\n';
        return;
    }

    int low = 1;
    int high = M;
    int answer;
    while(low <= high){
        int mid = (low + high) / 2;
        if(can_move_all_boxes(p, w, mid)){
            answer = mid;
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }

    cout << answer << '\n';
}

int main(){
    solve();
    return 0;
}