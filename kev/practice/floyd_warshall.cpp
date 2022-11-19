#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define size(v) (int)((v).size())
#define INF 1000000
int main(){
    int N = 4;
    vector<vector<int>> w = {
        {0, 5, INF, 8},
        {7, 0, 9, INF},
        {2, INF, 0, 4},
        {INF, INF, 3, 0}
    };

    for(int k = 0; k < N; k++){
        // i: 출발 노드
        for(int i = 0; i < N; i++){
            // j: 도착 노드
            for(int j = 0; j < N; j++){
                if(w[i][k] + w[j][k] >= w[i][j]) continue;
                w[i][j] = w[i][k] + w[k][j];
            }
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << w[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}