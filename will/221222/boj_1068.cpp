#include <iostream>
#include <vector>
using namespace std;

int N, DelN, Ans;
vector<vector<int>> AdjL;

void dfs(int now){
    if (now == DelN){ return; }
    if (AdjL[now].empty()){
        // leaf node 일 때
        Ans++;
        return;
    }

    for (int i = 0; i < AdjL[now].size(); i++){
        // child node 1개 + 근데, 그 노드가 삭제해야되는 노드일 때
        if (AdjL[now].size() == 1 and AdjL[now][i] == DelN){ Ans++; }
        else{ dfs(AdjL[now][i]); }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(), cout.tie();

    freopen("../SampleInput/input.txt", "r", stdin);

    cin >> N;
    AdjL.resize(N);
    int root = 0;
    for (int i = 0; i < N; i++){
        int parent;
        cin >> parent;
        if (parent == -1){ 
            root = i; 
            continue;
        }
        AdjL[parent].push_back(i);
    }
    cin >> DelN;

    dfs(root);
    cout << Ans << '\n';

    return 0;
}
/*
처음 시도: 막무가내로 트리로 접근하려고 시도
다음 시도: 풀이를 참고함 
         -> 단순 dfs를 통해 연결된 child 만 체크하면 됐음
         -> 조건 하나를 빼먹어서 틀렸음
         --> 자식 노드가 1개인데, 해당 노드가 삭제 대상인 경우 
             현재의 노드는 leaf 노드가 됨 -> cnt++;

= 무작정 자료구조라 생각하고 달려들지 말자 =
*/