#include <iostream>
#include <queue>

using namespace std;

struct Node{
    int y, x;
};

int M, N; // 가로, 세로
int board[1000][1000];
queue<Node> q;
int tomato_cnt;
int affect_cnt;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

queue<Node> bfs(queue<Node> prev){
    queue<Node> next;

    while(!prev.empty()){
        Node now = prev.front();
        prev.pop();

        for (int i = 0; i < 4; i++){
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
            if (!(0 <= ny && ny < N) || !(0 <= nx && nx < M))
                continue;
            if (board[ny][nx] != 0)
                continue;
            board[ny][nx] = 1;
            affect_cnt++;
            next.push({ny, nx});
        }
    }
    return next;
}

int solution(){
    queue<Node> result = q;
    int day_cnt = 0;
    while(true){
        result = bfs(result);
        if (result.empty())
            break;
        day_cnt++;
    }

    if (tomato_cnt != affect_cnt)
        return -1;
    return day_cnt;
}

void input(){
    cin >> M >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> board[i][j];
            if (board[i][j] == 1)
                q.push({i, j});
            if (board[i][j] == 0)
                tomato_cnt++;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    input();
    cout << solution();

    return 0;
}

/*
보관 후 하루 지나면
익은 토마토 인접 영역 -> 익는다.
며칠 지나면 다 익게 되는지, 최소 일수
*/