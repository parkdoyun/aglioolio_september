#include <iostream>
#include <queue>

using namespace std;

struct Node{
    int y, x;
};

int N;
int board[100][100];
int visited[2][100][100];

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

void bfs(Node start, int mode){
    queue<Node> q;
    q.push(start);

    while(!q.empty()){
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++){
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
            if (!(0 <= ny && ny < N) || !(0 <= nx & nx < N))
                continue;
            if (mode == 0){
                if (board[ny][nx] != board[start.y][start.x])
                    continue;
            }
            else{
                if (abs(board[ny][nx]) != abs(board[start.y][start.x]))
                    continue;
            }
            if (visited[mode][ny][nx] != 0)
                continue;
            visited[mode][ny][nx] = 1;
            q.push({ny, nx});
        }
    }
}

vector<int> solution(){
    vector<int> ret;
    for (int mode = 0; mode < 2; mode++){
        int cnt = 0;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N ; j++){
                if (visited[mode][i][j] != 0)
                    continue;
                cnt++;
                bfs({i, j}, mode);
            }
        }
        ret.push_back(cnt);
    }
    return ret;
}

void input(){
    cin >> N;
    string row;
    for (int i = 0; i < N; i++){
        cin >> row;
        for (int j = 0; j < N; j++){
            if (row[j] == 'R')
                board[i][j] = -1;
            if (row[j] == 'G')
                board[i][j] = 1;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    input();
    vector<int> result = solution();
    cout << result[0] << " " << result[1];

    return 0;
}

/*
NxN Grid - RGB 중 하나
한 구역은 같은 색으로 이루어짐
인접한 경우 같은 구역에 속한 것이다

적록색약 : 빨간색 + 초록색

*/