#include <iostream>
#include <string>

using namespace std;

void init();
void solve();

int main(){
    init();
    solve();

    return 0;
}

string input;

void init(){
    cin >> input;
}

bool is_ppap_str(const string& str){
    int p = 0; // 누적된 p의 개수
    for(int f = 0; f < str.size(); f++){
        if(str[f] == 'A'){
            if(p < 2) return false;
            if(f + 1 == str.size()) return false;
            if(str[f + 1] != 'P') return false;
            f++;
            p--; // p - 2 + 1
        }
        else{
            p++;
        }
    }
    return p == 1;
}

void solve(){
    if(is_ppap_str(input)) cout << "PPAP" << '\n';
    else cout << "NP" << '\n';
}
