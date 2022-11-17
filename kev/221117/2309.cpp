#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define all(v) (v).begin(), (v).end()

void solve(){
    vector<int> h(9);
    for(int i = 0; i < 9; i++)
        cin >> h[i];
    
    sort(all(h));
    
    int total = 0; 
    for(int i = 0; i < 9; i++) 
        total += h[i];

    vector<int> mask(9, 1);
    mask[0] = mask[1] = 0;
    do{
        int removed = 0;
        for(int i = 0; i < 9; i++){
            if(mask[i] == 0)
                removed += h[i];
        }
        if(total - removed == 100){
            for(int i = 0; i < 9; i++){
                if(mask[i] == 0) continue;
                cout << h[i] << '\n';
            }
            break;
        }
    }while(next_permutation(all(mask)));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}