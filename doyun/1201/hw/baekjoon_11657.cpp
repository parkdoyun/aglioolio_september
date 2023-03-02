#include <iostream>
#include <vector>

using namespace std;

// 백준 11657 - 타임머신
// bellman-ford
// 골드 4

// bellman-ford
// 간선의 가중치 음수일 때 사용
// 매번 모든 간선 전부 확인하여 최단 거리 줄일 수 있다면 줄인다.
// 음수 사이클 유의해야 함
// 시간 복잡도 O(N^2)
// dijkstra보다 시간 복잡도 크므로 가중치 모두 양수라면 굳이 사용 X

// 사이클 생긴다면 -1 출력
// 사이클 : n - 1번 순회 이후에도 계속 갱신되는 정점 있다면 음수 사이클 有

#define INF 1000000000

int n, m;

struct vertex
{
	int idx;
	long long time = INF;
};

struct edge
{
	int oppo;
	long long weight;
};

vector<vertex> V;
vector<vector<edge>> E;

int bellmanFord(int start)
{
	V[start].time = 0;

	for (int i = 0; i < n; i++) // n-1번 확인 (n번째에 줄어드는 애 있으면 음수 사이클 존재)
	{
		// 모든 edge 전부 확인
		for (int j = 1; j <= n; j++)
		{
			for (int k = 0; k < E[j].size(); k++)
			{
				if (V[j].time != INF && V[E[j][k].oppo].time > V[j].time + E[j][k].weight)
				{
					if (i == n - 1) return -1;
					V[E[j][k].oppo].time = V[j].time + E[j][k].weight;
				}
			}
		}
	}
	return 0;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	V.resize(n + 1);
	E.resize(n + 1);

	for (int i = 1; i <= n; i++) V[i].idx = i;

	int a, b;
	long long c;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		E[a].push_back({ b, c });
	}

	if (bellmanFord(1) == -1)
	{
		cout << -1;
	}
	else
	{
		for (int i = 2; i <= n; i++)
		{
			if (V[i].time == INF) cout << -1 << '\n';
			else cout << V[i].time << '\n';
		}
	}
	

	return 0;
}