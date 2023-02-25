#include <iostream>

using namespace std;

// 백준 1806 - 부분합
// prefix sum, two pointer
// 골드 4

// 문제 잘 읽기!! S 이상도 포함

int arr[100001];
int sumArr[100001]; // 부분합 배열

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, s;
	cin >> n >> s;
	
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
		sumArr[i] = arr[i] + sumArr[i - 1];
	}
	int idx = 0;
	for (int i = 1; i <= n; i++)
	{
		if (sumArr[i] >= s)
		{
			idx = i;
			break;
		}
	}
	int start = 1;
	// idx부터 범위 조절하면서 부분합 확인
	int min1 = n + 1;
	while (true)
	{
		if (start > idx) break;
		if (idx > n) break;
		if (sumArr[idx] - sumArr[start - 1] == s)
		{
			if (min1 > idx - start + 1) min1 = idx - start + 1;
			idx++;
		}
		else if (sumArr[idx] - sumArr[start - 1] > s) // 문제 잘 읽기 (이상도 포함)
		{
			if (min1 > idx - start + 1) min1 = idx - start + 1;
			start++;
		}
		else
		{
			idx++;
		}
	}

	if (min1 == n + 1) cout << 0;
	else cout << min1;

	return 0;
}