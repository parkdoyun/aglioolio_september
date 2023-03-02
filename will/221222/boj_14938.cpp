#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M, R, Ans;
struct Area{int to, cost; };
vector<int> Items, Dist;
vector<vector<Area>> AdjList;

struct cmp{
    bool operator()(Area a, Area b){
        if (a.cost > b.cost) return true;
        if (a.cost < b.cost) return false;
        return false;
    }
};

void dijkstra(int start){
    priority_queue<Area, vector<Area>, cmp> pq;
    pq.push({start, 0});
    Dist[start] = 0;

    while(!pq.empty()){
        Area now = pq.top();
        pq.pop();

        for (int i = 0; i < AdjList[now.to].size(); i++){
            Area next = AdjList[now.to][i];
            if (Dist[now.to] + next.cost < Dist[next.to]){
                Dist[next.to] = Dist[now.to] + next.cost;
                pq.push(next);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(), cout.tie();

    freopen("../SampleInput/input.txt", "r", stdin);
    
    int sumAns = 0;
    cin >> N >> M >> R;
    Items.resize(N + 1);
    for (int i = 1; i <= N; i++){
        cin >> Items[i];
    }

    AdjList.resize(N + 1);
    for (int i = 0; i < R; i++){
        int from, to, cost;
        cin >> from >> to >> cost;
        AdjList[from].push_back({to, cost});
        AdjList[to].push_back({from, cost});
    }

    for (int start = 1; start <= N; start++){
        Dist.resize(N + 1, 2e9);
        dijkstra(start);

        int sum = Items[start];
        for (int i = 0; i < N + 1; i++){
            if (0 < Dist[i] && Dist[i] <= M){
                sum += Items[i];
            }
        }

        Ans = max(Ans, sum);
        Dist.clear();
    }

    cout << Ans << '\n';

    Items.clear();
    AdjList.clear();
    return 0;
}
/*
- 이번 문제의 핵심이자 내가 단번에 파악 못했던 부분
  -> Vertex 에 '도달' 할 수 있고, M 이내의 거리에 존재한다면
  -> 해당 영역의 Item 수를 더해주기만 하면돼
  -> 따라서 이 문제는 Vertex 까지의 최소 비용을 구하는 문제가 되고
  -> 결국 Dijkstra 문제로 귀결이 되는 것

- 잘못이해한 부분
  -> 모든 경로가 아닌 갈 수 있는 경로 상에서 최대 개수로 생각함

- 시도하면서 구현을 못한 부분
  -> DFS로 접근해서, 종료 조건 설정에 어려움을 겪음
     : 양방향이므로, to, from 이 같고 lvl != 0 일때를 고려했지만
       기조 조건을 만나기전에 범위조건(<= M)을 벗어나 종료되는 경우가 생김
       이에 따라, 기저 조건에서 지나온 item 갯수를 합쳐주는 것이 까다로워짐
  -> 이러면서 점점 포기하기 시작함

- 핵심 아이디어는 결국, 해당 node 에 도달 가능하다/안하다 로 나뉘어지고,
  이는 다익스트라로 간단하게 알 수 있다는 것을 파악하는 것이다
  문제를 많이 보고 빠르게 파악할 수 있는 능력을 키우자
*/