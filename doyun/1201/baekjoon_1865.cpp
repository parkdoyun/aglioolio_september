#include <iostream>
#include <vector>

using namespace std;

// 백준 1865 - 웜홀
// 음수 사이클 생기지 않으면 제자리로 돌아갈 수 없다
// 음수 사이클 안 생기면 무조건 NO
// 음수 사이클 생기고 출발지점 음수로 갱신되면 YES (무조건)

// 이렇게 bellman-ford를 모든 정점에 대해 2 * n만큼 돌면서 확인하면
// 답은 맞으나 시간초과
// 한 정점에 대하여 n-1번 돌면서 V[j].time != INF 부분을 빼면 된다 

// bellman-ford
// 간선의 가중치 음수일 때 사용
// 매번 모든 간선 전부 확인하여 최단 거리 줄일 수 있다면 줄인다.
// 음수 사이클 유의해야 함
// 시간 복잡도 O(N^2)
// dijkstra보다 시간 복잡도 크므로 가중치 모두 양수라면 굳이 사용 X

// 사이클 생긴다면 -1 출력
// 사이클 : n - 1번 순회 이후에도 계속 갱신되는 정점 있다면 음수 사이클 有

#define INF 2000000000

int n, m, w;

struct vertex
{
	int idx;
	long long time = INF; // 출력 초과 나온다면 -> long long으로 바꾸자
};

struct edge
{
	int oppo;
	long long weight;
};

vector<vertex> V;
vector<vector<edge>> E;

int bellmanford(int start) // 0 : NO (cycle X), 1 : YES
{
	V[start].time = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int k = 0; k < E[j].size(); k++)
			{
				if (V[E[j][k].oppo].time > V[j].time + E[j][k].weight)
				{
					if (i == n - 1) // cycle 돌면 무조건 OK
					{
						return 1;
					}
					V[E[j][k].oppo].time = V[j].time + E[j][k].weight;
				}
			}
		}
	}

	return 0;
}

void vertexClr()
{
	for (int i = 1; i <= n; i++) V[i].time = INF;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> n >> m >> w;
		V.resize(n + 1);
		E.resize(n + 1);
		for (int i = 1; i <= n; i++) V[i].idx = i;

		int s, e;
		long long t;
		for (int i = 0; i < m; i++)
		{
			cin >> s >> e >> t;
			E[s].push_back({ e, t });
			E[e].push_back({ s, t });
		}

		// 웜홀 
		for (int i = 0; i < w; i++)
		{
			cin >> s >> e >> t;
			E[s].push_back({ e, t * -1 });
		}

		/*
		int flag = 0;
		for (int i = 1; i <= n; i++)
		{
			// 초기화
			vertexClr();
			if (bellmanford(i) == 1)
			{
				cout << "YES\n";
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout << "NO\n";
		*/

		if (bellmanford(1) == 1) cout << "YES\n";
		else cout << "NO\n";

		V.clear();
		for (int i = 0; i <= n; i++)
		{
			E[i].clear();
		}
	}

	return 0;
}