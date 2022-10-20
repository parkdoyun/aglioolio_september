#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 백준 1092 - 배
// greedy, binary_search

// 이분 탐색 (한 크레인 당 실을 수 있는 무게)

bool cmp(int a, int b)
{
	if (a < b) return true;
	return false;
}

vector<int> crane;
vector<int> box;
int n, m, a;

int ok(int mid) // 크레인에 mid개수만큼 박스가 담길 수 있는지
{
	int idx = 0;
	for (int i = 0; i < n; i++)
	{
		int tmp_idx = idx;
		if (idx >= m) break;
		for (int j = tmp_idx; j < tmp_idx + mid; j++)
		{
			if (j >= m) break;
			if (box[j] > crane[i]) break;
			idx++;
		}
	}
	if (idx < m) return -1;
	return 1;
}

int main()
{

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> a;
		crane.push_back(a);
	}

	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> a;
		box.push_back(a);
	}

	sort(crane.begin(), crane.end(), cmp);
	sort(box.begin(), box.end(), cmp);

	if (box[m - 1] > crane[n - 1])
	{
		cout << -1;
		return 0;
	}

	// 이분 탐색
	int start = 1;
	int end = m;
	int mid;
	int time = m;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (ok(mid) == 1)
		{
			if (time > mid) time = mid;
			end = mid - 1;
		}
		else start = mid + 1;
	}
	cout << time;
	return 0;
}