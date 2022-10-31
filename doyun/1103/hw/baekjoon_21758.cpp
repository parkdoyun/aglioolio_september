#include <iostream>
#include <algorithm>

using namespace std;

// 백준 21758 - 꿀 따기
// greedy, 누적 합
// 골드 5

// 모든 가짓수 다 해보기 -> 시간 초과

// 1. 벌통이 끝에 있다면 -> 하나는 끝에 두고 중간에 가지는 곳에 둔다
// 2. 벌통이 중간에 있다면 -> 벌 시작점 양 끝에 두는 게 최대이다
// 이 세가지를 다 해보면 됨

long long arr[100001];
long long sum[100001]; // 누적 합

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);


	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
		sum[i] = sum[i - 1] + arr[i];
	}

	long long max1 = 0;
	// 벌통이 끝에 있다면
	// 1. 왼쪽 끝 => 벌통 위치 : 1 벌 시작점 : i, n
	for (int i = 2; i < n; i++)
	{
		max1 = max(max1, sum[n] - arr[n] - arr[i] + sum[i - 1]);
	}

	// 2. 오른쪽 끝 => 벌통 위치 : n, 벌 시작점 : 1, i
	for (int i = 2; i < n; i++)
	{
		max1 = max(max1, sum[n] - arr[1] - arr[i] + (sum[n] - sum[i]));
	}

	// 3. 중간 => 벌통 위치 : i
	for (int i = 2; i < n; i++)
	{
		max1 = max(max1, (sum[i] - arr[1]) + (sum[n] - sum[i - 1] - arr[n]));
	}

	cout << max1;

	return 0;
}