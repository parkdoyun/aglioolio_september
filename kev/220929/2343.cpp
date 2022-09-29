#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int acc[100001];

int main(){
    int N; cin >> N;
    int M; cin >> M;
    
    acc[0] = 0;
    int low = -1, high = 1e9;
    for(int i = 1; i <= N; i++){
        int n; cin >> n;
        if(n > low) low = n;
        acc[i] = acc[i - 1] + n;
    }

    int answer = 1e9;
    while(low <= high){
        ll mid = (low + high) >> 1;
        
        int cnt = 1; // 블루레이 길이가 mid일 때, 블루레이 개수
        int prev = acc[0]; // 0;
        for(int i = 1; i <= N; i++){
            if(acc[i] - prev <= mid) continue;
            prev = acc[i - 1];
            cnt++;
        }

        if(cnt <= M){
            answer = mid;
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }

    cout << answer << '\n';
    return 0;
}