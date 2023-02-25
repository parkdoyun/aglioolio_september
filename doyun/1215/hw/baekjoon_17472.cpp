#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 백준 17472 - 다리 만들기 2
// union-find, BFS
// 골드 1

// 0. 섬에 번호 매기기 (BFS)
// 1. 일단 모든 섬 간 다리 구해놓자
// 2. dijkstra로 연결
// 2-1. dijkstra 기준이 여기까지 오는 총 다리의 합의 기준으로 해야 함 (모든 다리들의 합으로)
// 2-2. dijkstra 말고 union-find로 하자
// 3. 모두 연결됐는지 확인 => 이거 착각
// ** 다 같은 루트여야 함!(모두 연결) 그냥 연결됐다고 끝이 아님 **

int n, m;
int board[11][11];
int chk[11][11];
int y_mov[] = { -1, 1, 0, 0 };
int x_mov[] = { 0, 0, -1, 1 };
int total = 0;

struct node
{
	int y;
	int x;
	int idx;
};
queue<node> q; // 바다랑 연결된 지역들 넣는 큐

struct vertex
{
	int idx;
	int dist = 10000000;
	int root;
	int chk = -1;
};

bool operator<(vertex v1, vertex v2)
{
	if (v1.dist > v2.dist) return true;
	return false;
}

struct edge
{
	int oppo;
	int weight;
	int me;
};
bool operator<(edge e1, edge e2)
{
	if (e1.weight > e2.weight) return true;
	return false;
}

vector<vertex> V;
vector<vector<edge>> E;
priority_queue<edge> pq;

void chkClear()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) chk[i][j] = 0;
	}
}

queue<node> q1; // 섬 구별하기 위한 큐
void makeIsland(int y, int x, int idx)
{
	// 4방향 중에 하나만 바다랑 연결되어도 queue에 넣어놓는다
	while (!q1.empty()) q1.pop();

	q1.push({ y, x, idx });

	while (!q1.empty())
	{
		node tmp = q1.front();
		q1.pop();

		if (chk[tmp.y][tmp.x] == 1) continue;
		chk[tmp.y][tmp.x] = 1;
		board[tmp.y][tmp.x] = idx;

		int flag = 1;

		int tx, ty;
		for (int i = 0; i < 4; i++)
		{
			tx = tmp.x + x_mov[i];
			ty = tmp.y + y_mov[i];
			if (ty >= 0 && ty < n &&
				tx >= 0 && tx < m &&
				chk[ty][tx] == 0)
			{
				if (board[ty][tx] == 1)
				{
					q1.push({ ty, tx });
				}
				else flag = 0; // 바다와 연결됨
			}
		}

		if (flag != 1) // 바다랑 연결되었다면
		{
			q.push({ tmp.y, tmp.x, idx });
		}
	}
}

void makeBridge() // 다리 만들기
{
	while (!q.empty())
	{
		node tmp = q.front();
		q.pop();

		// 네방향 모두 해보기
		int len;
		int ty, tx;
		for (int i = 0; i < 4; i++)
		{
			len = 0;
			ty = tmp.y;
			tx = tmp.x;
			while (true)
			{
				ty += y_mov[i];
				tx += x_mov[i];
				len++;
				if (ty < 0 || ty >= n || tx < 0 || tx >= m) break;
				else if (board[ty][tx] != 0 && board[ty][tx] == tmp.idx)
				{
					break;
				}
				else if (board[ty][tx] != 0 && board[ty][tx] != tmp.idx)
				{
					if (len > 2)
					{
						E[tmp.idx].push_back({ board[ty][tx], len - 1, tmp.idx });
						pq.push(E[tmp.idx].back()); // pq에 삽입
					}
					break;
				}
			}
		}
	}
}

int findRoot(int a)
{
	if (V[a].root == a) return a;
	return findRoot(V[a].root);
}

void Union(int a, int b, int w)
{
	int ar = findRoot(a);
	int br = findRoot(b);
	if (ar == br) return;
	total += w;

	V[a].chk = 1;
	V[b].chk = 1;

	if (ar == a)
	{
		V[ar].root = br;
	}
	else V[br].root = ar;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) cin >> board[i][j];
	}

	// 섬 번호 매기기
	int idx = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (board[i][j] != 0 && chk[i][j] == 0)
			{
				makeIsland(i, j, idx);
				idx++;
			}
		}
	}

	idx--; // 섬 갯수
	V.resize(idx + 1);
	E.resize(idx + 1);

	for (int i = 1; i <= idx; i++)
	{
		V[i].idx = i;
		V[i].root = i; // 루트는 자기 자신
	}

	// 다리 구하기
	makeBridge();

	// 섬 연결
	while (!pq.empty())
	{
		edge tmp = pq.top();
		pq.pop();
		
		Union(tmp.me, tmp.oppo, tmp.weight);
	}

	// 다 연결되었는지 확인
	// ** 다 같은 루트여야 함!(모두 연결) 그냥 연결됐다고 끝이 아님 **
	int totalflag = 0;
	int root = findRoot(1);
	for (int i = 2; i <= idx; i++)
	{
		if (findRoot(i) != root) // 연결 안 됨
		{
			totalflag = 1;
			break;
		}
	}

	if (totalflag == 0) cout << total;
	else cout << -1;
	

	return 0;
}