#include <algorithm>
#include <cmath>
#include <limits.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define iterate(it, v) for(auto it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())

struct Point{
    int r, c;
};

int N, M;
int grid[1025][1025];
int acc[1025][1025];
vector<pair<Point, Point>> bounds; 

void init();
void solve();

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    init();
    solve();
    return 0;
}

void init(){
    cin >> N >> M;
    vector<pair<Point, Point>> tmp_bounds(M);
    rep(i, N)
        rep(j, N)
            cin >> grid[i + 1][j + 1];
    rep(i, M){
        cin >> tmp_bounds[i].first.r
            >> tmp_bounds[i].first.c
            >> tmp_bounds[i].second.r
            >> tmp_bounds[i].second.c;
    }
    swap(bounds, tmp_bounds);
}

void solve(){
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= N; j++){
            if(i == 0 || j == 0){
                acc[i][j] = 0;
            }
            else{
                acc[i][j] = grid[i][j] 
                            + acc[i - 1][j] 
                            + acc[i][j - 1] 
                            - acc[i - 1][j - 1];
            }
        }
    }
    
    for(const auto& bound: bounds){
        Point p = bound.first;
        Point q = bound.second;
        int a = acc[q.r][q.c];
        int b = acc[q.r][p.c - 1];
        int c = acc[p.r - 1][q.c];
        int d = acc[p.r - 1][p.c - 1];
        cout << a - b - c + d << '\n';
    }
}