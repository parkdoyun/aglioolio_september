#include <iostream>
#include <queue>

using namespace std;

// 백준 1655 - 가운데를 말해요
// priority queue
// 골드 2
// 1시간 반

// 최대 힙 1개, 최소 힙 1개
// 두 힙 사이에서 중간 값 나올 때까지 왔다갔다


struct node
{
	int val;
};

struct node2
{
	int val;
};

// 최소 힙
bool operator<(node n1, node n2)
{
	if (n1.val > n2.val) return true;
	return false;
}

// 최대 힙
bool operator<(node2 n1, node2 n2)
{
	if (n1.val < n2.val) return true;
	return false;
}

priority_queue<node> pq_min;
priority_queue<node2> pq_max;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, a, tmp;
	cin >> n >> a;
	pq_max.push({ a });
	cout << a << '\n';

	for (int i = 1; i < n; i++)
	{
		cin >> a;

		// push
		if (pq_max.empty()) pq_min.push({ a });
		else if(pq_min.empty()) pq_max.push({ a });
		else
		{
			if (pq_max.top().val > a) pq_max.push({ a });
			else pq_min.push({ a });
		}

		// 중간 찾기 (두 힙 갯수 같아질 때까지)
		while (pq_min.size() != pq_max.size() && pq_min.size() + 1 != pq_max.size())
		{
			if (pq_max.size() > pq_min.size() + 1)
			{
				tmp = pq_max.top().val;
				pq_max.pop();
				pq_min.push({ tmp });
			}
			else
			{
				tmp = pq_min.top().val;
				pq_min.pop();
				pq_max.push({ tmp });
			}
		}

		cout << pq_max.top().val << '\n';
		
	}

	return 0;

}