#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// 백준 11000 - 강의실 배정
// greedy
// 골드 5

// 자료구조 2개 사용
// 1. 강의실 시작/종료 시간 담은 배열
// 2. 이용 가능한 강의실 정보 담은 pq

// pq에 강의실 종료 시간이 빠른 순으로 담는다.
// 배열에는 시작 시간이 빠른 순으로 담은 후, 만약 pq에서 가장 빠른 종료 시간이
// 배열의 시작 시간보다 늦을 경우(들어가야 하는 수업), 해당 수업이 들어갈 강의실이 없으므로 pq에 하나 더 추가한다
// 강의실 개수는 pq.size() 출력하면 된다.

struct node
{
	int s;
	int t;
};
struct node2
{
	int t; // 종료 시간
};

bool operator<(node2 n1, node2 n2)
{
	if (n1.t > n2.t) return true;
	return false;
}

bool cmp(node n1, node n2)
{
	if (n1.s < n2.s) return true;
	else if (n1.s == n2.s && n1.t < n2.t) return true;
	return false;
}

vector<node> vec; // 강의실 정보
priority_queue<node2> pq; // 수업 가능한 강의실 (종료 시간 비교)

int main()
{
	int n;
	cin >> n;

	node tmp;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp.s >> tmp.t;
		vec.push_back(tmp);
	}

	// 시작 시간이 빠른 순으로 정렬, 같다면 종료 시간 빠른 순
	sort(vec.begin(), vec.end(), cmp);

	for (int i = 0; i < n; i++)
	{
		if (pq.empty())
		{
			pq.push({ vec[i].t });
			continue;
		}

		if (pq.top().t > vec[i].s)
		{
			pq.push({ vec[i].t });
		}
		else
		{
			pq.pop();
			pq.push({ vec[i].t });
		}
		
	}

	cout << pq.size();

	return 0;
}