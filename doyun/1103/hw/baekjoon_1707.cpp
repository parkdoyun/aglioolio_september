#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 백준 1707 - 이분 그래프
// bfs
// 골드 4

// 모든 둘로 나눈 집합 다 구한다 => backtracking
// 인접하지 않도록 분할되는지 확인 => DFS
// 0번 팀, 1번 팀
// 시간 초과

// bfs를 하면서 나와 인접한 애들을 다른 팀으로 체크
// 이미 방문되고 인접한데 나와 같은 팀이 있다면 -> NO
// 다 체크된다면 -> YES

// 주의할 점 : 그래프가 떨어져 있을 수 있음 -> visitChk로 검사
// 모든 출발지부터 다 해봐야 함
// 시간 초과 => while문을 한번 더 해서 => 해결

int visit[20001];
int team[20001]; // 1, -1
int v;

struct edge
{
	int oppo;
};

vector<vector<edge>> E;

void visitClr(int v)
{
	for (int i = 1; i <= v; i++) visit[i] = 0;
}

int visitChk(int v)
{
	for (int i = 1; i <= v; i++)
	{
		if (visit[i] == 0) return i;
	}
	return -1;
}

// visit 안 한 곳 중 현재 나랑 team 같은 애들 있으면 chk = 1
int total_chk;
int chk;

struct node
{
	int num;
	int prev;
};
queue<node> q;
void BFS(int start)
{
	while (!q.empty()) q.pop();

	q.push({ start, 1 });

	while (!q.empty())
	{
		node tmp = q.front();
		q.pop();

		if (visit[tmp.num] == 1) continue;
		visit[tmp.num] = 1;

		team[tmp.num] = tmp.prev * -1;
		
		for (int i = 0; i < E[tmp.num].size(); i++)
		{
			if (visit[E[tmp.num][i].oppo] == 1 && (team[E[tmp.num][i].oppo] == team[tmp.num]))
			{
				chk = 1;
				return;
			}
			else if (visit[E[tmp.num][i].oppo] == 1) continue;
			q.push({E[tmp.num][i].oppo, team[tmp.num]});
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T, e;
	cin >> T;
	E.resize(20001);
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> v >> e;
		total_chk = -1;
		for (int i = 0; i < e; i++)
		{
			int a, b;
			cin >> a >> b;
			E[a].push_back({ b });
			E[b].push_back({ a });
		}

		visitClr(v);
		chk = -1;
		for (int i = 1; i <= v; i++)
		{
			// 굳이 다 while() 할 필요가 X

			//visitClr(v);
			//chk = -1;
			/*
			while (true)
			{
				int s = visitChk(v);
				if (s == -1 || chk == 1) // 다 방문했다면
				{
					break;
				}
				BFS(s);
			}
			*/
			int s = visitChk(v);
			if (s == -1) break;
			BFS(s);

		}

		if (chk == -1) total_chk = 1;

		if (total_chk == -1) cout << "NO\n";
		else cout << "YES\n";

		// 초기화
		for (int i = 0; i <= v; i++) E[i].clear();
		//E.clear();
	}

	return 0;
}