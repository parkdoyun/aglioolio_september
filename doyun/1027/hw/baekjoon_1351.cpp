#include <iostream>
#include <map>

using namespace std;

// 백준 1351 - 무한 수열
// DP
// 골드 5

// 배열로 하려 했는데 배열 터짐
// 맵 이용해서 재귀로 품(피보나치 재귀로 푸는 것과 동일한 방식)
// int로 하니까 division by zero 오류 -> long long으로 바꾸니 됨 (오버플로우 발생한 듯)

map<long long, long long> DP;
long long n, p, q;

long long DFS(long long val)
{
	if (DP.find(val) != DP.end())
	{
		return DP[val];
	}
	long long a = DFS(val / p); // 자동 짤림 (소수점)
	DP.insert({ val / p, a });
	long long b = DFS(val / q);
	DP.insert({ val / q, b });

	return a + b;
}
int main()
{
	cin >> n >> p >> q;

	DP.insert({ 0, 1 });

	cout << DFS(n);

	return 0;
}