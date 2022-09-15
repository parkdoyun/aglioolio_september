#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

typedef struct _posistion{
    int y;
    int x;
}Position;

typedef struct _node{
    Position position;
    int move_cnt;
    int k;
}Node;

int K;
int W, H;
int board[200][200];
int visited[31][200][200];

void init();
void solve();
void bfs();
Position move_like_knight(const Position& cur, int dir, int turn);
Position move_like_pawn(const Position& cur, int dir);
bool is_position_valid(const Position& pos, int k);

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init();
    solve();

    return 0;
}

void init(){
    cin >> K;
    cin >> W >> H;
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            cin >> board[i][j];
        }
    }
    
    for(int k = 0; k <= K; k++){
        for(int i = 0; i < H; i++){
            for(int j = 0; j < W; j++){
                visited[k][i][j] = INT_MAX;
            }
        }
    }
}

void solve(){
    bfs();
    int min_move_cnt = INT_MAX;
    for(int k = 0; k <= K; k++){
        min_move_cnt = min(min_move_cnt, visited[k][H - 1][W - 1]);
    }
    if(min_move_cnt == INT_MAX) cout << -1 << '\n';
    else cout << min_move_cnt << '\n';
}

void bfs(){
    queue<Node> q;
    for(int k = 0; k <= K; k++){
        visited[k][0][0] = 0;
    }
    q.push({{0, 0}, 0, 0});
    
    while(!q.empty()){
        Node cur = q.front();
        q.pop();
        
        for(int dir = 0; dir < 4; dir++){
            Position next = move_like_pawn(cur.position, dir);
            if(!is_position_valid(next, cur.k))
                continue;

            visited[cur.k][next.y][next.x] = cur.move_cnt + 1;
            q.push({next, cur.move_cnt + 1, cur.k});
        }

        if(cur.k < K){
            for(int dir = 0; dir < 4; dir++){
                for(int turn = 0; turn < 2; turn++){
                    Position next = move_like_knight(cur.position, dir, turn);
                    if(!is_position_valid(next, cur.k + 1))
                        continue;
                    
                    visited[cur.k + 1][next.y][next.x] = cur.move_cnt + 1;
                    q.push({next, cur.move_cnt + 1, cur.k + 1});
                }
            }
        }
    }
}

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, -1, 0, 1};

Position move_like_knight(const Position& cur, int dir, int turn){
    // turn 0: left, 1: right
    int ny = -1, nx = -1;
    switch (dir)
    {
        case 0:
        {
            // up
            ny = cur.y - 2;
            nx = turn == 0 ? cur.x - 1 : cur.x + 1;
        }
        break;

        case 1:
        {
            // left
            ny = turn == 0 ? cur.y + 1 : cur.y - 1;
            nx = cur.x - 2;
        }
        break;
        
        case 2:
        {
            // down
            ny = cur.y + 2;
            nx = turn == 0 ? cur.x + 1 : cur.x - 1;
        }
        break;

        case 3:
        {
            // right
            ny = turn == 0 ? cur.y - 1: cur.y + 1;
            nx = cur.x + 2;
        }
        break;
    }
    return {ny, nx};
}
Position move_like_pawn(const Position& cur, int dir){
    return {cur.y + dy[dir], cur.x + dx[dir]};
}
bool is_position_valid(const Position& pos, int k){
    if(pos.y < 0 || pos.x < 0 || pos.y >= H || pos.x >= W)
        return false;
    
    if(board[pos.y][pos.x] == 1)
        return false;

    if(visited[k][pos.y][pos.x] < INT_MAX)
        return false;

    return true;
}