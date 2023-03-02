#include <iostream>
#include <queue>

using namespace std;

// softeer - 금고털이
// 별 2개
// greedy

struct jewel
{
	long long int price;
	long long int weight;
};
bool operator<(jewel j1, jewel j2)
{
	if (j1.price < j2.price) return true;
	return false;
}
priority_queue<jewel> pq;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long int w, n, m, p;
	cin >> w >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> m >> p;
		pq.push({ p, m });
	}

	long long int now_w = 0;
	long long int total_price = 0;
	while (!pq.empty())
	{
		jewel tmp = pq.top();
		pq.pop();

		if (now_w + tmp.weight > w)
		{
			// 자르기
			total_price += (tmp.price * (w - now_w));
			break;
		}
		else // 그냥 넣기
		{
			total_price += (tmp.price * tmp.weight);
			now_w += tmp.weight;
		}
	}

	cout << total_price;

	return 0;
}