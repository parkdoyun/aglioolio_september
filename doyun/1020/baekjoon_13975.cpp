#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

// 백준 13975 - 파일 합치기 3
// greedy
// 골드 4

struct node
{
	long long a;
};
bool operator<(node n1, node n2)
{
	if (n1.a > n2.a) return true;
	return false;
}
priority_queue<node> pq;

int main()
{
	int T;
	cin >> T;
	int k;
	long long a, b;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> k;
		long long res = 0;
		long long total = 0;
		while (!pq.empty()) pq.pop();
		for (int i = 0; i < k; i++)
		{
			cin >> a;
			pq.push({ a });
			total += a;
		}

		while ((pq.size()) > 1)
		{
			a = pq.top().a;
			pq.pop();
			b = pq.top().a;
			pq.pop();
			pq.push({ a + b });
			res += a + b;
		}

		
		cout << res << '\n';

	}

	return 0;
}