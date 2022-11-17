#include <iostream>
#include <vector>
using namespace std;

int N, S;
int v[20];
int answer;

void dfs(int idx, int sum){
    if(sum == S)
        answer++;

    if(idx == N)
        return;

    for(int i = idx + 1; i < N; i++){
        dfs(i, sum + v[i]);
    }
}

int main(){
    cin >> N >> S;
    for(int i = 0; i < N; i++)
        cin >> v[i];
    
    for(int i = 0; i < N; i++){
        dfs(i, v[i]);
    }
    cout << answer << '\n';

    return 0;
}
