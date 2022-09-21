#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct _node{
    int y;
    int x;
}Node;

int N, M;

int lab[8][8];

void init();
void solve();

int main(void){
    init();
    solve();

    return 0;
}

void init(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> lab[i][j];
        }
    }
}

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, -1, 0, 1};

void bfs(Node start, int (*copy)[8], bool (*visited)[8]){
    queue<Node> q;
    q.push(start);
    visited[start.y][start.x] = true;

    while(!q.empty()){
        Node cur = q.front();
        q.pop();

        copy[cur.y][cur.x] = 2;

        for(int k = 0; k < 4; k++){
            int ny = cur.y + dy[k];
            int nx = cur.x + dx[k];

            if(ny < 0 || nx < 0 || ny >= N || nx >= M)
                continue;
            
            if(copy[ny][nx] != 0)
                continue;
            
            if(visited[ny][nx])
                continue;
            
            visited[ny][nx] = true;
            q.push({ny, nx});
        }
    }
}

int get_safe_area(){
    // bfs
    int copy[8][8];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            copy[i][j] = lab[i][j];
        }
    }

    bool visited[8][8];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++)
            visited[i][j] = false;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(copy[i][j] != 2)
                continue;
            
            if(visited[i][j])
                continue;

            bfs({i, j}, copy, visited);
        }
    }

    int cnt = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(copy[i][j] == 0)
                cnt++;
        }
    }

    return cnt;
}

int answer = 0;
void dfs(int walls){
    if(walls == 0){
        int safe_area = get_safe_area();
        answer = max(answer, safe_area);
        return;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(lab[i][j] != 0) continue;
            lab[i][j] = 1;
            dfs(walls - 1);
            lab[i][j] = 0;
        }
    }
}

void solve(){
    dfs(3);
    cout << answer << '\n';
}