#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

// 백준 1202 - 보석 도둑
// greedy
// 골드 2

// 각 가방에 넣을 수 있는 애들 따로
// 1순위 가격 2순위 무게로 정렬
// 가방 최대 무게 무거운 순으로 정렬
// 1번부터 가방에 넣자

// pq에 넣고(현재 가방에 넣을 수 있는 애들) 그 중 가격 높은 애들을 넣는다
// 자료구조 2개 필요

// 가격 제일 높은 거 비교하는 pq (가격 높은 게 우선순위)
// 모든 보석들 다 넣은 pq (무게 낮은 애들)
// 가방 작은 애들부터 확인

struct jewel
{
	long long m;
	long long v;
};

struct jewel2
{
	long long m;
	long long v;
};

bool operator<(jewel j1, jewel j2)
{
	if (j1.m > j2.m) return true;
	return false;
}

bool operator<(jewel2 j1, jewel2 j2)
{
	if (j1.v < j2.v) return true;
	return false;
}

priority_queue<jewel> pq;
priority_queue<jewel2> pq_cmp;
long long bag[300001];

bool cmp2(long long a, long long b)
{
	if (a < b) return true;
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);


	int n, k;
	cin >> n >> k;
	jewel j;
	for (int i = 0; i < n; i++)
	{
		cin >> j.m >> j.v;
		pq.push(j);
	}
	for (int i = 0; i < k; i++)
	{
		cin >> bag[i];
	}

	long long total = 0;
	sort(bag, bag + k, cmp2);

	for (int i = 0; i < k; i++) {
		jewel2 tmp;
		while (!pq.empty() && pq.top().m <= bag[i])
		{
			tmp.m = pq.top().m;
			tmp.v = pq.top().v;
			pq_cmp.push(tmp);
			pq.pop();
		}
		if (pq_cmp.empty()) continue; // 이거 안 넣으면 double free error
		total += pq_cmp.top().v;
		pq_cmp.pop();
		/*
		jewel tmp1;
		while (!pq_cmp.empty()) // 다시 뺄 필요 X => 어차피 더 큰 가방을 확인하므로
		{
			tmp1.m = pq_cmp.top().m;
			tmp1.v = pq_cmp.top().v;
			pq.push(tmp1);
			pq_cmp.pop();
		}
		*/
	}

	cout << total;

	return 0;
}