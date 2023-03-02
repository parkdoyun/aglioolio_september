// N * N 보드
// (N - 1) * (N - 1) 닫힌 칸 존재
// (N - 1)^2 개의 지뢰가 모두 있다고 가정한다
// 닫힌 칸들 중 가장 바깥쪽에 있는 닫힌 칸들을 닫힌 칸 테두리라고 하자

#include <iostream>
#include <vector>
using namespace std;

void init();
void solve();

int main(){
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    init();
    solve();

    return 0;
}


int N;
vector<vector<char>> board;

void init(){

    cin >> N;

    board.resize(N);

    for(auto& row: board){
        
        row.resize(N);
        
        for(auto& e: row){
            
            cin >> e;
        }
    }
}

const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};

bool is_mine_valid(int y, int x){
    
    for(int k = 0; k < 8; ++k){
        int ny = y + dy[k];
        int nx = x + dx[k];

        if(ny < 0 || nx < 0 || ny >= N || nx >= N)
            continue;
        
        if(board[ny][nx] == '#')
            continue;
        
        int possible_mines = board[ny][nx] - '0';
        
        if(possible_mines <= 0)
            return false;
    }

    return true;
}

void put_mine(int y, int x){
    for(int k = 0; k < 8; ++k){
        int ny = y + dy[k];
        int nx = x + dx[k];

        if(ny < 0 || nx < 0 || ny >= N || nx >= N)
            continue;

        if(board[ny][nx] == '#')
            continue;
        
        int possible_mines = board[ny][nx] - '0';
        board[ny][nx] = --possible_mines + '0';
    }
}

void solve(){

    if( (N - 2) <= 0){
        cout << "0" << '\n';
        return;
    }

    int cnt = (N - 2) * (N - 2); // 놓을 수 있는 최대 지뢰
    
    for(int i = 1; i < N - 1; ++i){
        
        for(int j = 1; j < N - 1; ++j){
            
            if(i != 1 && i != N - 2 && j != 1 && j != N - 2)
                continue;
            
            if(is_mine_valid(i, j)){
                put_mine(i, j);
            }
            else{
                cnt--;
            }
        }
    }

    cout << cnt << '\n';
}