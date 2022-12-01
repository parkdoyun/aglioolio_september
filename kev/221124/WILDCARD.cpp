#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

int N;
string W, S;
int cache[101][101];


void init();
void solve();
void test();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // test();
    int C; cin >> C;
    rep(i, C){
        solve();
    }

    return 0;
}

bool match(int i, int j){
    int& ret = cache[i][j];
    
    if(ret != -1)
        return ret;
    
    while(i < size(W) && j < size(S) && (W[i] == S[j] || W[i] == '?')){
        return ret = match(i + 1, j + 1);
    }

    if(i == size(W))
        return ret = j == size(S);

    if(W[i] == '*'){
        if(match(i + 1, j) || (j < size(S) && match(i, j + 1)))
            return ret = 1;
    }
    return ret = 0;
}

void solve(){    
    cin >> W;
    int N; cin >> N;
    vector<string> file_names(N); rep(i, N) cin >> file_names[i];
    
    vector<string> answer;
    for(const auto& file_name: file_names){
        memset(cache, -1, sizeof(cache));

        S = file_name;

        if(match(0, 0)) answer.push_back(file_name);
    }
    
    sort(all(answer));
    for(const auto& a: answer)
        cout << a << "\n";
}

void test(){
    rep(i, 101) rep(j, 101) cache[i][j] = -1;
    W = "he?p";
    S = "helpp";
    cout << boolalpha << match(0, 0) << '\n';
}
