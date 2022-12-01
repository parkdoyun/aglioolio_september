#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

typedef struct __node__{
    int y;
    int x;
}Node;

const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
// top, top-left, left, bottom-left, bottom, bottom-right, right, top-right

// 완전 탐색
// 주어진 단어를 길이가 길고 사전 순으로 앞서는 순으로 정렬
// dfs로 탐색

int N, B;
vector<string> w;
int score[9] = {0, 0, 0, 1, 1, 2, 3, 5, 11};
char b[30][4][4];

bool cmp (const string& l, const string& r){
    if(size(l) > size(r)) return true;
    if(size(l) < size(r)) return false;
    return l < r;
}

void init(){
    cin >> N;
    w.resize(N);
    rep(i, N){
        cin >> w[i];
    }

    cin >> B;
    rep(k, B) rep(i, 4) rep(j, 4) cin >> b[k][i][j];

    sort(all(w), cmp);
}

bool dfs(int idx, Node cur, const char (*board)[4], bool (*visited)[4], const string& word){
    if(idx == size(word) - 1){
        return true;
    }

    bool found = false;
    
    for(int k = 0; k < 8 && !found; k++){
        int ny = cur.y + dy[k];
        int nx = cur.x + dx[k];

        if(ny < 0 || nx < 0 || ny >= 4 || nx >= 4) continue;
        if(board[ny][nx] != word[idx + 1]) continue;
        if(visited[ny][nx]) continue;
        
        visited[ny][nx] = true;
        found |= dfs(idx + 1, {ny, nx}, board, visited, word);
        visited[ny][nx] = false;
    }

    return found;
}

void solve(int idx){
    char (*board)[4] = b[idx];
    
    int total_score = 0;
    string longest_word = "";
    int words_found_cnt = 0;

    for(const auto& target: w){
        // dfs
        vector<Node> start_points;
        rep(i, 4){
            rep(j, 4){
                if(board[i][j] == target[0]) 
                start_points.push_back({i, j});
            }
        }

        bool found = false;
        bool visited[4][4] = {{false, }, };

        for(int i = 0; i < size(start_points) && !found; i++){
            Node start = start_points[i];
            visited[start.y][start.x] = true;
            found |= dfs(0, start, board, visited, target);
            visited[start.y][start.x] = false;
        }

        if(found){
            if(size(longest_word) < size(target))
                longest_word = target;
            total_score += score[size(target)];
            words_found_cnt++;
        }
    }

    cout << total_score << " " << longest_word << " " << words_found_cnt << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init();
    rep(i, B)
        solve(i);

    return 0;
}