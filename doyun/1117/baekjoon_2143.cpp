#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// 백준 2143 - 두 배열의 합
// map
// 골드 3

// two pointer와 비슷
// A 배열과 B 배열의 모든 부분합 경우의 수 구해서 맵에 넣은 후
// 더해서 T가 되는 애들 카운트한다.

long long arr1[1002];
long long arr2[1002];
long long arr1s[1002]; // 부분합 배열
long long arr2s[1002];
long long T;
int n, m;

unordered_map<long long, long long> vec1;
unordered_map<long long, long long> vec2; // 부분합 경우의 수 담는 배열

int main()
{
	cin >> T >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr1[i];
		arr1s[i] = arr1s[i - 1] + arr1[i];
	}

	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> arr2[i];
		arr2s[i] = arr2s[i - 1] + arr2[i];
	}

	// 모든 부분합 다 구하기
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			if (vec1.find(arr1s[j] - arr1s[i - 1]) == vec1.end())
			{
				vec1.insert({arr1s[j] - arr1s[i - 1], 1	});
			}
			else vec1[arr1s[j] - arr1s[i - 1]]++;
		}
	}

	for (int i = 1; i <= m; i++)
	{
		for (int j = i; j <= m; j++)
		{
			if (vec2.find(arr2s[j] - arr2s[i - 1]) == vec2.end())
			{
				vec2.insert({ arr2s[j] - arr2s[i - 1], 1 });
			}
			else vec2[arr2s[j] - arr2s[i - 1]]++;
		}

	}

	long long cnt = 0;
	for (auto v : vec1)
	{
		if (vec2.find(T - v.first) != vec2.end())
		{
			cnt += vec2[T - v.first] * v.second;
		}
	}
	
	cout << cnt;

	return 0;
}