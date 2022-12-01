#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)

char org[10][10];
char light[10][10];
int answer = INT_MAX;

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, -1, 0, 1};

void turn_on(int i, int j){
    {
        char state = light[i][j];
        light[i][j] = (state == '#') ? 'O' : '#';
    }

    for(int k = 0; k < 4; k++){
        int ny = i + dy[k];
        int nx = j + dx[k];
        if(ny < 0 || nx < 0 || ny >= 10 || nx >= 10) continue;
        char state = light[ny][nx];
        light[ny][nx] = (state == '#') ? 'O' : '#';
    }
}

int modify_first_row(int bit){
    int cnt = 0;
    for(int c = 0; c < 10; c++){
        if(bit & (1 << c)){
            turn_on(0, c);
            cnt++;
        }
    }
    return cnt;
}

void solve(){
    rep(i, 10) rep(j, 10) cin >> org[i][j];
    for(int k = 0; k < 1024; k++){
        rep(i, 10) rep(j, 10) light[i][j] = org[i][j];

        int cnt = modify_first_row(k);

        for(int r = 1; r < 10; r++){
            for(int c = 0; c < 10; c++){
                if(light[r - 1][c] == 'O'){
                    turn_on(r, c);
                    cnt++;
                }
            }
        }

        bool valid = true;
        for(int c = 0; c < 10; c++){
            if(light[9][c] == 'O'){
                valid = false;
                break;
            }
        }
        
        if(valid) answer = min(answer, cnt);
    }
    
    if(answer == INT_MAX) cout << -1 << '\n';
    else cout << answer << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}