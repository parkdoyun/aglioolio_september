#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 백준 9370 - 미확인 도착지
// dijkstra
// 골드 2

// 최단경로 여러개 있을 경우 포함해야 함
// gh 도로만 미세하게 값을 빼주어(1보다 작은) 같은 최단 경로 비용일 때 gh가 포함된 경로가 채택이 되도록 구현 

int n, m, t, g, h, a, b, d, x;

struct vertex
{
	int num;
	int dist = 100000000;
	int visit = 0;
	vector<int> path;
};

struct bus
{
	int arrive;
	int cost;
};

bool operator<(vertex v1, vertex v2)
{
	if (v1.dist > v2.dist) return true;
	return false;
}

bool cmp(int a, int b) {
	if (a < b) return true;
	return false;
}
vector<vertex> V;
vector<vector<bus>> E;
priority_queue<vertex> pq;
vector<int> dest;

int main()
{
	int T;
	cin >> T;

	int start;
	for (int tc = 0; tc < T; tc++)
	{
		cin >> n >> m >> t;
		cin >> start >> g >> h;

		V.resize(n + 1);
		E.resize(n + 1);

		for (int i = 1; i <= n; i++) V[i].num = i;

		for (int i = 0; i < m; i++)
		{
			cin >> a >> b >> d;
			if ((a == g && b == h) || (a == h && b == g)) d = d - 0.01; // gh 경로만 값을 미세하게 조정
			E[a].push_back({ b, d });
			E[b].push_back({ a, d });
		}

		for (int i = 0; i < t; i++)
		{
			cin >> x;
			dest.push_back(x);
		}

		V[start].dist = 0;
		pq.push(V[start]);

		while (!pq.empty())
		{
			vertex tmp = pq.top();
			pq.pop();
			if (V[tmp.num].visit == 2) continue;
			V[tmp.num].visit = 2;
			V[tmp.num].path.push_back(tmp.num);

			for (int i = 0; i < E[tmp.num].size(); i++)
			{
				if (V[E[tmp.num][i].arrive].visit == 0 && V[E[tmp.num][i].arrive].dist >= tmp.dist + E[tmp.num][i].cost)
				{
					V[E[tmp.num][i].arrive].dist = tmp.dist + E[tmp.num][i].cost;
					// path 변경
					vector<int> tmp_p = V[tmp.num].path;
					tmp_p.push_back(tmp.num);
					V[E[tmp.num][i].arrive].path = tmp_p;
					pq.push(V[E[tmp.num][i].arrive]);
				}
			}

		}

		// 목적지 확인
		// 오름차순 정렬
		sort(dest.begin(), dest.end(), cmp);
		// path에 g h 있는지 확인 -> 가능
		for (int i = 0; i < t; i++)
		{
			for (int j = 0; j < V[dest[i]].path.size(); j++)
			{
				if (V[dest[i]].path[j] == g)
				{
					if ((j >= 1 && V[dest[i]].path[j - 1] == h) || (j < V[dest[i]].path.size() - 1 && V[dest[i]].path[j + 1] == h))
					{
						cout << dest[i] << ' ';
						break;
					}
				}
			}
		}
		cout << '\n';

		// 초기화
		while (!V.empty()) V.pop_back();
		while (!E.empty()) E.pop_back();
		while (!pq.empty()) pq.pop();
		while (!dest.empty()) dest.pop_back();
	}
	
	return 0;
}