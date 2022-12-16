#include <iostream>
#include <string>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

bool cmp(const string& l, const string& r){
    
}

string subtract(const string& l, const string& r){
    string minuend(l.rbegin(), l.rend());
    string subtrahend(r.rbegin(), r.rend());
    string diff;
    
    rep(i, size(r)){
        char d = minuend[i] - subtrahend[i] + '0';
        if(d < '0'){
            --minuend[i + 1];
            d += 10;
        }
        diff.push_back(d);
    }

    for(int i = size(diff) - 1; i > -1; --i){
        if(diff[i] < '0')
    }

    reverse(all(l));
}

int main(){
    string N, M;
    cin >> N >> M;

    // 뺄셈으로 나누기 구현
    
    return 0;
}