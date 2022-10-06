#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 백준 3649 - 로봇 프로젝트
// 골드 5
// two pointer

// 반례 : n이 0일 때 -> 해결

vector<int> v1;

bool cmp1(int a, int b)
{
	if (a < b) return true;
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	long long x;
	int n, a;

	while (true)
	{
		cin >> x >> n;

		if (cin.eof()) break;

		v1.clear();

		for (int i = 0; i < n; i++)
		{
			cin >> a;
			v1.push_back(a);
		}

		x *= 10000000;

		sort(v1.begin(), v1.end(), cmp1); // 작은 게 앞

		// two pointer로 양쪽부터 확인
		int p1 = 0;
		int p2 = n - 1;

		long long tmp;
		int chk = -1;
		while (p1 < n && p2 >= 0)
		{
			tmp = (long long)v1[p1] + (long long)v1[p2];
			if (tmp < x) // 작을 때 -> 더 큰 쪽으로 이동
			{
				if (p1 == n - 1)
				{
					chk = 1;
					break;
				}
				p1++;
			}
			else if (tmp > x)
			{
				if (p2 == 0)
				{
					chk = 1;
					break;
				}
				p2--;
			}
			else // tmp == x
			{
				if (p1 == p2) // 같은 수라면 치지 않는다
				{
					if (p1 + 1 < n && (long long)v1[p1 + 1] + (long long)v1[p2] == x) p1++;
					else if (p2 - 1 >= 0 && (long long)v1[p1] + (long long)v1[p2 - 1] == x) p2--;
					else
					{
						chk = 1;
						break;
					}
				}
				else
				{
					if (p1 + 1 < n && (long long)v1[p1 + 1] + (long long)v1[p2] == x &&
						abs(v1[p1] - v1[p2]) >= abs(v1[p1 + 1] - v1[p2])) p1++;
					else if (p2 - 1 >= 0 && (long long)v1[p1] + (long long)v1[p2 - 1] == x &&
						abs(v1[p1] - v1[p2]) >= abs(v1[p1] - v1[p2 - 1])) p2--;
					else
					{
						break;
					}
				}
			}
		}

		if (chk != -1 || n == 0)
		{
			cout << "danger\n";
		}
		else cout << "yes " << min(v1[p1], v1[p2]) << ' ' << max(v1[p1], v1[p2]) << '\n';

	}

	
	return 0;
}