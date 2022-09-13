#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 백준 2565 - 전깃줄
// LIS, DP
// 골드 5

// A 지역 오름차순으로 정렬했을 때, B 지역도 모두 오름차순이면 교차하지 않는다
// A 지역 오름차순으로 정렬하고 B 지역의 최장 공통 증가 수열(LIS, Longest Increasing Subsequence) 찾아서
// 전체 N에서 빼주면 된다.

struct node
{
	int a;
	int b;
};

bool cmp(node n1, node n2)
{
	if (n1.a < n2.a) return true;
	else if (n1.a == n2.a && n1.b < n2.b) return true;
	return false;
}

int DP[101];

int main()
{
	vector<node> vec;

	int n;
	cin >> n;

	int a, b;
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b;
		vec.push_back({ a, b });
	}

	// A 지역 오름차순으로 정렬
	sort(vec.begin(), vec.end(), cmp);

	// LIS 구하기

	// 기저 조건 : 한개로 이루어진 수열의 최대 길이 1
	DP[0] = 1;

	int max = -1;
	for (int i = 0; i < n; i++)
	{
		int tmp = 0;
		for (int j = 0; j < i; j++)
		{
			if (vec[i].b > vec[j].b && tmp < DP[j]) tmp = DP[j];
		}
		DP[i] = tmp + 1;
		if (DP[i] > max) max = DP[i];
	}

	cout << n - max;

	return 0;
}