#include <iostream>
#include <vector>
using namespace std;

int N;
bool used[9];

void dfs(int cnt, vector<int>& path){
    if(cnt == N){
        for(const auto& e: path) cout << e << " ";
        cout << "\n";
        return;
    }

    for(int i = 1; i <= N; i++){
        if(used[i]) continue;
        used[i] = true;
        path.push_back(i);
        dfs(cnt + 1, path);
        path.pop_back();
        used[i] = false;
    }
}

int main(){
    cin >> N;
    vector<int> path;
    for(int i = 1; i <= N; i++){
        used[i] = true;
        path.push_back(i);
        dfs(1, path);
        path.pop_back();
        used[i] = false;
    }
    return 0;
}