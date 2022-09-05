#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 백준 2294 - 동전 2
// 골드 5
// DP

vector<int> coin; // 동전
int DP[10001];

bool cmp(int a, int b)
{
	if (a < b) return true;
	return false;
}

int main()
{
	int n, k;
	cin >> n >> k;

	int c;
	for (int i = 0; i < n; i++)
	{
		cin >> c;
		coin.push_back(c);
	}

	for (int i = 1; i <= k; i++) DP[i] = 100001; // 전부

	// 가장 작은 동전부터
	sort(coin.begin(), coin.end(), cmp);

	// 처음엔 그냥 넣기 (가장 작은 동전으로)
	for (int j = coin[0]; j <= k; j++)
	{
		DP[j] = DP[j - coin[0]] + 1;
	}


	for (int i = 1; i < n; i++)
	{
		for (int j = coin[i]; j <= k; j++)
		{
			// 이전 동전들의 가짓수에 지금 동전의 경우의 수 더할지 말지
			if (DP[j] > DP[j - coin[i]] + 1)
			{
				DP[j] = DP[j - coin[i]] + 1;
			}
		}
	}


	// 나올 수 없으면 -1 출력
	// 나올 수 없을 때 : 가장 작은 동전이 k보다 크거나, 동전들의 합으로 k 나올 수 없는 경우
	// DP[k] == 100001이 X
	if (DP[k] > 100001 || coin[0] > k) cout << -1;
	else cout << DP[k];

	return 0;

}