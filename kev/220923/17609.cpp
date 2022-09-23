#include <iostream>
#include <vector>
#include <string>

using namespace std;

void init();
void solve();

bool is_palindrome(const string&);
bool is_pseudo_palindrome(const string&);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init();
    solve();

    return 0;
}

string words[30];
int N;
void init(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> words[i];
    }
}

bool is_palindrome(const string& word){
    int i = 0, j = word.size() - 1;
    while(i < j){
        if(word[i] != word[j]) return false;
        i++; j--;
    }
    return true;
}

bool is_pseudo_palindrome(const string& word){
    int i = 0, j = word.size() - 1;
    
    while(i < j){
        if(word[i] == word[j]){ i++; j--; }
        else break;
    }

    bool ret = is_palindrome(word.substr(i + 1, j - i));
    if(!ret) ret = is_palindrome(word.substr(i, j - i));

    return ret;
}

void solve(){
    for(int i = 0; i < N; i++){
        if(is_palindrome(words[i])) cout << 0 << '\n';
        else if(is_pseudo_palindrome(words[i])) cout << 1 << '\n';
        else cout << 2 << '\n';
    }
}