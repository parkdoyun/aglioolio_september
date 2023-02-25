#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <set>
#include <unordered_map>
using namespace std;

struct Coord{
    int y;
    int x;
};

string plain_text;
string key_string;
unordered_map<char, Coord> literal_position;
array<array<char, 5>, 5> code_table;

void init_code_table();
void init_literal_position();
string insert_cut_characters(string text);
vector<pair<char, char>> text_to_pairs(const string& text);
pair<char, char> encrypt_pair(const pair<char, char>& p);

#ifndef TEST
int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin >> plain_text;
    cin >> key_string;

    init_code_table();
    init_literal_position();

    vector<pair<char, char>> pairs = text_to_pairs(plain_text);
    
    string answer = "";
    for(const auto& p: pairs){
        
        auto encrypted = encrypt_pair(p);
        
        answer.push_back(encrypted.first);
        answer.push_back(encrypted.second);
    }

    cout << answer << '\n';

    return 0;
}
#endif

//#define TEST
#ifdef TEST
int main(){

    vector<pair<char, char>> pairs = text_to_pairs("HELLOWORLD");
    for(const auto& p: pairs){
        cout << p.first << p.second << '\n';
    }

    key_string = "PLAYFAIRCIPHERKEY";
    init_code_table();
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            cout << code_table[i][j] << " ";
        }
        cout << '\n';
    }
}
#endif

void init_code_table(){
    
    set<char> alphabet_remainings;

    for(char c = 'A'; c <= 'Z'; ++c){
        if(c == 'J') continue;
        alphabet_remainings.insert(c);
    }
    
    int pos = 0;
    int idx = 0;
    while(pos < 25){
        
        char c;
        
        if(idx >= key_string.size()){
            auto front = alphabet_remainings.begin();
            c = *front;
        }
        else{
            char key_char = key_string[idx++];
            if(alphabet_remainings.find(key_char) == alphabet_remainings.end()) continue;
            c = key_char;
        }

        int y = pos / 5;
        int x = pos % 5;
        pos++;

        code_table[y][x] = c;
        
        alphabet_remainings.erase(c);
    }
}

void init_literal_position(){
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            literal_position[code_table[i][j]] = {i, j};
        }
    }
}

string insert_cut_characters(string text){
    for(int i = 0; i < text.size(); i += 2){
        
        if(i + 1 >= text.size()) continue;

        if(text[i] != text[i + 1]) continue;

        // 인접하는 두 문자가 동일하다
        if(text[i] == 'X') text.insert(i + 1, "Q");
        else text.insert(i + 1, "X");
    }

    return text;
}

vector<pair<char, char>> text_to_pairs(const string& text){
    // HE LLO WO RL DX
    string modified = insert_cut_characters(text);
    modified.push_back('X');

    // HE LX LO WO RLDX
    vector<pair<char, char>> ret;
    for(int i = 0; i < modified.size() - 1; i += 2){
        ret.push_back({modified[i], modified[i + 1]});
    }

    return ret;
}

pair<char, char> encrypt_pair(const pair<char, char>& p){

    // HE
    Coord h = literal_position[p.first];
    Coord t = literal_position[p.second];

    pair<char, char> ret;
    // 두 문자가 코드표의 같은 행에 위치할 때, 오른쪽에 위치한 문자로 변환
    if(h.y == t.y){
        ret.first = code_table[h.y][(h.x + 1) % 5];
        ret.second = code_table[t.y][(t.x + 1) % 5];

        return ret;
    }

    // 두 문자가 코드표의 같은 열에 위치할 때
    if(h.x == t.x){
        ret.first = code_table[(h.y + 1) % 5][h.x];
        ret.second = code_table[(t.y + 1) % 5][t.x];

        return ret;
    }

    // 위 두 조건을 둘 다 만족하지 않을 떄
    ret.first = code_table[h.y][t.x];
    ret.second = code_table[t.y][h.x];

    return ret;
}


