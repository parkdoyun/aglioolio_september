#include <iostream>
using namespace std;

// 00h 30m, 0ms

int N, M;
bool broken[11];

int can_make_number(int num){
    if(num == 0){
        return broken[0] ? 0 : 1;
    }

    int cnt = 0;
    while(num > 0){
        int btn = num % 10;
        if(broken[btn]) return 0;
        num /= 10;
        cnt++;
    }
    return cnt;
}

void solve(){
    cin >> N >> M;
    for(int i = 0; i < M; i++){
        int n; cin >> n;
        broken[n] = true;
    }
    
    // 남은 숫자 버튼으로 N과 가장 가까운 번호 만들기
    // 시작 채널 100
    int d = N > 100 ? N - 100 : 100 - N;
    
    if(d == 0){
        cout << d << '\n';
        return;
    }
    
    for(int n = N; n >= 0; n--){
        int len = can_make_number(n);
        if(len == 0) continue;
        if(d > len + N - n){
            d = len + N - n;
        }
        break;
    }

    for(int n = N; n < N + d; n++){
        int len = can_make_number(n);
        if(len == 0) continue;
        if(d > len + n - N){
            d = len + n - N;
        }
        break;
    }

    cout << d << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}