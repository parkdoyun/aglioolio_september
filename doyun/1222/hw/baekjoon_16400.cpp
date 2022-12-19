#include <iostream>
#include <vector>

using namespace std;

// 백준 16400 - 소수 화폐
// 에라토스테네스의 체 + DP
// 골드 5

// 에라토스테네스의 체 + DP (동전 문제)
// 에라토스테네스의 체 : 소수 찾는 알고리즘
// 동전 문제 점화식 DP[j] = DP[j] + DP[j-prime_num[i]];

int chk[40001];
vector<int> prime_num;
int DP[40001];

void findPrime(int n) // 에라토스테네스의 체
{
	for (int i = 2; i <= n; i++)
	{
		if (chk[i] == 1) continue;

		// i의 배수 모두 소수 아니므로 지우기
		for (int j = 2; i * j <= n; j++)
		{
			chk[i * j] = 1;
		}
	}

	// 남아있는 수 소수로 배열에 넣기
	for (int i = 2; i <= n; i++)
	{
		if (chk[i] == 1) continue;
		prime_num.push_back(i);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	findPrime(n); // 소수 찾기

	// 동전 문제 풀듯이 DP 풀기

	for (int i = 0; i < prime_num.size(); i++)
	{
		DP[prime_num[i]] = (DP[prime_num[i]] + 1) % 123456789;
		for (int j = prime_num[i]; j <= n; j++)
		{
			DP[j] = (DP[j] + DP[j - prime_num[i]]) % 123456789;
		}
	}

	cout << DP[n];

	return 0;
}