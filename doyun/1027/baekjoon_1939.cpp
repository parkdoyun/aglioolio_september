#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 백준 1939 - 중량 제한
// dijkstra
// 골드 3

// 갈 수 있는 다리 중 최대 중량을 갖는 다리 선택 
// vertex를 pq에서 꺼낼 때 vertex의 dist의 최대가 아니라 그 vertex로 가는 다리 weight의 최대값을 비교해야 함
// 선택한 경로 내 다리들의 최소값 출력

struct vertex
{
	int idx;
	int chk = -1; // 1 : chk
	//long long dist = 100000000000001;
	long long dist = 0;
	int oppo = -1; // 이걸로 거슬러 올라가기 (b부터 a까지)
};

struct edge
{
	int opposite;
	long long weight;
};

bool operator<(vertex v1, vertex v2)
{
	if (v1.dist < v2.dist)
	{
		return true;
	}
	return false;
}

vector<vertex> V;
vector<vector<edge>> E;
priority_queue<vertex> pq;
int a, b;
long long min1 = 1000000001;

void dijkstra()
{
	while (!pq.empty()) pq.pop();

	pq.push( V[a] );

	while (!pq.empty())
	{
		vertex tmp = pq.top();
		pq.pop();
		if (V[tmp.idx].chk == 1) continue;
		V[tmp.idx].chk = 1;
		V[tmp.idx].dist = tmp.dist;
		V[tmp.idx].oppo = tmp.oppo;
		if (tmp.idx == b) break;

		for (int i = 0; i < E[tmp.idx].size(); i++)
		{
			if (V[E[tmp.idx][i].opposite].chk == -1 &&
				V[E[tmp.idx][i].opposite].dist < E[tmp.idx][i].weight)
			{
				//V[E[tmp.idx][i].opposite].dist = V[tmp.idx].dist + E[tmp.idx][i].weight;
				//V[E[tmp.idx][i].opposite].oppo = tmp.idx;
				pq.push({ E[tmp.idx][i].opposite, -1, E[tmp.idx][i].weight , tmp.idx });
			}
		}
	}

	// b부터 a까지 거슬러 올라가면서 최소 비용 찾기
	vertex tmp = V[b];
	if (tmp.oppo == -1)
	{
		min1 = 0;
		return;
	}
	min1 = tmp.dist;
	while (tmp.oppo != -1)
	{
		tmp = V[tmp.oppo];
		if (tmp.idx == a) break;
		if (tmp.oppo == -1) // 해당되는 경로 존재 X
		{
			min1 = 0;
			return;
		}
		if (min1 > tmp.dist)
		{
			min1 = tmp.dist;
		}
	}
}


int main()
{
	int n, m;
	cin >> n >> m;

	V.resize(n + 1);
	E.resize(n + 1);
	long long c;
	for (int i = 1; i <= n; i++)
	{
		V[i].idx = i;
	}
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		E[a].push_back({ b, c });
		E[b].push_back({ a, c });
	}
	
	cin >> a >> b;

	dijkstra();

	cout << min1;

	return 0;
}