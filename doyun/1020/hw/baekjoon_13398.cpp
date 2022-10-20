#include <iostream>

using namespace std;

// 백준 13398 - 연속 합
// DP
// 골드 5

// 이전까지의 연속합이 음수이면 나부터 새로 시작
// 아니면 더하기 (제거 안 한 수열)
// 해당 인덱스 뒤만 제거한 수열

int num[100001];
int DP[100001]; // 일반 연속합
int DP1[100001]; // 하나 제거하는 연속합

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> num[i];

	DP[0] = num[0];
	DP1[0] = num[0];

	int max = num[0];
	for (int i = 1; i < n; i++)
	{
		// 큰 것 넣기
		if (DP[i - 1] + num[i] > num[i]) DP[i] = DP[i - 1] + num[i];
		else DP[i] = num[i];
		
		// 건너뛸 때
		// 안 건너뛴 직전 것과 건너뛴 상태에서 더한 값 비교
		if (DP[i - 1] > DP1[i - 1] + num[i])
		{
			DP1[i] = DP[i - 1];
		}
		else DP1[i] = DP1[i - 1] + num[i];


		if (max < DP[i]) max = DP[i];
		if (max < DP1[i]) max = DP1[i];
	}
	cout << max;

	return 0;
}