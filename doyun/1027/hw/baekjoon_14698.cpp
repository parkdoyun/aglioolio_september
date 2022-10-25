#include <iostream>
#include <queue>

using namespace std;

// 백준 14698 - 전생했더니 슬라임 연구자였던 건에 대하여 (Hard)
// greedy
// 골드 4


struct node
{
	unsigned long long n;
};

bool operator<(node n1, node n2)
{
	if (n1.n > n2.n) return true;
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	priority_queue<node> pq;

	unsigned long long res;
	int T;
	cin >> T;
	int n;
	unsigned long long a;
	for (int tc = 1; tc <= T; tc++)
	{
		while (!pq.empty()) pq.pop();

		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> a;
			pq.push({ a });
		}

		unsigned long long b, c, tmp;
		res = 1;

		while (pq.size() > 1)
		{
			b = pq.top().n;
			pq.pop();
			c = pq.top().n;
			pq.pop();

			tmp = b * c;

			/*
			if (pq.empty())
			{
				tmp = tmp % 1000000007;
				res = res % 1000000007;
				res = (unsigned long long)(res * tmp % 1000000007);
			}
			else res = (unsigned long long)(res * tmp);
			*/


			pq.push({ tmp });
			tmp %= 1000000007;
			res = (unsigned long long)(res * tmp);
			res %= 1000000007;
		}

		cout << res << '\n';

	}



	return 0;
}