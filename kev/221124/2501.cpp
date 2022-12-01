 #include <iostream>
 using namespace std;

void solve();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}

void solve(){
    int N, K;
    cin >> N >> K;
    
    if(K == 1){
        cout << 1 << "\n";
        return;
    }
    
    int k = 1;
    for(int n = 2; n <= N; n++){
        if(N % n == 0) k++;
        if(k == K){
            cout << n << "\n";
            return;
        }
    }
    cout << "0" << "\n";
}