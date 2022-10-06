#include <iostream>

using namespace std;

// 백준 3079 - 입국심사
// 이진탐색
// 골드 5

// 최소 1, 최대 심사 시간 * 인원 수
// 이진탐색을 하는 수 안에 심사 마칠 수 있는지?

int arr[100001];

int main()
{
	int n, m;
	cin >> n >> m;

	int max = -1;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		if (max < arr[i]) max = arr[i];
	}

	unsigned long long start = 1;
	// int 범위보다 계산 값이 크면 long long으로 받아도 터진다
	// 형변환 필요
	unsigned long long end = (long long)max * (long long)m;
	unsigned long long mid;

	unsigned long long min = end;

	
	while (start <= end)
	{
		mid = (start + end) / 2;

		// 검사
		long long cnt = 0;
		for (int i = 0; i < n; i++)
		{
			cnt += mid / arr[i];
		}

		if (cnt >= m) // 적절 -> 더 시간 줄여도 됨
		{
			if (min > mid) min = mid;
			end = mid - 1;
		}
		else start = mid + 1;
	}

	cout << min;

	return 0;
}