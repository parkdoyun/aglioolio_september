#include <iostream>
#include <queue>
using namespace std;

// 백준 1715 - 카드 정렬하기
// greedy
// 골드 4

// 가장 작은 두 수 꺼내서 더한 후 다시 pq에 넣으면 된다
// 가장 작은 비교 수(총 합)는 제일 작은 수끼리 계속 더하는 것

// 최소 힙
priority_queue<int, vector<int>, greater<int>> pq;

int main()
{
	int n;
	cin >> n;

	int a, b;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		pq.push(a);

	}

	int tmp = 0;
	while (!pq.empty())
	{
		if (pq.size() == 1)
		{
			cout << tmp;
			break;
		}
		a = pq.top();
		pq.pop();
		b = pq.top();
		pq.pop();
		tmp += a + b;
		pq.push(a + b);
	}


	return 0;
}