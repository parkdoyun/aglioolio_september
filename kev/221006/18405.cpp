#include <iostream>
#include <queue>
using namespace std;

typedef struct _coord2D_ {
    int y;
    int x;
}Coord2D;

typedef struct _virus_ {
    int k;
    Coord2D pos;
}Virus;

bool operator < (const Virus& l, const Virus& r){
    return r.k < l.k;
}

int N, K;
int S, X, Y;
int grid[201][201];

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, -1, 0, 1};

int main(){
    priority_queue<Virus> pq;
    cin >> N >> K;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            int k; cin >> k;
            
            grid[i][j] = k;
            if(k > 0) pq.push({k, {i, j}});
        }
    }
    cin >> S >> X >> Y;
    
    // 증식은 낮은 번호의 바이러스부터 시작
    // 상하좌우로 증식, 증식하려는 칸에 다른 바이러스가 있다면 증식할 수 없음
    // grid 좌상단부터 증식시키되 같은 시간에 겹치는 곳은 낮은 번호의 바이러스가 해당 셀을 차지하도록
    // 해당 셀을 언제 차지하였는지 알 필요가 있음?
    // 우선 순위 큐를 쓸 것. 번호가 낮을 수록 우선 순위가 높다.
    int tic = 0;
    while(tic++ < S){
        vector<Virus> next_gen;
        while(!pq.empty()){
            Virus virus = pq.top();
            pq.pop();

            for(int k = 0; k < 4; k++){
                int ny = virus.pos.y + dy[k];
                int nx = virus.pos.x + dx[k];

                if(ny <= 0 || ny > N || nx <= 0 || nx > N)
                    continue;
                
                if(grid[ny][nx] > 0)
                    continue;
                grid[ny][nx] = virus.k;
                
                next_gen.push_back({virus.k, {ny, nx}});
            }
        }

        // 더 이상 바이러스가 증식할 수 없다.
        if(next_gen.empty()) break;
        
        for(const auto& virus: next_gen){
            pq.push(virus);
        }
    }

    cout << grid[X][Y] << '\n';

    return 0;
}