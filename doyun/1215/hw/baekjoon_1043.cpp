#include <iostream>
#include <vector>

using namespace std;

// 백준 1043 - 거짓말
// union-find
// 골드 4

// 진실 아는 사람들이 포함되면 무조건 진실 말해야 함 
// 여기에 다른 포함되지 않은 사람들 모두 진실 말해야 함

// 연결 그래프로 풀자 (진실만을 들어야 하는 애들끼리 연결)
// 진실을 아는 사람들과 같은 날 있는 애들 모두 연결 => 연쇄적 연결(union-find) 
// 모든 그래프 전부 확인 (진실 들어야 하는 애들 포함되면 무조건 1로)
// 진실 아는 사람과 연결되지 않은 애들 있는 날 (거짓말 하는 날) chk

int n, m, true_n;
int V[51]; // 0 : 과장된 말 들어도 됨, 1 : 진실 들어야 함
vector<vector<int>> party; // 파티 명단
int root[51];

int find(int a)
{
	if (root[a] == a) return a;
	return find(root[a]);
}

void Union(int a, int b)
{
	int a_root = find(a);
	int b_root = find(b);
	if (a_root == b_root) return;

	if (V[a_root] == 0 && V[b_root] == 1)
	{
		root[a_root] = b_root;
	}
	else // 둘다 0이거나 A가 1 => 무조건 A에 붙임
	{
		root[b_root] = a_root;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);


	cin >> n >> m >> true_n;

	party.resize(m + 1);
	for (int i = 1; i <= n; i++)
	{
		root[i] = i; // 처음에 루트는 자기 자신
	}
	int a;
	for (int i = 0; i < true_n; i++)
	{
		cin >> a;
		V[a] = 1;
	}
	
	int party_n;
	for (int i = 0; i < m; i++)
	{
		cin >> party_n;
		int prev, now;
		for (int j = 0; j < party_n; j++)
		{
			if (j == 0)
			{
				cin >> prev;
				party[i].push_back(prev);
			}
			else
			{
				cin >> now;
				Union(prev, now);
				prev = now;
			}
		}
	}

	// 하나씩 전부 훑으면서 root가 1이면 1로 바꿈
	for (int i = 1; i <= n; i++)
	{
		if (V[find(i)] == 1) V[i] = 1;
	}

	int cnt = 0;
	for (int i = 0; i < m; i++)
	{
		if (V[party[i][0]] == 0) cnt++;
	}

	cout << cnt;

	return 0;
}